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
		Symbol(string name, string datatype);

		void adjustName(string name);
		void adjustDatatype(string datatype);
		void adjustData(string data);
		void adjustNext(Symbol* symbol);
		void adjustPrev(Symbol* symbol);

		string getName();
		string getDatatype();
		string getData();
		Symbol* getNext();
		Symbol* getPrev();
	};

	class Scope
	{
	private:
		Symbol* symbolHead;
		Symbol* symbolCurrent;
		Scope* scopeNext;
		Scope* scopePrev;
	public:
		Scope();
		~Scope();

		void addSymbol(string name, string datatype);
		bool assignSymbol(string name, string data);
		Symbol* findSymbol(string name);

		void adjustNext(Scope* scope);
		void adjustPrev(Scope* scope);

		Scope* getNext();
		Scope* getPrev();
		Symbol* getCurrentSymbol();
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