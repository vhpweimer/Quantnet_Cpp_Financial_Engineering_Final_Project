/*
This file implements all the public member function declared in PerpetualAmericanOption.hpp
*/

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>	
#include "AccompaniedOptionFunctions.hpp"
#include "EuropeanOption.hpp"

PerpetualAmericanOption::PerpetualAmericanOption() : Option() {}						// Invoke Base Default Constructor						
PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& source) : Option(source) {} 	// Invoke Base Copy Constructor 
PerpetualAmericanOption::PerpetualAmericanOption(double newK, double newSigma, double newr, double newS, double newb, int newtype) : Option(newK, newSigma, newr, newS, newb, newtype) {}	// Invoke Base Parameterized Constructor 

PerpetualAmericanOption::~PerpetualAmericanOption() {}

double PerpetualAmericanOption::CalcOptionPrice() {

	double price = 0;
	double sigsquared = sigma * sigma;
	double fac = b / sigsquared - 0.5; fac *= fac;

	double y1 = 0.5 - b / sigsquared + sqrt(fac + 2.0 * r / sigsquared);
	double y2 = 0.5 - b / sigsquared - sqrt(fac + 2.0 * r / sigsquared);

	if (1.0 == y1)
		return S;

	double fac2 = ((y1 - 1.0) * S) / (y1 * K);
	double fac3 = ((y2 - 1.0) * S) / (y2 * K);

	if (type == 1) {							// Calculate Option given a Call
		price = K * pow(fac2, y1) / (y1 - 1.0); 
	}
	else {									// Calculate Option given a Put
		price = K * pow(fac3, y2) / (1.0 - y2); 
	}

	return price;							
}

double PerpetualAmericanOption::CalcOptionPrice(const double& newS) { 

	double price = 0;
	double sigsquared = sigma * sigma;
	double fac = b / sigsquared - 0.5; fac *= fac;

	double y1 = 0.5 - b / sigsquared + sqrt(fac + 2.0 * r / sigsquared);
	double y2 = 0.5 - b / sigsquared - sqrt(fac + 2.0 * r / sigsquared);

	if (1.0 == y1)
		return newS;

	double fac2 = ((y1 - 1.0) * newS) / (y1 * K);
	double fac3 = ((y2 - 1.0) * newS) / (y2 * K);

	if (type == 1) {							// Calculate Option given a Call
		price = K * pow(fac2, y1) / (y1 - 1.0);	
	}
	else {										// Calculate Option given a Put
		price = K * pow(fac3, y2) / (1.0 - y2);	
	}

	return price;							
}

std::string PerpetualAmericanOption::Print() const {						
	std::stringstream temp;														
	temp << GetType() << " Option(Strike Price: " << GetK() << ", sigma: " << Getsig() << ", risk free rate: " << Getsig() << ", Stock Price: " << GetS() << ")";
	return temp.str();														
}

void PerpetualAmericanOption::RangeofOptionPrices(const double& startValue, const double& interval, const int& size) {

	vector<double> RangeofS = MeshArray(startValue, interval, size);
	vector<double> OptionPrices;

	for (int i = 0; i != size; i++) {
		OptionPrices.push_back(CalcOptionPrice(RangeofS[i]));
		cout << "Underlying Stock Price: " << RangeofS[i] << ", Option Price: " << OptionPrices[i] << endl;
	}
}

// RangeofOptionPrices -- Matrix
void PerpetualAmericanOption::RangeofOptionPrices(const vector<vector<double>>& source) {

	vector<double> optionPrices;

	for (unsigned int i = 0; i < source.size(); i++) {

		K = source[i][0];
		sigma = source[i][1];
		r = source[i][2];
		S = source[i][3];
		b = source[i][4];
		type = (int)source[i][5];

		optionPrices.push_back(CalcOptionPrice());
	}

	for (unsigned int i = 0; i < optionPrices.size(); i++) {
		cout << "Option " << i + 1 << ", Price: " << optionPrices[i] << ", Type: " << source[i][5] << endl;
	}
}

// Implement Overloaded Operators

PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& source) {

	// Avoid doing assign to myself
	if (this == &source)
		return *this;

	// Call Base Class Assignment Operator
	Option::operator = (source);
	
	return *this;
}
