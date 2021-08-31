#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"



template <typename T>
class SymbolTable
{
private:
    class Symbol;
    class Scope;

    Scope* scopeHead;
    Scope* scopeCurrent;
    int size;


    class Symbol
    {
    private:
        string name;
        string datatype;
        T data;
        Symbol* symbolNext;
    public:

    };

    class Scope
    {
    private:
        Symbol* symbolHead;
        Symbol* symbolCurrent;
        Scope* scopeNext;
        int size;
    public:

    };



    

public:
    SymbolTable() {}
    void run(string filename);
};
#endif