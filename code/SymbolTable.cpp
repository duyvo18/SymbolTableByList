#include "SymbolTable.h"


SymbolTable::SymbolTable() {
	levelIndex = 0;
	scopeHead = new Scope();
	scopeCurrent = scopeHead;
}

SymbolTable::~SymbolTable() {
	while (scopeCurrent != scopeHead)
	{
		END();
	}

	Scope* temp = scopeCurrent;

	scopeCurrent = scopeCurrent->getPrev();

	delete temp;
}

void SymbolTable::run(string filename)
{
	ifstream fin;
	fin.open(filename);

	while (!fin.eof())
	{
		string temp;
		string ins;
		getline(fin, ins, '\n');

		//1 ve
		if (ins == "BEGIN")
		{
			BEGIN();
		}
		else if (ins == "END")
		{
			if (!END())
				throw UnknownBlock();
		}
		else if (ins == "PRINT")
		{
			cout << PRINT() << endl;
		}
		else if (ins == "RPRINT")
		{
			cout << RPRINT() << endl;
		}
		else
		{
			// n ve 
			size_t pos = ins.find_first_of(' ', 0);
			temp = ins.substr(0, pos);

			if (temp == "INSERT")
			{
				//cutting
				temp = ins.substr(pos + 1, ins.find_first_of(' ', pos + 1) - (pos + 1));
				pos = ins.find_first_of(' ', pos + 1);

				//valid name
				if (!isIden(temp))
					throw InvalidInstruction(ins);

				/*
				if (temp[0] >= lowercaseLowerBound && temp[0] <= lowercaseUpperBound)
				{
					for (int i = 0; i < temp.length(); i++)
					{
						if (temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound);
						else if (temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
						else if (temp[i] == underscore);
						else
							throw InvalidInstruction(ins);
					}
				}
				else
					throw InvalidInstruction(ins);
				*/

				//cutting
				string data = ins.substr(pos + 1, ins.find_first_of('\n', pos + 1) - (pos + 1));
				pos = ins.find_first_of('\n', pos + 1);

				//valid datatype
				if (data == "number" || data == "string");
				else
					throw InvalidInstruction(ins);

				if (INSERT(temp, data))
					cout << "success\n";
				else
					throw Redeclared(ins);
			}
			else if (temp == "ASSIGN")
			{
				//scenario 0 = success, 1 = invalidinstruction, 2 = typemismatch
				int scenario = 0;

				//cutting
				temp = ins.substr(pos + 1, ins.find_first_of(' ', pos + 1) - (pos + 1));
				pos = ins.find_first_of(' ', pos + 1);

				//valid name
				if (!isIden(temp))
					throw InvalidInstruction(ins);

				/*
				if (temp[0] >= lowercaseLowerBound && temp[0] <= lowercaseUpperBound)
				{
					for (int i = 1; i < temp.length(); i++)
					{
						if (temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound);
						else if (temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
						else if (temp[i] == underscore);
						else
							throw InvalidInstruction(ins);
					}
				}
				else
					throw InvalidInstruction(ins);
				*/

				string name = temp;

				//cutting
				temp = ins.substr(pos + 1, ins.find_first_of('\n', pos + 1) - (pos + 1));
				pos = ins.find_first_of('\n', pos + 1);

				scenario = ASSIGN(name, temp);

				//controller
				if (scenario == 1)
					throw InvalidInstruction(ins);
				else if (scenario == 2)
					throw TypeMismatch(ins);
				else if (scenario == 3)
					throw Undeclared(ins);
				else
					cout << "success\n";
			}
			else if (temp == "LOOKUP")
			{
				temp = ins.substr(pos + 1, ins.find_first_of('\n', pos + 1) - (pos + 1));
				pos = ins.find_first_of('\n', pos + 1);

				if (!isIden(temp))
					throw InvalidInstruction(ins);

				if (LOOKUP(temp) != -1)
				{
					cout << LOOKUP(temp);
					cout << endl;
				}
				else
					throw Undeclared(ins);
			}
			else
				throw InvalidInstruction(ins);
		}
	}

	// check scope level
	if (levelIndex != 0)
		throw UnclosedBlock(levelIndex);
}

bool SymbolTable::INSERT(string name, string datatype) {
	if (scopeCurrent->findSymbol(name))
		return false;

	scopeCurrent->addSymbol(name, datatype);

	return true;
}

int SymbolTable::ASSIGN(string name, string value) {
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
			identifier->adjustData(value);
			return 0;
		}
		else
			return 2;
	}
	else if (isNum(value))
	{
		if (identifier->getDatatype() == "number")
		{
			identifier->adjustData(value);
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
			identifier->adjustData(valueIden->getData());
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


			identifier->adjustData(value);
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

				identifier->adjustData(value);
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
			identifier->adjustData(valueIden->getData());
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

int SymbolTable::LOOKUP(string name) {
	Scope* temp = scopeCurrent;
	for (int i = levelIndex; i >= 0; i--)
	{
		if (temp->findSymbol(name))
			return i;
		temp = temp->getPrev();
	}

	return -1;
}

string SymbolTable::PRINT() {
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
				print = symbolT->getName() + "//" + to_string(i) + " " + print;
			}
			symbolT = symbolT->getPrev();
		}

		scopeT = scopeT->getPrev();
	}

	if (print.length() != 0)
		print.erase(print.length() - 1, 1);

	return print;
}

string SymbolTable::RPRINT() {
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
				rprint = rprint + symbolT->getName() + "//" + to_string(i) + " ";
			}
			symbolT = symbolT->getPrev();
		}
		scopeT = scopeT->getPrev();
	}

	if (rprint.length() != 0)
		rprint.erase(rprint.length() - 1, 1);

	return rprint;
}

void SymbolTable::BEGIN() {
	addScope();
}

bool SymbolTable::END() {
	if (scopeCurrent != scopeHead)
	{
		Scope* temp = scopeCurrent;

		scopeCurrent = scopeCurrent->getPrev();
		scopeCurrent->adjustNext(NULL);

		levelIndex--;
		delete temp;

		return true;
	}
	else
		return false;
}

bool SymbolTable::isNum(string str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < numericLowerBound || str[i] > numericUpperBound)
			return false;
	}
	return true;
}

bool SymbolTable::isStr(string value) {
	if (value.back() == apostrophe && value.front() == apostrophe)
	{
		for (size_t i = 1; i < value.length() - 1; i++)
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

bool SymbolTable::isIden(string value) {
	if (value[0] >= lowercaseLowerBound && value[0] <= lowercaseUpperBound)
	{
		for (size_t i = 0; i < value.length(); i++)
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

void SymbolTable::addScope() {
	Scope* newScope = new Scope();

	scopeCurrent->adjustNext(newScope);
	newScope->adjustPrev(scopeCurrent);

	scopeCurrent = newScope;
	++levelIndex;
}

SymbolTable::Symbol* SymbolTable::findIden(string name) {
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


SymbolTable::Symbol::Symbol(string name, string datatype) {
	this->name = name;
	this->datatype = datatype;
	symbolNext = NULL;
	symbolPrev = NULL;
	data = "";
}

void SymbolTable::Symbol::adjustName(string name) {
	this->name = name;
}

void SymbolTable::Symbol::adjustDatatype(string datatype) {
	this->datatype = datatype;
}

void SymbolTable::Symbol::adjustData(string data) {
	this->data = data;
}

void SymbolTable::Symbol::adjustNext(Symbol* symbol) {
	symbolNext = symbol;
}



void SymbolTable::Symbol::adjustPrev(Symbol* symbol)
{
	symbolPrev = symbol;
}

string SymbolTable::Symbol::getName()
{
	return this->name;
}

string SymbolTable::Symbol::getDatatype()
{
	return this->datatype;
}

string SymbolTable::Symbol::getData()
{
	return this->data;
}

SymbolTable::Symbol* SymbolTable::Symbol::getNext()
{
	return symbolNext;
}

SymbolTable::Symbol* SymbolTable::Symbol::getPrev()
{
	return symbolPrev;
}



SymbolTable::Scope::Scope()
{
	symbolHead = NULL;
	symbolCurrent = NULL;
	scopeNext = NULL;
	scopePrev = NULL;
}

SymbolTable::Scope::~Scope()
{
	while (symbolCurrent != NULL)
	{
		Symbol* temp = symbolCurrent;

		symbolCurrent = symbolCurrent->getPrev();

		delete temp;
	}
}

void SymbolTable::Scope::addSymbol(string name, string datatype)
{
	Symbol* newSymbol = new Symbol(name, datatype);

	if (symbolHead == NULL)
	{
		symbolHead = newSymbol;
		symbolCurrent = newSymbol;
	}
	else
	{
		symbolCurrent->adjustNext(newSymbol);
		newSymbol->adjustPrev(symbolCurrent);

		symbolCurrent = newSymbol;
	}
}

bool SymbolTable::Scope::assignSymbol(string name, string data)
{
	Symbol* temp = symbolHead;

	while (temp != NULL)
	{
		if (temp->getName() == name)
		{
			temp->adjustData(data);
			return true;
		}
		else
		{
			temp = temp->getNext();
		}
	}

	return false;
}

SymbolTable::Symbol* SymbolTable::Scope::findSymbol(string name)
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

void SymbolTable::Scope::adjustNext(Scope* scope)
{
	scopeNext = scope;
}

void SymbolTable::Scope::adjustPrev(Scope* scope)
{
	scopePrev = scope;
}

SymbolTable::Scope* SymbolTable::Scope::getNext()
{
	return scopeNext;
}

SymbolTable::Scope* SymbolTable::Scope::getPrev()
{
	return scopePrev;
}

SymbolTable::Symbol* SymbolTable::Scope::getCurrentSymbol()
{
	return symbolCurrent;
}