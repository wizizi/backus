#include "transformations.h"
#include <iostream>

Automaton * GrammarToAutomaton(const Grammar &G)
{
    Automaton * A = new Automaton();
    A->setExAlphabet(G.getTAlphabet());
    for(int i = 0; i < G.getNtAlphabet().size(); i++)
        A->addState(G.getNtAlphabet()[i]);
    for(int j = 0; j < G.getRules().size(); j++)
    {
        if(G.getRules()[j].a != "")
        {
            if(G.getRules()[j].B == "END" && !A->getInAlphabet().contains("END"))
            {
                A->addState("END");
                A->setFinality("END", true);
            }
            A->addConnection(G.getRules()[j].A, G.getRules()[j].a, G.getRules()[j].B);
        }
        else if(G.getRules()[j].B == "END")
            A->setFinality(G.getRules()[j].A, true);

    }

    return A;
}


Grammar * AutomatonToGrammar(const Automaton &A)
{
    Grammar * G = new Grammar();
    QVector<QString> cell;
    std::cout << "TRUE SIZE:" << A.getConnections().matrix.size() << std::endl;
    std::cout << "DECLARED SIZE:" << A.getConnections().size << std::endl;
    for(int i = 0; i < A.getConnections().size; i++)
    {
        for(int j = 0; j < A.getConnections().size; j++)
        {
            cell = A.getConnections().matrix[i][j];
            for(int k = 0; k < cell.size(); k++)
                G->addRule(Rule(A.getInAlphabet()[i].name, cell[k], A.getInAlphabet()[j].name));
        }
    }
    for(int q = 0; q < A.getInAlphabet().size(); q++)
    {
        if(A.getInAlphabet()[q].isFinal)
        {
             G->addRule(Rule(A.getInAlphabet()[q].name, "", "END"));
        }

    }
    return G;
}

