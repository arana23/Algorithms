/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Aparajita Rana 
 * Version     : 1.0
 * Date        : 03/28/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */

long count_inversions_slow(int array[], int length) 
{
    long temp=0;
    for(int x=0; x<length; x++)
    {
        for(int y=x+1; y<length; y++)
        {
            if((array[y]<array[x]))
            {
                temp++;
            }
        }
    }
    return temp;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) 
{
    // TODO
    // Hint: Use mergesort!
    int *temp=new int[length];
    long val=mergesort(array, temp, 0, length-1);
    delete[] temp;
    return val;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	
    long count = 0;
	int center;
    
    //checks low versus high
	if(low<high) 
    {
        //center calc
		center=(low + high)/2; 
        
        //utilize calling mergesort
		count=mergesort(array, scratch, low, center);
		count+=mergesort(array, scratch, center+1, high);
        
        //temp variables
		int l=low;
		int m=center+1;

		for (int i=low; i<=high; i++) 
        {
			if(l<=center && (m>high || array[m]>=array[l])) 
            {
				scratch[i]=array[l];
				l++;
			} 
            
            else 
            {
				scratch[i]=array[m];
				m++;
				count+=(center-l)+1;
			}
		}

		for(int i=low; i<=high; i++) 
        {
			array[i] = scratch[i];
		}
	}

	return count;
}

int main(int argc, char *argv[]) 
{
    
    //parsed command-line argument
    if(argc != 1 && argc != 2) 
    {
		cout  << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
    
	if(argc == 2) 
    {
		string x = argv[1];
		if(x.compare("slow") != 0) 
        {
			cout << "Error: Unrecognized option 'average'." << endl;
			return 1;
		}
	}
    
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    //produced output
    int size=values.size();
    
    if(values.empty()) 
    {
    	cerr << "Error: Sequence of integers not received.";
    	return 1;
    }

    int *v = &values[0];
    
    if(argc==2) 
    {
    	cout << "Number of inversions: " << count_inversions_slow(v, size) << endl;
        return 0;
    }
    else 
    {
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], size) << endl;
        return 0;
    }
    
     if (values.empty()) {
      		cerr << "Error: Sequence of integers not received." << endl;
      		return 1;
      }
      if (argc == 1) {
      		cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
      		return 0;
      }
      else {
      		cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
      		return 0;
      }
    
}
