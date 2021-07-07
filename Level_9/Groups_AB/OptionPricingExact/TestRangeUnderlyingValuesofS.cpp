#include "ExcelDriverLite.hpp"
//#include "Utilities.hpp"
#include "EuropeanOption.hpp"
#include "AccompaniedOptionFunctions.hpp"


#include <cmath>
#include <list>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Implement 4 batches in double vectors 
// Batch 1						T     K     sig   r    S							
std::vector<double> Batch1 = { 0.25, 65.0, 0.3, 0.08, 60.0 };
// Batch 2
std::vector<double> Batch2 = { 1.0, 100.0, 0.2, 0.0, 100.0 };
// Batch 3
std::vector<double> Batch3 = { 1.0, 10.0, 0.5, 0.12, 5.0 };
// Batch 4
std::vector<double> Batch4 = { 30.0, 100.0, 0.3, 0.08, 100.0 };

int main() {
	// DON'T FORGET TO MODIFY EXCELIMPORTS.CPP for correct version of Excel.

	// Declare and initialize T, K, sig, r, S  -- Switch Batch number if want to use a different batch
	double T = Batch1[0];
	double K = Batch1[1];
	double sig = Batch1[2];
	double r = Batch1[3];
	double S = Batch1[4];
	double b = r;							// Set b=r in case of Stock Options
	int EuroOptionTypeC = 1;
	int EuroOptionTypeP = -1;

	// Printing message to screen
	// Pricing European Options 
	cout << " *** Pricing European Options *** " << endl << endl;
	std::cout << "Batch 1: " << endl;

	// Declare and initiate europeanOption object - Call
	EuropeanOption europeanOptionCall(T, K, sig, r, S, b, EuroOptionTypeC);

	// Declare and initiate europeanOption object - Put
	EuropeanOption europeanOptionPut(T, K, sig, r, S, b, EuroOptionTypeP);

	// Declare and initialize size
	unsigned int size = 150;

	// Initialize a vector of doubles for Underlying Stock Prices -- Values to be inputted are startvalue, interval, and size
	auto x = MeshArray(0, 1, size);

	// Create Vectors to store Option prices in
	vector<double> OptionCallPrices;
	vector<double> OptionPutPrices;

	cout << endl << "Producing multiple Option prices using a range of underlying Stock values of S " << endl << endl;
	
	for (int i = 0; i != size; i++) {
		OptionCallPrices.push_back(europeanOptionCall.CalcOptionPrice(x[i]));
		OptionPutPrices.push_back(europeanOptionPut.CalcOptionPrice(x[i]));
	}
	
	// Print message
	cout << endl << "Starting Excel.." << endl;

	ExcelDriver xl; xl.MakeVisible(true);
	xl.CreateChart(x, OptionCallPrices, "Call");
	xl.CreateChart(x, OptionPutPrices, "Put");

	// C++11 style initializer lists
	// std::list<std::string> labels{ "x^2", "x^3" };
	std::list<std::string> labels;
	labels.push_back("Call");
	labels.push_back("Put");

	// C++11 style initializer lists
	// std::list<std::vector<double>> curves{ vec1, vec2 };
	std::list<std::vector<double>> curves;
	curves.push_back(OptionCallPrices);
	curves.push_back(OptionPutPrices);

	// Create Chart
	xl.CreateChart(x, labels, curves, "Option Prices for increasing range of underlying values of S - Batch 1", "S", "Option Price");

	return 0;
}