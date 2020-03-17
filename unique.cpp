/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Aparajita Rana
 * Date        : 02/18/2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) 
{
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    
    //iterates through the full s
    for(unsigned int x=0; x<s.length(); x++)
    {
        //if it is lower, then ends loop by returning false
		if (!islower(s[x]))
        {
			return false;
		}

	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    if (s.length()==0)
    {
        return true;
    }
	 unsigned int x=0;
    
    //looks to find non-unique letters
	 for (unsigned int c=0; c<s.length();c++)
	 {
         //97 because of language
		 int val=s[c]-97;
		 if ((x & (1 << val))>0)
         {
             return false;
         }
		 x |= (1 << val);
	 }
	 return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    
    if(argc!=2)
    {
			cout << "Usage: ./unique <string>" << endl;
			return 1;
	}
    
	bool x=is_all_lowercase(string(argv[1]));
	bool y=all_unique_letters(string(argv[1]));
    
	if(argc==2)
    {
        //check if string has lowercase
		if(!x)
        {
			cout << "Error: String must contain only lowercase letters." << endl;
			return 1;
		}
        // check if unique
        else if(!y)
        {
			cout << "Duplicate letters found."<< endl;
			return 1;
		}
        // at this point, they are unique & lowercase
        else
        {
			cout << "All letters are unique." << endl;
			return 0;
		}
        
	}
}
