#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include "automaton.h"
#include "grammar.h"
#include "rule.h"

Automaton * GrammarToAutomaton(const Grammar &G);
Grammar * AutomatonToGrammar(const Automaton &A);

#endif // TRANSFORMATIONS_H
