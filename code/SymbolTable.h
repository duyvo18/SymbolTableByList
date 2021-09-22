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
	SymbolTable()
	{
		levelIndex = 0;
		scopeHead = new Scope();
		scopeCurrent = scopeHead;
	}

	~SymbolTable()
	{
		while (scopeCurrent != scopeHead)
		{
			END();
		}

		Scope* temp = scopeCurrent;

		scopeCurrent = scopeCurrent->getPrev();

		delete temp;
	}

	void run(string filename);

	void addScope()
	{
		Scope* newScope = new Scope();

		scopeCurrent->setNext(newScope);
		newScope->setPrev(scopeCurrent);

		scopeCurrent = newScope;
		++levelIndex;
	}

	bool INSERT(string name, string datatype)
	{
		if (scopeCurrent->findSymbol(name))
			return false;
		scopeCurrent->addSymbol(name, datatype);
		return true;

	}

	int ASSIGN(string name, string value)
	{
		Scope* pScope = scopeCurrent;
		Symbol* identifier = NULL;

		// find name
		while (pScope != NULL) {
			if (pScope->findSymbol(name))
			{
				identifier = pScope->findSymbol(name);
				break;
			}
			else
				pScope = pScope->getPrev();
		}


		if (identifier == NULL)
			return 3;

		if (isStr(value))
		{
			if (identifier->getDatatype() == "string")
			{
				identifier->setData(value);
				return 0;
			}
			else
				return 2;
		}
		else if (isNum(value))
		{
			if (identifier->getDatatype() == "number")
			{
				identifier->setData(value);
				return 0;
			}
			else
				return 2;
		}
		else if (isIden(value))
		{
			Symbol* valueIden = findIden(value);

			if (valueIden == NULL)
			{
				return 3;
			}

			if (valueIden->getDatatype() == identifier->getDatatype())
			{
				identifier->setData(valueIden->getData());
				return 0;
			}
			else
				return 2;
		}
		else
			return 1;

		/*
		// number or iden
		else if (value.back() != apostrophe && value.front() != apostrophe)
		{
			bool isNumber = true;
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] < numericLowerBound || value[i] > numericUpperBound)
					isNumber = false;
			}

			// num
			if (isNumber)
			{
			}
			// iden?
			else
			{
				Symbol* valueIden = NULL;

				pScope = scopeCurrent;
				while (pScope != NULL)
				{
					if (pScope->findSymbol(value))
					{
						valueIden = pScope->findSymbol(value);
						break;
					}
					else
						pScope = pScope->getPrev();
				}

				// iden
				if (valueIden != NULL)
				{
				}
				// not iden
				else
					return 3;
			}

		}
		// unknown
		else
			return 1;
		*/
		/*
		// name not found
		if (identifier == NULL)
			return 3;
		else {
			if (identifier->getDatatype() == "number")
			{
				if (value.back() == apostrophe && value.front() == apostrophe)
					return 2;

				for (int i = 0; i < value.length(); i++)
				{
					if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
					else
						return 1;
				}


				identifier->setData(value);
				return 0;
			}
			else
			{
				if (value.back() == apostrophe && value.front() == apostrophe)
				{
					for (int i = 1; i < value.length() - 1; i++)
					{
						if (value[i] >= lowercaseLowerBound && value[i] <= lowercaseUpperBound);
						else if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
						else if (value[i] >= uppercaseLowerBound && value[i] <= uppercaseUpperBound);
						else if (value[i] == space);
						else
							return 1;
					}

					identifier->setData(value);
					return 0;
				}
				else
					return 2;

			}
		}

		// find value as identifier
		pScope = scopeCurrent;
		while (pScope != NULL)
		{
			if (pScope->findSymbol(value))
			{
				valueIden = pScope->findSymbol(value);
				break;
			}
			else
				pScope = pScope->getPrev();
		}

		// if value is identifier
		if (valueIden != NULL)
		{
			if (valueIden->getDatatype() == identifier->getDatatype())
			{
				identifier->setData(valueIden->getData());
				return 0;
			}
			else
				return 2;
		}
		else
			return 3;
		*/
		/*
		while (temp != NULL)
		{
			if (temp->findSymbol(name))
			{
				if (temp->findSymbol(name)->getDatatype() == "number")
				{
					if (value.back() == apostrophe && value.front() == apostrophe)
						return 2;

					for (int i = 0; i < value.length(); i++)
					{
						if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
						else
							return 1;
					}


					temp->assignSymbol(name, value);
					return 0;
				}
				else
				{
					if (value.back() == apostrophe && value.front() == apostrophe)
					{
						for (int i = 1; i < value.length() - 1; i++)
						{
							if (value[i] >= lowercaseLowerBound && value[i] <= lowercaseUpperBound);
							else if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
							else if (value[i] >= uppercaseLowerBound && value[i] <= uppercaseUpperBound);
							else if (value[i] == space);
							else
								return 1;
						}
						temp->assignSymbol(name, value);
						return 0;
					}
					else
						return 2;
				}
			}
			else
				temp = temp->getPrev();
		}
		// cant not find it
		return 3;
		*/
	}

	int LOOKUP(string name)
	{
		Scope* temp = scopeCurrent;
		for (int i = levelIndex; i >= 0; i--)
		{
			if (temp->findSymbol(name))
				return i;
			temp = temp->getPrev();
		}

		return -1;
	}

	string PRINT()
	{
		Scope* scopeT = scopeCurrent;
		Scope* temp = new Scope();
		string print = "";

		for (int i = levelIndex; i >= 0; i--)
		{
			// per scope
			Symbol* symbolT = scopeT->getCurrentSymbol();
			while (symbolT != NULL)
			{
				// per symbol in scope
				if (!temp->findSymbol(symbolT->getName()))
				{
					temp->addSymbol(symbolT->getName(), symbolT->getDatatype());
					print = print + symbolT->getName() + "//" + to_string(i) + " ";
				}
				symbolT = symbolT->getPrev();
			}

			scopeT = scopeT->getPrev();
		}

		print.erase(print.length() - 1, 1);
		return print;
	}

	string RPRINT()
	{
		Scope* scopeT = scopeCurrent;
		Scope* temp = new Scope();
		string rprint = "";

		for (int i = levelIndex; i >= 0; i--)
		{
			// per scope
			Symbol* symbolT = scopeT->getCurrentSymbol();
			while (symbolT != NULL)
			{
				// per symbol in scope
				if (!temp->findSymbol(symbolT->getName()))
				{
					temp->addSymbol(symbolT->getName(), symbolT->getDatatype());
					rprint = symbolT->getName() + "//" + to_string(i) + " " + rprint;
				}
				symbolT = symbolT->getPrev();
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
		if (scopeCurrent != scopeHead)
		{
			Scope* temp = scopeCurrent;

			scopeCurrent = scopeCurrent->getPrev();
			scopeCurrent->setNext(NULL);

			levelIndex--;
			delete temp;

			return true;
		}
		else
			return false;
	}

	bool isNum(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] < numericLowerBound || str[i] > numericUpperBound)
				return false;
		}
		return true;
	}

	bool isStr(string value)
	{
		if (value.back() == apostrophe && value.front() == apostrophe)
		{
			for (int i = 1; i < value.length() - 1; i++)
			{
				if (value[i] >= lowercaseLowerBound && value[i] <= lowercaseUpperBound);
				else if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
				else if (value[i] >= uppercaseLowerBound && value[i] <= uppercaseUpperBound);
				else if (value[i] == space);
				else
					return false;
			}
			return true;
		}
		else
			return false;
	}

	bool isIden(string value) {
		if (value[0] >= lowercaseLowerBound && value[0] <= lowercaseUpperBound)
		{
			for (int i = 0; i < value.length(); i++)
			{
				if (value[i] >= lowercaseLowerBound && value[i] <= lowercaseUpperBound);
				else if (value[i] >= uppercaseLowerBound && value[i] <= uppercaseUpperBound);
				else if (value[i] >= numericLowerBound && value[i] <= numericUpperBound);
				else if (value[i] == underscore);
				else
					return false;
			}
			return true;
		}
		else
			return false;
	}
	
	Symbol* findIden(string name)
	{
		Symbol* iden = NULL;
		Scope* tmp = scopeCurrent;

		while (tmp != NULL)
		{
			if (tmp->findSymbol(name))
			{
				iden = tmp->findSymbol(name);
				break;
			}
			else
				tmp = tmp->getPrev();
		}

		return iden;
	}
};



#endif