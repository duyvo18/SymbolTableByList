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



class SymbolTable
{
private:
	class Symbol;
	class Scope;

	Scope* scopeHead;
	Scope* scopeCurrent; // pointer to current scope
	int levelIndex; // current scope index

	class Symbol
	{
	private:
		string name;
		string datatype;
		string data;
		Symbol* symbolNext;
		Symbol* symbolPrev;
	public:
		Symbol(string name, string datatype)
		{
			this->name = name;
			this->datatype = datatype;
			symbolNext = NULL;
			symbolPrev = NULL;
			data = "";
		}

		void setName(string name)
		{
			this->name = name;
		}

		void setDatatype(string datatype)
		{
			this->datatype = datatype;
		}

		void setData(string data)
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

		string getData()
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
			scopePrev = NULL;
		}

		~Scope()
		{
			while (symbolCurrent != NULL)
			{
				Symbol* temp = symbolCurrent;

				symbolCurrent = symbolCurrent->getPrev();

				delete temp;
			}
		}

		void addSymbol(string name, string datatype)
		{
			Symbol* newSymbol = new Symbol(name, datatype);

			if (symbolHead == NULL)
			{
				symbolHead = newSymbol;
				symbolCurrent = newSymbol;
			}
			else
			{
				symbolCurrent->setNext(newSymbol);
				newSymbol->setPrev(symbolCurrent);

				symbolCurrent = newSymbol;
			}
		}

		bool assignSymbol(string name, string data)
		{
			Symbol* temp = symbolHead;

			while (temp != NULL)
			{
				if (temp->getName() == name)
				{
					temp->setData(data);
					return true;
				}
				else
				{
					temp = temp->getNext();
				}
			}

			return false;
		}

		Symbol* findSymbol(string name)
		{
			Symbol* temp = symbolHead;

			while (temp != NULL)
			{
				if (temp->getName() != name)
				{
					temp = temp->getNext();
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
			scopePrev = scope;
		}

		Scope* getNext()
		{
			return scopeNext;
		}

		Scope* getPrev()
		{
			return scopePrev;
		}

		Symbol* getCurrentSymbol()
		{
			return symbolCurrent;
		}
	};

public:
	SymbolTable();
	~SymbolTable();

	void run(string filename);

	bool INSERT(string name, string datatype);
	int ASSIGN(string name, string value);
	int LOOKUP(string name);
	string PRINT();
	string RPRINT();
	void BEGIN();
	bool END();

	void addScope();
	Symbol* findIden(string name);

	bool isNum(string str);
	bool isStr(string value);
	bool isIden(string value);
};



#endif