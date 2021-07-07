/*
This is a C++ program that tests Option Pricing Exact methods. 

The following functionality is tested for European and American Options:

- Implemented Black Scholes formulae to calculate Call and Put prices
- The Greeks (Gamma, Delta etc)
- The Greeks - Approximate Delta and Gamma
- Calculate option for a range of S
- Matrix pricing 
*/

#include <iostream>
#include <string>
#include <vector>
#include "PerpetualAmericanOption.hpp"
#include "EuropeanOption.hpp"
#include "AccompaniedOptionFunctions.hpp"

using namespace std;

// Implement 4 batches in double vectors 
//								T     K     sig   r    S							
std::vector<double> Batch1 = { 0.25, 65.0, 0.3, 0.08, 60.0};
std::vector<double> Batch2 = { 1.0, 100.0, 0.2, 0.0, 100.0};
std::vector<double> Batch3 = { 1.0, 10.0, 0.5, 0.12, 5.0 };
std::vector<double> Batch4 = { 30.0, 100.0, 0.3, 0.08, 100.0 };
std::vector<double> Batch5 = { 1.45, 120.0, 0.51, 0.045, 108.0 };

int main() {

	// Declare and initialize T, K, sig, r, S -- Switch Batch number for using a different batch
	double T = Batch5[0];
	double K = Batch5[1];
	double sig = Batch5[2];
	double r = Batch5[3];
	double S = Batch5[4];
	double b = 0;							// Set b=r in case of Stock Options
	int EuroOptionTypeC = 1;
	int EuroOptionTypeP = -1;

	// Printing message to screen
	// Pricing European Options 
	cout << " *** Pricing European Options *** " << endl << endl;
	std::cout << "Batch 5: " << endl;

	cout << "Option Types: " << "\n"
		<< "1: Call" "\n"
		<< "-1: Put" << endl << endl;
	
	// Part 1 //
	
	// Declare and initiate europeanOption object - Call
	EuropeanOption europeanOptionCall(T, K, sig, r, S, b, EuroOptionTypeC);

	// Declare and initiate europeanOption object - Put
	EuropeanOption europeanOptionPut(T, K, sig, r, S, b, EuroOptionTypeP);

	cout << europeanOptionCall.Print() << endl;

	// Calculate Call Price and Print to screen
	double EuropeanOptionCallPrice = europeanOptionCall.CalcOptionPrice(S);
	cout << "Call price for European Option: " << EuropeanOptionCallPrice << endl << endl;

	cout << europeanOptionPut.Print() << endl;

	// Call CalcPutPrice() Function
	double EuropeanOptionPutPrice = europeanOptionPut.CalcOptionPrice(S);
	cout << "Put price for European Option: " << EuropeanOptionPutPrice << endl;

	cout << endl << "Calculating Put-Call Parity prices for European Options" << endl << endl;

	cout << "Parity Put Price: " << CalcPutCallParityPrice(europeanOptionCall, EuropeanOptionCallPrice) << endl;

	cout << "Parity Call Price: " << CalcPutCallParityPrice(europeanOptionPut, EuropeanOptionPutPrice) << endl;

	// Second method to check if Put-Call Parity holds with Formula
	cout << "Put-Call Parity of this Option Holds: " << CheckPutCallParity(EuropeanOptionCallPrice, EuropeanOptionPutPrice, europeanOptionCall) << endl;

	cout << endl << "Generating multiple Call and Put Option prices utilizing a range of underlying stock values of S " << endl << endl;

	cout << "Range of Option Prices for a Call Option" << endl;
	europeanOptionCall.RangeofOptionPrices(0.0, 5.0, 15);

	cout << endl << "Range of Option Prices for a Put Option" << endl;
	europeanOptionPut.RangeofOptionPrices(0.0, 5.0, 15);

	// Create matrix - Everything Constant except for S
	vector<vector<double>> matrix_of_options = { 
		{ 0.25, 65.0, 0.3, 0.08, 60.0, 0.08, 1},
		{ 0.25, 65.0, 0.3, 0.08, 61.0, 0.08, 1},
		{ 0.25, 65.0, 0.3, 0.08, 62.0, 0.08, -1},
		{ 0.25, 65.0, 0.3, 0.08, 63.0, 0.08, -1},
		{ 0.25, 65.0, 0.3, 0.08, 64.0, 0.08, 1} 
	};

	// Create matrix - Everything Constant except for T
	vector<vector<double>> matrix_of_options_T = {
		{ 0.10, 65.0, 0.3, 0.08, 60.0, 0.08, 1},
		{ 0.25, 65.0, 0.3, 0.08, 60.0, 0.08, 1},
		{ 0.50, 65.0, 0.3, 0.08, 60.0, 0.08, 1},
		{ 1, 65.0, 0.3, 0.08, 60.0, 0.08, 1},
		{ 2, 65.0, 0.3, 0.08, 60.0, 0.08, 1}
	};
 
	EuropeanOption* europeanOption = new EuropeanOption();

	cout << endl << "* Computing a range of Option prices from an inputted matrix of Option paramaters *" << endl << endl;

	// Call rangeofOptionprices with matrix as input to output the option prices
	cout << "Option Prices with increasing value of S" << endl;
	europeanOption->RangeofOptionPrices(matrix_of_options, "Option");
	cout << endl;
	cout << "Option Prices with increasing value of T" << endl;
	europeanOption->RangeofOptionPrices(matrix_of_options_T, "Option");

	delete europeanOption;

	// Part 2 - OPTION SENSITIVITIES // 

	// Calculate Delta and Gamma for a Call and Put Option
	// Parameters: K=100, S=105, T=0.5, r=0.1, b=0, sig=0.36
	cout << endl << "*** Option Sensitivities aka the Greeks *** " << endl << endl;
	cout << "Calculating Delta & Gamma." << endl << endl;

	EuropeanOption europeanOptionCall2;
	EuropeanOption europeanOptionPut2;

	// Option Parameter Variables
	double T2 = 1.45;
	double K2 = 120;
	double sig2 = 0.51;
	double r2 = 0.045;
	double S2 = 108;
	double b2 = 0;							

	europeanOptionCall2.OptionParameters(T2, K2, sig2, r2, S2, b2, 1);
	europeanOptionPut2.OptionParameters(T2, K2, sig2, r2, S2, b2, -1);

	// Print Delta and Approximate Delta
	cout << "Delta for Call Option : " << europeanOptionCall2.Delta(S2) << endl;
	cout << "Delta for Put Option : " << europeanOptionPut2.Delta(S2) << endl;
	cout << "Gamma for Call&Put Option : " << europeanOptionCall2.Gamma() << endl;

	// Compute Call Delta Price for a monotinically increasing range of underlying values of S
	cout << endl << "Calculating Call Delta values for European Options for a range of underlying values of S " << endl << endl;

	// Call RangeofDeltas() function and input parameters
	europeanOptionCall2.RangeofDeltas(50, 5, 25); // Start at S of 25, take steps of 5 (h) and take 25 steps

	// Matrix Delta and Gamma

	EuropeanOption* europeanOption2 = new EuropeanOption();
	cout << endl << "* Computing a range of Deltas and Gammas from an inputted matrix of Option paramaters *" << endl << endl;

	// Call rangeofOptionprices with matrix as input to output the option prices
	europeanOption2->RangeofOptionPrices(matrix_of_options, "Delta");
	cout << endl;
	europeanOption2->RangeofOptionPrices(matrix_of_options, "Gamma");

	delete europeanOption2;

	cout << endl << "* Use divided differences to approximate option sensitivities *" << endl << endl;

	// Calculate Approximate Deltas and Gamma for a fixed value of S and h
	cout << "Approximate Delta for Call Option : " << europeanOptionCall2.ApproximateDelta(S2, 0.0005) << endl;
	cout << "Approximate Delta for Put Option : " << europeanOptionPut2.ApproximateDelta(S2, 0.0005) << endl;
	cout << "Approximate Gamma for Call&Put Option : " << europeanOptionCall2.ApproximateGamma(S2, 0.0005) << endl;

	// Calculate Approximate Call Deltas for an increasing underlying values of S and h
	cout << endl << "Calculating Approximate Call Delta values for European Options for a range of underlying values of S and h" << endl << endl;

	// Call RangeofDeltas() function and input parameters
	europeanOptionCall2.RangeofDeltas(50, 5, 0.005, 0.1, 25); // Start at S of 50, take steps of 5 (h) and take 25 steps. For h start at 0.005

	// Part B: Testing American Options 
	cout << endl << " *** Pricing American Options *** " << endl << endl;

	// Create object perpAmericanOptionCall
	int TypeC = 1;
	PerpetualAmericanOption perpAmericanOptionCall(100.0, 0.1, 0.1, 110.0, 0.02, TypeC);

	// Create object perpAmericanOptionPut
	int TypeP = -1;
	PerpetualAmericanOption perpAmericanOptionPut(100.0, 0.1, 0.1, 110.0, 0.02, TypeP);

	// Call CalcCallPrice() Function
	cout << perpAmericanOptionCall.Print() << endl;
	cout << "Call price for Perpetual American Option: " << perpAmericanOptionCall.CalcOptionPrice(110) << endl << endl;
	
	cout << perpAmericanOptionPut.Print() << endl;
	cout << "Put price for Perpetual American Option: " << perpAmericanOptionPut.CalcOptionPrice(110) << endl;


	// Compute call and put option price for a monotonically increasing range of underlying values of S
	cout << endl << "Calculating Call and Put prices for Perpetual American Options for a range of underlying values of S " << endl << endl;

	// Call RangeofOptionPrices() function and input parameters
	cout << "Range of Option Prices for a Call Option" << endl;
	perpAmericanOptionCall.RangeofOptionPrices(5, 5, 25);

	// Call RangeofOptionPrices() function and input parameters
	cout << endl << "Range of Option Prices for a Put Option" << endl;
	perpAmericanOptionPut.RangeofOptionPrices(5, 5, 25);

	// Create a Matrix of Options and input that into a function

	// Create matrix - Everything constant except for S
	vector<vector<double>> matrix_of_options_us = {
		{ 100.0, 0.1, 0.1, 110.0, 0.02, 1},
		{ 100.0, 0.1, 0.1, 111.0, 0.02, 1},
		{ 100.0, 0.1, 0.1, 112.0, 0.02, -1},
		{ 100.0, 0.1, 0.1, 113.0, 0.02, -1},
		{ 100.0, 0.1, 0.1, 114.0, 0.02, 1}
	};
 
	PerpetualAmericanOption* americanOption = new PerpetualAmericanOption();

	cout << endl << "* Computing a range of Option prices from an inputted matrix of Option paramaters *" << endl << endl;

	// Call rangeofOptionprices with matrix as input to output the option prices
	americanOption->RangeofOptionPrices(matrix_of_options_us);

	delete americanOption;

	return 0;
}