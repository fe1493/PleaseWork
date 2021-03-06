//
// Created by yonatan on 02/01/2020.
//

#ifndef PLEASEWORK_CONDITIONPARSER_H
#define PLEASEWORK_CONDITIONPARSER_H

#include "Command.h"

/*
 * run the command in the loop
 */
class ConditionParser: public Command {
private:
    unordered_map<string, Command *> *firstMapCommands;
public:
    ConditionParser(unordered_map<string, Command *> *firstMap){
        this->firstMapCommands = firstMap;
    }
    int execute(string *str, InputSymbolTable* inputSymbolTable,
                OutputSymbolTable* outputSymbolTable, queue<string> *queueForUpdatingServer);
};


#endif //PLEASEWORK_CONDITIONPARSER_H
