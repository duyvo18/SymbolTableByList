#include "SymbolTable.h"

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

				string name = temp;

				//type mismatch
				//cutting
				temp = ins.substr(pos + 1, ins.find_first_of('\n', pos + 1) - (pos + 1));
				pos = ins.find_first_of('\n', pos + 1);

				//valid name
				if (temp.back() == apostrophe && temp.front() == apostrophe)
					throw InvalidInstruction(ins);
				else
					for (int i = 0; i < temp.length(); i++)
					{
						if (temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound);
						else if (temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
						else if (temp[i] >= uppercaseLowerBound && temp[i] <= uppercaseUpperBound);
						else if (temp[i] == space);
						else
							throw InvalidInstruction(ins);
					}

				scenario = ASSIGN(name, temp);

				//controller
				if (scenario == 1)
					throw InvalidInstruction(ins);
				else if (scenario == 2)
					throw TypeMismatch(ins);
				else
					cout << "success\n";
			}
			else if (temp == "LOOKUP")
			{
				temp = ins.substr(pos + 1, ins.find_first_of('\n', pos + 1) - (pos + 1));
				pos = ins.find_first_of('\n', pos + 1);

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
