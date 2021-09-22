#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"


const int lowercaseLowerBound = 97;
const int lowercaseUpperBound = 122;
const int uppercaseLowerBound = 65;
const int uppercaseUpperBound = 90;
const int numericLowerBound = 48;
const int numericUpperBound = 57;
const int space = 32;
const int underscore = 95;
const int apostrophe = 39;



template <typename T>
class SymbolTable
{
private:
    class Symbol;
    class Scope;

    Scope* scopeHead;
    Scope* scopeCurrent; // pointer to current scope
    int level; // current scope index

    class Symbol
    {
    private:
        string name;
        string datatype;
        T data;
        Symbol* symbolNext;
        Symbol* symbolPrev;
    public:
        Symbol(string name, string datatype)
        {
            this->name = name;
            this->datatype = datatype;
            symbolNext = NULL;
            symbolPrev = NULL;
        }
        
        void setName(string name)
        {
            this->name = name;
        }

        void setDatatype(string datatype) 
        { 
            this->datatype = datatype;
        }

        void setData(T data)
        {
           this->data = data;
        }

        void setNext(Symbol* symbol)
        {
          symbolNext = symbol;
        }

        void setPrev(Symbol* symbol)
        {
          symbolPrev = symbol;
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

        Symbol* getNext()
        {
            return symbolNext;
        }

        Symbol* getPrev()
        {
            return symbolPrev;
        }
    };

    class Scope
    {
    private:
        Symbol* symbolHead;
        Symbol* symbolCurrent;
        Scope* scopeNext;
        Scope* scopePrev;
    public:
        Scope()
        {
            symbolHead = NULL;
            symbolCurrent = NULL;
            scopeNext = NULL;
            scopePrev - NULL;
        }

        ~Scope()
        {
            while(symbolCurrent != NULL)
            {
                Symbol* temp = symbolCurrent;

                symbolCurrent = symbolCurrent->getPrev(); 
                symbolCurrent->getNext() = NULL;

                delete temp;
            }
        }

        void addSymbol(string name, string datatype)
        {            
            Symbol newSymbol = new Symbol(name, datatype);

            if (symbolHead == NULL)
            {
              symbolHead = newSymbol;
              symbolCurrent = newSymbol;
            }
            else
            {
              symbolCurrent.setNext(newSymbol);
              newSymbol.setPrev(symbolCurrent);

              symbolCurrent = newSymbol;
            }
        }

        bool assignSymbol(string name, T data)
        {
            Symbol* temp = symbolHead;

            while(temp != NULL)
            {
              if (temp.getName() == name)
              {
                temp.setData(data);
                return true;
              }
              else
              {
                temp = temp.getNext();
              }
            }

            return false;
        }

        Symbol findSymbol(string name)
        {
            Symbol* temp = symbolHead;

            while (temp != NULL)
            {
              if (temp.getName() != name)
              {
                temp = temp.getNext();
              }
              else
              {
                return temp;
              }
            }
            
            return NULL;
        }        

        void setNext(Scope* scope)
        {
          scopeNext = scope;
        }

        void setPrev(Scope* scope)
        {
          scopeNext = scope;
        }

        Scope* getNext()
        {
          return scopeNext;
        }

        Scope* getPrev()
        {
          return scopePrev;
        }

    };    

public:
    SymbolTable()
    {
        levelIndex = 0;
        scopeHead = new Scope();
        scopeCurrent = scopeHead;
    }

    ~SymbolTable()
    {
        while(scopeCurrent != scopeHead)
        {
            END();
        }
        
        Scope* temp = scopeCurrent;

        scopeCurrent = scopeCurrent->getPrev();
        scopeCurrent->getNext() = NULL;

        delete temp;
    }

    void run(string filename);

    void addScope()
    {
        Scope newScope = new Scope();

        scopeCurrent.setNext(newScope);
        newScope.setPrev(scopeCurrent);

        scopeCurrent = newScope;
        ++levelIndex;
    }

    bool INSERT(string name, string datatype)
    {
        if(scopeCurrent->findSymbol(name))
            return false;
        scopeCurrent.addSymbol(name, datatype);
        return true;
        
    }

    int ASSIGN(string name, string value)
    {
        //scenario 1 
        if(scopeCurrent->findSymbol(name))
            return 1;     

        Scope* temp = scopeCurrent;
        
        while (temp != NULL)
        {
            if (temp.findSymbol(name))
            {
                if(temp.findSymbol(name)->getDatatype == "number");
                {
                    //if value = int
                    for (int i = 0; i < value.length(); i++)
                    {
                        if (isdigit(value[i]) == false)
                            return 2;
                    }

                    temp.assignSymbol(name, value);
                    return 0;
                }
            else 
                if(temp.findSymbol(name)->getDatatype == "string");
                {
                    //if value != int
                    for (int i = 0; i < value.length(); i++)
                    {
                        if (isdigit(value[i]) == true)
                            return 2;
                    }

                    temp.assignSymbol(name, value);
                    return 0;
                }
            }
            else
                temp = temp.getPrev();
        }
        
        //scenario 0
        return 0;
    }

    int LOOKUP(string name)
    {
        Scope* temp = scopeCurrent;
        for(int i = levelIndex; i == 0; i--)
        {
            if(temp.findSymbol(name))
                return i;
            temp = temp->getPrev;
        }
        
        return -1; 
    }

    
    string PRINT()
    {
        Scope* scopeT = scopeCurrent;
        Scope temp; 
        string print = "";

        for(int i = levelIndex; i >= 0; i--)
        {
            // per scope
            Symbol* symbolT = scopeT->symbolCurrent;
            while(symbolT->getPrev() != NULL)
            {
                // per symbol in scope
                if(temp.findSymbol(symbolT.getName()))
                    temp.addSymbol(symbolT.getName,symbolT.getDatatype);
                    print = print + symbolT.getName() + "//" + i + " ";
                SymbolT = SymbolT->getPrev();
            }
            
            scopeT = scopeT->getPrev();
        }

        print.erase(print.length() - 1, 1);
        return print;
    }

    string RPRINT()
    {

        Scope* scopeT = scopeCurrent;
        Scope temp; 
        string rprint = "";

        for(int i = levelIndex; i >= 0; i--)
        {
            // per scope
            Symbol* symbolT = scopeT->symbolCurrent;
            while(symbolT->getPrev() != NULL)
            {
                // per symbol in scope
                if(temp.findSymbol(symbolT.getName()))
                    temp.addSymbol(symbolT.getName,symbolT.getDatatype);
                    rprint = symbolT.getName() + "//" + i + " " + rprint;
                SymbolT = SymbolT->getPrev();
            }
            
            scopeT = scopeT->getPrev();
        }

        rprint.erase(rprint.length() - 1, 1);
        return rprint;
    }

    void BEGIN()
    {
        addScope();
    }

    bool END()
    {
        if(scopeCurrent != scopeHead)
        {
            Scope* temp = scopeCurrent;

            scopeCurrent = scopeCurrent->getPrev();
            scopeCurrent->getNext() = NULL;

            levelIndex--;
            delete temp;

            return true;
        }
        else 
            return false;
    }
};

#endif