/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Aparajita Rana
 * Date        : 02/23/2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    //Returns a vector of vectors of ints representing different combinations of 
    //ways to climb stairs, moving up either 1, 2, or 3 stairs at a time.
    
    vector< vector <int> > w;
	vector< vector <int> > r;
    
    //if stair # is less than = to zero, push on val
	if(num_stairs<=0)
    {
		w.push_back(vector<int>());
		return w;
	}
    //otherwise find combo
    else
    {
		for(int x=1;x<=3;x++)
        {
			if(num_stairs>=x)
            {
				r=get_ways(num_stairs-x);
				for(unsigned int y=0;y<r.size();y++)
                {
					r[y].push_back(x);
					w.push_back(r[y]);
				}
			}
		}
		return w;
	}
}

void display_ways(const vector< vector<int> > &ways) {
    //Displays the ways to climb stairs by iterating over the vector of vectors and //printing each combination.
    unsigned int val;
	int temp;

    //iterate through ways and determine temp accordingly
	for(unsigned int x=0;x<ways.size();x++)
    {
		temp=ways.size();
		val=1;
        
		while(temp>=10)
        {
			val++;
			temp=temp/10;
		}
        
		cout << setw(val) << x+1 << ". " << "[";
        
        //iterate through loop and display different pathways
		for(unsigned int y = ways[x].size() - 1; y >= 1; y--)
        {
			cout << ways[x][y] << ", ";
		}
        
		cout << ways[x][0] << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
    
    int lim;
    istringstream iss;
    
    //check if argc is not equal to 2, if so return
	if(argc != 2)
    {
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
    
    //get argv[1] now after passing first if statement
    iss.str(argv[1]);
    
    //check if stairs are below zero (negative)
    if ( !(iss >> lim) || lim < 1) 
    {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    
    //having gotten to this point, lim is a valid amount
    // apply get_ways and determines # ways
    vector< vector<int> > val = get_ways(lim);
    if(lim == 1)
    {
        cout << lim << " way to climb " << lim << " stair." << endl;
    }
    
    else
    {
        cout << val.size() << " ways to climb " << lim << " stairs." << endl;
    }
    
    display_ways(val);
    iss.clear();
    return 0;
}
