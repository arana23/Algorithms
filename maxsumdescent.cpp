/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Aparajita Rana
 * Version     : 1.0
 * Date        : 04/21/2020
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */

//check if its all single dig or not
bool checker(){
    for(int i=0; i<num_rows;i++)
    {
        for(int j=0; j<i+1;j++)
        {
            if(values[i][j]>=10){
                return false;
            }
        }
    }
    return true;
}

void display_table() {
    // TODO
    //print out the values in the format of a right triangle
    //cout << temp;

    //its all single digits
    if(checker()){
    for(int i=0; i<num_rows;i++)
    {
        for(int j=0; j<i+1;j++)
        {
            //if its NOT the last val -> needs a space after still
            if(j+1!=i+1){
                    cout << to_string(values[i][j]);
                    cout << " ";
            }
            //it is the last value -> same stuff as above but don't add space in
            else{
                cout << to_string(values[i][j]);
            }
        }
        //next line of nums
        cout <<"\n";
    }
    }
    else{
    for(int i=0; i<num_rows;i++)
    {
        for(int j=0; j<i+1;j++)
        {
            //if its NOT the last val -> needs a space after still
            if(j+1!=i+1){
                //if the number is a single digit (less than 10), right allign by adding " "
                if(values[i][j]<10){
                    cout << " ";
                    cout << to_string(values[i][j]);
                    cout << " ";
                }
                else{
                    cout << to_string(values[i][j]);
                    cout << " ";
                }
            }
            //it is the last value -> same stuff as above but don't add space in
            else{
                if(values[i][j]<10){
                    cout << " ";
                    cout << to_string(values[i][j]);
                }
                else{
                cout << to_string(values[i][j]);
                }
            }
        }
        //next line of nums
        cout <<"\n";
    }
}
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    int max_sum=0;
    //Base cases: check for empty, 1, or 2!
    if(num_rows<1){
        return max_sum;
    }

    if(num_rows==1){
        return values[0][0];
    }
    //this outlines a simplier version of the actual algorithm
    if(num_rows==2){
        sums[1][1] = values[1][1] + values[0][0]; 
        sums[1][0] = values[1][0] + values[0][0]; 
        if(sums[1][1]>=sums[1][0])
            return sums[1][1];
        return sums[1][0];
    }

    else{
        //default start out by adding the first vals
        sums[1][1] = values[1][1] + values[0][0]; 
        sums[1][0] = values[1][0] + values[0][0]; 

    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).
        for(int i = 2; i < num_rows; i++) { 
            //inital vals
            sums[i][0] = values[i][0] + sums[i-1][0]; 
            sums[i][i] = values[i][i] + sums[i-1][i-1]; 
      
            //fill in all the empty spaces/columns between ^ those nums
            for (int j = 1; j < i; j++){ 
                if (values[i][j] + sums[i-1][j-1] >= values[i][j] + sums[i-1][j]){
                    sums[i][j] = values[i][j] + sums[i-1][j-1];
                } 
                else
                    sums[i][j] = values[i][j]+sums[i-1][j]; 
            } 
        } 

    // Everything is filled -> Loop over the last row to find the max value -> thats the max sum.
    int max_sum=sums[num_rows-1][0]; 
      
    for(int i=1;i<num_rows;i++) 
    { 
        if(max_sum < sums[num_rows-1][i]) {
            max_sum = sums[num_rows-1][i]; 
        }
    } 

    // Return the max sum.
    return max_sum; 
    }
    return 0;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */

vector<int> backtrack_solution() {
    vector<int> solution;
    // TODO
    //start out by getting the loc of the max of vals

    //some base cases
    if(num_rows<1){
        return solution;
    }

    if(num_rows==1){
        //insert takes (loc, val) -> we use .begin() so it pushes to da top
        solution.insert(solution.begin(),(values[0][0]));
        return solution;
    }

    else{
    //copied the code from above max method -> instead of returning max value we save the location
    int max_sum=sums[num_rows-1][0]; 
    int loc=0;
      
    for(int i=1;i<num_rows;i++) 
    { 
        if(max_sum<sums[num_rows-1][i]) {
             max_sum=sums[num_rows-1][i]; 
             loc=i;
        }
    } 
    //push that max into the sol vector
    solution.insert(solution.begin(),values[num_rows-1][loc]);

    //slighty edited max method above to go backwards
    for (int i = num_rows-1; i > 1; i--){ 
            //if either values loc is a zero that means it DNE so set to the other
            if(values[i-1][loc-1]==0){
                solution.insert(solution.begin(),values[i-1][loc]);
            }
            else if(values[i-1][loc]==0){
                solution.insert(solution.begin(),values[i-1][loc-1]);
                //we moved to the left so move loc
                loc-=1;
            }
            //compare! EDIT: > instead of >= to make preference the directly above val
            else if (sums[i][loc] + sums[i-1][loc-1] > sums[i][loc] + sums[i-1][loc])
            {
                solution.insert(solution.begin(),values[i-1][loc-1]);
                //used
                loc-=1;
            } 
            else
                solution.insert(solution.begin(),values[i-1][loc]); 
        }
    //add in the first val bc we did nums_rows-1
    solution.insert(solution.begin(),values[0][0]);

    return solution;
    }
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    // TODO
    //sets the row amount
    values=new int*[data.size()];
    sums=new int*[data.size()];
    num_rows=data.size();
    //x & y are going to be our locations of values and sums -> comparable to what wed use in a nested for loop
    int x=0; int y=0;

    //go through the data till the end
    for (auto it = data.begin(); it != data.end(); ++it) {
        stringstream stream(*it);

        //inputs each number into line_nums -> seperates into individual num
        //comparable to .split() in java
        vector<int> line_nums((istream_iterator<int>(stream)),(istream_iterator<int>()));

        //sets the col amount
        values[x]=new int[line_nums.size()];
        sums[x]=new int[line_nums.size()];

        //inserts each int into values
        for (auto it2 = line_nums.begin(); it2 != line_nums.end(); ++it2) {
            values[x][y]=line_nums[y];
            //cout << values[x][y] << endl;
            y++;
        }
        y=0;
        x++;
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    // TODO
   for(int i=0; i<num_rows;i++)
   {
    delete[] values[i];
    delete[] sums[i];
   }

   delete[] values;
   delete[] sums;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    // TODO
    if(load_values_from_file(filename)){
        display_table();
        cout << "Max sum: ";
        cout<< compute_max_sum()<<endl;
        //backtrack returns a vector so we have to output accordingly not just cout
        vector<int> path=backtrack_solution();
        cout << "Values: [";
        for(vector<int>::const_iterator i = path.begin(); i != path.end(); ++i){
            if(i+1!=path.end()){
                cout << *i << ", ";
            }
            else{
                cout << *i;
            }
        }
        cout << "]";
        cout<<endl;
        cleanup();
    }

    return 0;
}
