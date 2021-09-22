#include "SymbolTable.h"

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
void SymbolTable<T>::run(string filename)
{
    ifstream fin;
    fin.open(filename); 
    
    while(!fin.eof())
    {
        string ins;
        string temp;
        getline(fin, ins, '\n');
        
        //1 ve
        if(ins == "BEGIN")
        {
            BEGIN();
            return "success\n";
        }
        else if(ins == "END")
        {
            if(!END())
                throw UnknownBlock();
            else
                return "success\n";
        }
        // n ve    
        int pos = ins.find_first_of(' ', 0);
        temp = ins.substr(0, pos);
        //https://www.cplusplus.com/reference/string/string/

        if(temp == "INSERT")
        {
            //cutting
            temp = ins.subtr(pos + 1, ins.find_first_of(' ', pos + 1));
            pos = ins.find_first_of(' ', pos + 1);

            //valid name
            if(temp[0] >= lowercaseLowerBound && temp[0] <= lowercaseUpperBound)
            {
                for(int i = 1; i <= temp.length(); i++)
                {
                    if(temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound); 
                    else if(temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
                    else if(temp[i] == underscore);
                    else
                        throw InvalidInstruction(ins);
                }
            }
            else 
                throw InvalidInstruction(ins);

            //cutting
            temp = ins.subtr(pos + 1, ins.find_first_of('\n', pos + 1));
            pos = ins.find_first_of('\n', pos + 1);

            //valid datatype
            if(temp == "number" || temp == "string");
            else
                throw InvalidInstruction(ins);

            return "success\n";
            
        }
        else if(ins == "ASSIGN");
        {
            //scenario 0 = success, 1 = invalidinstruction, 2 = typemismatch
            int scenario = 0;

            //cutting
            temp = ins.subtr(pos + 1, ins.find_first_of(' ', pos + 1));
            pos = ins.find_first_of(' ', pos + 1);

            //valid name
            if(temp[0] >= lowercaseLowerBound && temp[0] <= lowercaseUpperBound)
            {
                for(int i = 1; i <= temp.length(); i++)
                {
                    if(temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound); 
                    else if(temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
                    else if(temp[i] == underscore);
                    else
                        throw InvalidInstruction(ins);
                }
            }
            else 
                throw InvalidInstruction(ins);

            string name = temp;
                        
            //type mismatch
            //cutting
            temp = ins.subtr(pos + 1, ins.find_first_of('\n', pos + 1));
            pos = ins.find_first_of('\n', pos + 1);    

            //valid name
            if(temp.back() == apostrophe && temp.front() == apostrophe)
                throw InvalidInstruction(ins);
            else
                for(int i = 1; i <= temp.length(); i++)
                {
                    if(temp[i] >= lowercaseLowerBound && temp[i] <= lowercaseUpperBound); 
                    else if(temp[i] >= numericLowerBound && temp[i] <= numericUpperBound);
                    else if(temp[i] >= uppercaseLowerBound && temp[i] <= uppercaseUpperBound);
                    else if(temp[i] == space);
                    else
                        throw InvalidInstruction(ins);
                }
            
            scenario = ASSIGN(name, temp);

            //controller
            if(scenario == 1)
                throw InvalidInstruction(ins);
            else if(scenario == 2)
                throw TypeMismatch(ins);
            else 
                return "successs\n";

        }
        else if(ins == "LOOKUP");
        else if(ins == "PRINT");
        else if(ins == "RPRINT");
        else    
            throw InvalidInstruction();
    }

    // check
}