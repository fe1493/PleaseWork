//
// Created by yonatan on 26/12/2019.
//

#include <thread>
#include "Parser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "Expression.h"

/*
 * run the Commands from the fly.txt
 */
void Parser::parse() {
    // index of the current command
    int index = 0;
    // true - when the server listening
    bool isServerConnect = false;
    // true - when the client connect
    bool isClientConnect = false;
    // the current command
    Command *c;

    while (index < finalStringVector->size())
    {
        string commandName = finalStringVector->at(index);
        // if the command is in the first Map Commands
        // operServer, connectClient, Print, Sleep, Define Var
        if (firstMapCommands->find(commandName) != firstMapCommands->end())
        {
            c = firstMapCommands->at(commandName);
        }
            // check if the key is a Var in the output Map
        else if (this->outputSymbolTable->outputMap->find(commandName) != this->outputSymbolTable->outputMap->end())
        {
            c = this->outputSymbolTable->outputMap->at(commandName);
        }

        // if the current Command is OpenDataServer
        if (commandName == "openDataServer")
        {
            // open new thread, that create a new socket and wait to a client.
            // this thread stop the program, until the client connect and print the first line
            thread serverThread(OpenServerCommand::openServer, &finalStringVector->at(index), &isServerConnect,
                                this->inputSymbolTable, this->outputSymbolTable);
            // while the client don't connect, stop the program
            while (!isServerConnect)
            {
                //serverThread.join();
            }
            serverThread.detach();
        }
        if (commandName == "connectControlClient")
        {
            thread clientThread(ConnectCommand::connectClient, &finalStringVector->at(index),
                                &isClientConnect, this->queueForUpdatingServer, this->outputSymbolTable);
            while (!isClientConnect)
            {
                //clientThread.join();
            }
            clientThread.detach();
        }
        try{
            index += c->execute(&finalStringVector->at(index), this->inputSymbolTable,
                                outputSymbolTable, this->queueForUpdatingServer);
        }
        catch(const char* e) {
            throw ("unknown Command");
        }
        // close the thread
        isServerConnect = false;
        isClientConnect = false;
    }
}

/// check the condition of the loop
/// \param str
/// \param outputTable
/// \return true or false
 double Parser::checkExpression(string * str,OutputSymbolTable* outputTable )
{
    //create a new interpreter and expression
    auto* i = new Interpreter();
    Expression* e = nullptr;
    //we want to interpret the expression based on the string we get
    e = i->interpret(*str,outputTable);
    double result = e->calculate();
    return result;
}
