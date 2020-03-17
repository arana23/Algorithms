/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Aparajita Rana
 * Version : 1.0
 * Date    : January 28, 2020
 * Description : Computes the square root of a double using Newton's method
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
using namespace std;
#include <iomanip>
#include <algorithm>
#include <limits>
#include<istream>
#include <sstream>

double sqrt(double num, double epsilon){

	// given a num less than 0, return nan
	if(num<0){
		return numeric_limits<double>::quiet_NaN();
	}

	//given a num equal to 0 or 1, return the num itself (that is the sqrt)
	if(num==0 || num==1){
		return num;
	}

	//all other cases

	//start out last_guess as a positive number, I choose num but alternative positive numbers work
	double last_guess=num;

	//first application of next_guess calculation displayed in class & on the assignment
	double next_guess=(last_guess + (num/last_guess)) / 2;

	//get as close to epsilon value as possible
	while(!(abs(last_guess - next_guess) <= epsilon)){
		//temp save the guess just used
		last_guess=next_guess;
		//apply the formula to generate next closest guess value
		next_guess = (last_guess + (num/last_guess)) / 2;
	}
	//return the final guess aka closest estimate to the sqrt in double form rounded to 8 decimals
	return next_guess;
}


int main(int argc, char* const argv[]) {
    double m, n;
    istringstream iss;

    //invalid amount of arguments
    if (argc != 2 && argc != 3) {
        cerr << "Usage: ./sqrt <value> [epsilon]"
             << endl;
        return 1;
    }

    //read first value & check if valid double, error if was not
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: Value argument must be a double."
             << endl;
        return 1;
    }
    //clear error
    iss.clear();

    //given 3 arguments, check if the epsilon argument given is valid
    if(argc==3){
    	iss.str(argv[2]);
    	if ( !(iss >> n) ) {
        cerr << "Error: Epsilon argument must be a positive double."
             << endl;
        return 1;
    }
        if(n<=0){
    	cerr << "Error: Epsilon argument must be a positive double."
             << endl;
        return 1;
    }

    }

    //passed all error checking, lets run sqrt on it

    //not given an epsilon value
    if(argc==2){
    	double temp=1e-7;
    	std::cout << std::fixed << std::showpoint;
    	std::cout << std::setprecision(8);
    	std::cout << sqrt(m,temp) << '\n';
    }

    //given an epsilon value
    else if(argc==3){
    	std::cout << std::fixed << std::showpoint;
    	std::cout << std::setprecision(8);
    	std::cout << sqrt(m,n) << '\n';
    }
    return 0;

}