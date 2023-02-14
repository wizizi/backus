#include "automaton.h"
#include <QtAlgorithms>
#include <iostream>

Automaton::Automaton()
{
    this->exAlphabet = {};
    this->inAlphabet = {};
    this->connections = AdjMatrix();
}

bool Automaton::addState(QString S)
{
    if(!this->exAlphabet.contains(S))
    {
        if(!this->inAlphabet.contains(S))
        {
            this->inAlphabet.append(S);
            this->connections.increaseSize();
        }
        return true;
    }
    else
        return false;
}


void Automaton::deleteState(QString S)
{
    if(!inAlphabet.contains(S))
        return;
    int stateInd = inAlphabet.indexOf(S);
    for(int i = 0; i < inAlphabet.size(); i++)
        connections.matrix[i].removeAt(stateInd);
    connections.matrix.removeAt(stateInd);
    if(connections.size > 0)
        connections.size--;
    inAlphabet.removeAt(stateInd);
}

void Automaton::setFinality(QString S, bool finality)
{
    this->inAlphabet[this->inAlphabet.indexOf(S)].isFinal = finality;
}

void Automaton::changeName(QString oldName, QString newName)
{
    inAlphabet[inAlphabet.indexOf(oldName)].name = newName;
}

bool Automaton::addSymbol(QString S)
{
    if(!this->inAlphabet.contains(S))
    {
        if(!this->exAlphabet.contains(S))
        {
            this->exAlphabet.append(S);
        }
        return true;
    }
    else
        return false;
}

bool Automaton::addConnection(QString iniState, QString symbol, QString finState)
{
    if(this->inAlphabet.contains(iniState) && this->inAlphabet.contains(finState))
    {
        this->connections.addAdj(this->inAlphabet.indexOf(iniState), this->inAlphabet.indexOf(finState), symbol);
        if(!this->exAlphabet.contains(symbol))
            return this->addSymbol(symbol);
        else
            return true;
    }
    else
        return false;
}

void Automaton::deleteConn(QString iniState, QString symbol, QString finState)
{
    if(!inAlphabet.contains(iniState) || !inAlphabet.contains(finState))
        return;
    if(connections.matrix[inAlphabet.indexOf(iniState)][inAlphabet.indexOf(finState)].contains(symbol))
    connections.matrix[inAlphabet.indexOf(iniState)][inAlphabet.indexOf(finState)]
            .removeAt(connections.matrix[inAlphabet.indexOf(iniState)][inAlphabet.indexOf(finState)]
            .indexOf(symbol));
}

QVector<QVector<QVector<int>>> Automaton::getTransMatrix()
{
    QVector<QVector<QVector<int>>> transMatrix = QVector<QVector<QVector<int>>>();
    transMatrix.resize(this->inAlphabet.size());
    for(int i = 0; i < transMatrix.size(); i++)
            transMatrix[i].resize(this->exAlphabet.size());
    for(int i = 0; i < this->connections.size; i++)
    {
        for(int j = 0; j < this->connections.size; j++)
        {
            QVector<QString> cell = this->connections.get(i, j);
            for(int k = 0; k < cell.size(); k++)
                transMatrix[i][this->exAlphabet.indexOf(cell[k])].append(j);
        }
    }

    return transMatrix;
}

const QVector<QString> &Automaton::getExAlphabet() const
{
    return exAlphabet;
}

void Automaton::setExAlphabet(const QVector<QString> &newExAlphabet)
{
    exAlphabet = newExAlphabet;
}

const QVector<State> &Automaton::getInAlphabet() const
{
    return inAlphabet;
}

void Automaton::setInAlphabet(const QVector<State> &newInAlphabet)
{
    inAlphabet = newInAlphabet;
}

const AdjMatrix &Automaton::getConnections() const
{
    return connections;
}

void Automaton::setConnections(const AdjMatrix &newConnections)
{
    connections = newConnections;
}


void Automaton::determineAutomaton()
{
    QVector<QVector<QVector<int>>> transMatrix = this->getTransMatrix();
    QVector<State> newInAlphabet = {};
    AdjMatrix * newConnections = new AdjMatrix();
    QVector<QVector<int>> * stateClasses = new  QVector<QVector<int>>();
    this->restructureStates({0}, transMatrix, newConnections, stateClasses);
    for(int i = 0; i < stateClasses->size(); i++)
    {
        bool f = false;
        for(int j = 0; j < stateClasses->at(i).size(); j++)
            f = f || this->inAlphabet.at(stateClasses->at(i).at(j)).isFinal;
        newInAlphabet.append(State(QString::number(i), f));
    }
    this->inAlphabet = newInAlphabet;
    this->connections = *newConnections;

}

void Automaton::restructureStates(QVector<int> states, QVector<QVector<QVector<int>>> transMatrix, AdjMatrix * newConnections, QVector<QVector<int>> * stateClasses)
{
    stateClasses->append(states);
    newConnections->increaseSize();
    for(int i = 0; i < this->exAlphabet.size(); i++)
    {
        QVector<int> nextStates;
        for(int j = 0; j < states.size(); j++)
        {
            if(transMatrix[states[j]][i].size() != 0)
            {
                for(int k = 0; k < transMatrix[states[j]][i].size(); k++)
                {
                    if(!nextStates.contains(transMatrix[states[j]][i][k]))
                    {
                        nextStates.append(transMatrix[states[j]][i][k]);
                    }
                }

            }
        }
        std::sort(nextStates.begin(), nextStates.end());
        if(stateClasses->contains(nextStates))
        {
            newConnections->addAdj(stateClasses->indexOf(states), stateClasses->indexOf(nextStates), this->exAlphabet.at(i));
        }
        else if(!nextStates.isEmpty())
        {
            restructureStates(nextStates, transMatrix, newConnections, stateClasses);
            newConnections->addAdj(stateClasses->indexOf(states), stateClasses->indexOf(nextStates), this->exAlphabet.at(i));
        }
    }
}

void Automaton::minimizeAutomaton()
{
    QVector<QVector<QVector<int>>> transMatrix = this->getTransMatrix();
    QVector<QVector<bool>> nextDiffMatrix = QVector<QVector<bool>>(this->inAlphabet.size(), QVector<bool>(this->inAlphabet.size(), false));
    for(int i = 0; i < this->inAlphabet.size(); i++)
        for(int j = 0; j < this->inAlphabet.size(); j++)
        {
            nextDiffMatrix[i][j] = this->inAlphabet.at(i).isFinal != this->inAlphabet.at(j).isFinal && i != j;
        }
    QVector<QVector<bool>> diffMatrix = QVector<QVector<bool>>(this->inAlphabet.size(), QVector<bool>(this->inAlphabet.size(), false));
    while(nextDiffMatrix != diffMatrix)
    {
        diffMatrix = nextDiffMatrix;
        for(int i = 0; i < this->inAlphabet.size(); i++)
        {
            for(int j = 0; j < this->inAlphabet.size(); j++)
            {
                if(diffMatrix[i][j] == false && i != j)
                {
                    for(int k = 0; k < this->exAlphabet.size(); k++)
                    {
                            for(int l = 0; l < transMatrix[i][k].size(); l++)
                                for(int m = 0; m < transMatrix[j][k].size(); m++)
                                    nextDiffMatrix[i][j] = diffMatrix[transMatrix[i][k][l]][transMatrix[j][k][m]] || nextDiffMatrix[i][j];
                            if(transMatrix[i][k].size() != transMatrix[j][k].size())
                                nextDiffMatrix[i][j] = true;
                    }
                }
            }
        }
    }
    QVector<QVector<int>> stateClasses = QVector<QVector<int>>();
    QVector<int> classifiedStates = QVector<int>();
    for(int i = 0; i < this->inAlphabet.size(); i++)
        if(!classifiedStates.contains(i))
        {
            QVector<int> newClass = {};
            for(int j = i; j < this->inAlphabet.size(); j++)
            {
               if(diffMatrix[i][j] == false)
               {
                   classifiedStates.append(j);
                   newClass.append(j);
               }
            }
            stateClasses.append(newClass);
        }
    QVector<QVector<QVector<int>>> newTransMatrix = QVector<QVector<QVector<int>>>(stateClasses.size());
    for(int i = 0; i < stateClasses.size(); i++)
    {
        newTransMatrix[i] = transMatrix[stateClasses[i][0]];
    }
    for(int i = 0; i < stateClasses.size(); i++)
        for(int j = 0; j < this->exAlphabet.size(); j++)
        {
            for(int k = 0; k < stateClasses.size(); k++)
            {
                for(int l = 0; l < newTransMatrix[i][j].size(); l++)
                {
                    if(stateClasses[k].contains(newTransMatrix[i][j][l]))
                    {
                        newTransMatrix[i][j][l] = k;
                    }
                }
            }

        }
    QVector<State> newInAlphabet = {};
    for(int i = 0; i < stateClasses.size(); i++)
    {
        bool f = false;
        for(int j = 0; j < stateClasses.at(i).size(); j++)
            f = f || this->inAlphabet.at(stateClasses.at(i).at(j)).isFinal;
        newInAlphabet.append(State(QString::number(i), f));
    }
    AdjMatrix newConnections = AdjMatrix();
    newConnections.setSize(stateClasses.size());
    for(int i = 0; i < stateClasses.size(); i++)
        for(int j = 0; j < this->exAlphabet.size(); j++)
            if(newTransMatrix[i][j].size() > 0)
                for(int k = 0; k < newTransMatrix[i][j].size(); k++)
                    newConnections.addAdj(i, newTransMatrix[i][j][k], this->exAlphabet.at(j));
    this->inAlphabet = newInAlphabet;
    this->connections = newConnections;
    this->connections.setSize(this->inAlphabet.size());

}



