//
// Created by Efraim Paley on 26/12/2019.
//

#ifndef PLEASEWORK_VAR_H
#define PLEASEWORK_VAR_H

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include "Command.h"

// *** Var Class ***
class Var : public Command
{
public:
    string varName;
    string simName;
    int direction;
    double value;

    virtual int execute(string* str, unordered_map<string, Command*> *input, unordered_map<string, Command*> *output);

};


#endif //PLEASEWORK_VAR_H