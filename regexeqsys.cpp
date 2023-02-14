#include "regexeqsys.h"
#include "iostream"

RegexEqSys::RegexEqSys()
{

}

RegexEq::RegexEq()
{


}

RegexEqTerm::RegexEqTerm()
{

}

RegexEqSys::RegexEqSys(const Grammar &G)
{
    equations = {};
    std::cout << "FLAG1" << std::endl;
    for(int i = 0; i < G.getNtAlphabet().size(); i++)
    {
        if(G.getNtAlphabet()[i] != "END" && !G.altRules(G.getNtAlphabet()[i]).isEmpty())
            equations.append(RegexEq(G.getNtAlphabet(), G.getNtAlphabet()[i], G.altRules(G.getNtAlphabet()[i])));
    }
    std::cout << "FLAG2" << std::endl;
}

RegexEq::RegexEq(QVector<QString> vars, QString nt, QVector<Rule> rules)
{

    if(vars.contains("END"))
        vars.removeAt(vars.indexOf("END"));
    variables = vars;
    this->NT = nt;
    for(int i = 0; i < rules.size(); i++)
    {
        QString free = rules[i].a == "" ? "1" : rules[i].a;
        if(rules[i].B == "END")
            freeTerm += freeTerm == "" ? free : "+" + free;
        else
            terms.append(RegexEqTerm(rules[i].a, rules[i].B));
    }

}

RegexEqTerm::RegexEqTerm(QString rex, QString nt)
{
    rEx = rex;
    NT = nt;
}

QString RegexEqSys::toString() const
{
    QString res = "";
    for(int i = 0; i < equations.size(); i++)
        res += equations[i].toString() + "\n";
    return res;

}

QString RegexEq::toString() const
{
    QString res = NT + " = ";
    for(int i = 0; i < terms.size(); i++)
        res += terms[i].toString() + (i == (terms.size() - 1) && freeTerm != "" ? "" : " + ");
     res += freeTerm;
    return res;
}

QString RegexEqTerm::toString() const
{
    return rEx + NT;
}

QString RegexEqTerm::getRegex() const
{
    return rEx;
}

QString RegexEqTerm::getNT() const
{
    return NT;
}

void RegexEqTerm::setRegex(QString rex)
{
    rEx = rex.contains("+") ? "(" + rex + ")" : rex;
}

QString RegexEq::getNT() const
{
    return NT;
}

QString RegexEq::getCoeff (QString nt) const
{
    QString res = "#NONE#";
    for(int i = 0; i < terms.size(); i++)
        if(terms[i].getNT() == nt)
            res = res == "#NONE#" || res == "" ? terms[i].getRegex() : res + "+" + terms[i].getRegex();
    return res;
}

void RegexEq::remove(QString nt)
{
    for(int i = 0; i < terms.size(); i++)
    {
         if(terms[i].getNT() == nt)
         {
             terms.removeAt(i);
             i--;
         }
    }
}

QString RegexEq::getSelfCoeff () const
{
    return getCoeff(getNT()) == "#NONE#" ? "" :
                                           (getCoeff(getNT()).length() > 1 && getCoeff(getNT())[0] != '(' && getCoeff(getNT())[getCoeff(getNT()).length() - 1] != ')' ?
                                           "(" + getCoeff(getNT()) + ")" : getCoeff(getNT()));
}

QString RegexEq::getFreeTerm() const
{
    return freeTerm.contains("+") ? "(" + freeTerm + ")" : freeTerm;

}

void RegexEq::plug(const RegexEq & eq)
{
    if(getCoeff(eq.getNT()) == "#NONE#")
        return;
    for(int i = 0; i < terms.size(); i++)
    {
         std::cout << getCoeff(eq.getNT()).toStdString() << std::endl;
         if(terms[i].getNT() != eq.getNT() && eq.getCoeff(terms[i].getNT()) != "#NONE#")
            terms[i].setRegex(getCoeff(eq.getNT()) +
                              (eq.getSelfCoeff() == "" ? "" : (eq.getSelfCoeff() + "*"))
                              + eq.getCoeff(terms[i].getNT()) + "+" + terms[i].getRegex());
    }
    for(int i = 0; i < variables.size(); i++)
    {
        if(getCoeff(variables[i]) == "#NONE#" && eq.getCoeff(variables[i]) != "#NONE#")
            terms.append(RegexEqTerm(getCoeff(eq.getNT()) +
                                     (eq.getSelfCoeff() == "" ? "" : (eq.getSelfCoeff() + "*"))
                                     + eq.getCoeff(variables[i]), variables[i]));
    }
    if(eq.getFreeTerm() != "")
        freeTerm += (freeTerm == "" ? getCoeff(eq.getNT()) :
                                  "+" + getCoeff(eq.getNT())) + (eq.getSelfCoeff() == "" ? eq.getFreeTerm() : eq.getSelfCoeff() + "*" + eq.getFreeTerm());
    remove(eq.getNT());
    std::cout << toString().toStdString() << std::endl;
}

QString applyAxioms(QString rex)
{
    for(int i = 0; i < rex.length(); i++)
    {
        bool drop = false;
        if(rex[i] == '1')
            drop = (i == 0 ? true : rex[i-1] != '+') && (i + 1 == rex.length() ? true : rex[i+1] != '+');
        if(drop)
        {
            rex.remove(i, 1);
            i--;
        }

    }
    return rex;
}

QString RegexEqSys::solve()
{
    if(equations.size() == 0)
        return "";
    for(int i = equations.size() - 1; i > 0; i--)
    {
        for(int j = i - 1; j >= 0; j--)
            equations[j].plug(equations[i]);
    }
    return applyAxioms(equations[0].getSelfCoeff() == "" ? equations[0].getFreeTerm() : equations[0].getSelfCoeff() + "*" + equations[0].getFreeTerm());
}




