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
    int levelIndex;


    class Symbol
    {
    private:
        string name;
        string datatype;
        T data;
        Symbol* symbolNext;
    public:
        Symbol(string name, string datatype)
        {
            this->name = name;
            this->datatype = datatype;
            symbolNext = NULL;
        } 

        void setName(string name)
        {
            this->name = name;
        }

        void setDatatype(string datatype) 
        { 
            this->datatype = datatype;
        }

        string getName()
        {
            return this->name;
        }

        string getDatatype()
        {
            return this->datatype;
        }

        T getData()
        {
            return this->data;
        }
    };

    class Scope
    {
    private:
        Symbol* symbolHead;
        Symbol* symbolCurrent;
        Scope* scopeNext;
        int level;
    public:
        Scope()
        {
            symbolHead = new Symbol();
            symbolCurrent = NULL;
            symbolNext = NULL;
            level = levelIndex;
        }
        // void addNewScope()
        // int findCurrentScopeLevel()
        // void addSymbolToScope(...)
    };


// what the current pointers are for Kuo ? -_- 
    

public:
    SymbolTable()
    {
        levelIndex = 0;
        scopeHead = new Scope();
        scopeCurrent = NULL;
        scopeNext = NULL;
    }

    void run(string filename);

    void INSERT(string name, string datatype)
    {

    }

    void ASSIGN(string name, T value)
    {

    }
};
#endif