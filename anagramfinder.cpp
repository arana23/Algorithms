/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Aparajita Rana
 * Date        : 05/06/2020
 * Description : Anagram Finder
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdbool.h>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <map>


using namespace std;

int num_elements = 0;
//3rd time doing this I decided to use a map instead of vectors so it's faster lol
map<int, vector<string>> ana_map; //all the anagrams and the length
map<int, vector<string>> vals; //all the values and length
int max=0;

//checks if two strings are anagrams
bool isAnagram(string one, string two){
    if(one==two){
        return true;
    }
    if(one.length()!=two.length()){
        return false;
    }
    else{
        //convert both to lowercase so we have a fair compare
        transform(one.begin(), one.end(), one.begin(), ::tolower);
        transform(two.begin(), two.end(), two.begin(), ::tolower);

        //alphabetize and then compare if equal
        sort(one.begin(),one.end());
        sort(two.begin(),two.end());
        return one==two;
    }
}

bool findAnagram(vector<string> data){
    int check=0;
    int size=data.size();
    bool hasA=false;
    //takes the first item compares to the rest
    for(int x=0; x<size-1;x++){
        for(int y=x+1;y<size;y++){
            if(isAnagram(data[x],data[y])){
                //we used the x val
                check=1;
                //add the anagram
                ana_map[data[y].length()].push_back(data[y]);
                //remove bc we used it
                data[y].clear();
                hasA=true;
            }
        }
        //we used the x val
        if(check==1){
            ana_map[data[x].length()].push_back(data[x]);
            data[x].clear();
            check=0;
        }
    }
    return hasA;
}

int findMax(){
    int max=0;

    vector<int> v;
    //basically saves the size
    v.reserve(vals.size());
    //add all the keys into a vector
    for(auto const& it: vals)
        v.push_back(it.first);
    //flip the vector so first key is longest
    reverse(v.begin(),v.end());
    for(int x : v) {
        //check if longest is an anagram
        if(findAnagram(vals[x])){
            return x;
        }
    }
    return max;
}

//basically a helper method to get all the same anagrams in line
vector<string> whichAna(string one, vector<string> two){
    vector<string> items;
    //is the first value an anagram with the rest? if so print
    for(string x : two){
        if(isAnagram(one, x)){
            cout << x << endl;
        }
        //otherwise items is everything we don't use
        else{
            items.push_back(x);
        }
    }
    //space bc we are done with one kind of anagram and we return what we haven't used
    cout << endl;
    return items;
    }

//applys whichAna
void printAna(){
    int max=findMax();

    if(max<=0){
        cout << "No anagrams found."<<endl;
    }
    else{
        cout << "Max anagram length: ";
        cout << max << endl;
        vector<string> anagrams=ana_map[max];
        //alphabetized
        sort(anagrams.begin(),anagrams.end());
        anagrams=whichAna(anagrams[0],anagrams);
        //until we have printed all the anagrams of the max length
        while(anagrams.size()>0){
            anagrams=whichAna(anagrams[0],anagrams);
        }
    }

}
//cleanup 
void cleanup() {
    vals.clear();
    ana_map.clear();
}

//NOTE: taken from the how to readfile on the CS385 canvas page
int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <dictionary file>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: File '" << argv[1] << "' not found." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        //unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            vals[line.length()].push_back(line);
            //data.push_back(line);
            ++num_elements;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    //quick check
    if(num_elements<=1){
    	cout << "No anagrams found."<<endl;
    }
    else {
		printAna();
		cleanup();
    }
    return 0;
    cleanup();
}
