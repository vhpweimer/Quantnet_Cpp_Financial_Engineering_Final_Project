/*
This file implements all the public member functions declared in EuropeanOption.hpp
*/

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>	
#include "EuropeanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include "AccompaniedOptionFunctions.hpp"
using namespace boost::math;


EuropeanOption::EuropeanOption() : Option() {}				// Invoke Base Default Constructor						
EuropeanOption::EuropeanOption(const EuropeanOption& source) : Option(source) {} // Invoke Base Copy Constructor 
EuropeanOption::EuropeanOption(double newT, double newK, double newSigma, double newr, double newS, double newb, int newtype) : Option(newT, newK, newSigma, newr, newS, newb, newtype) {}	// Invoke Base Parameterized Constructor 

EuropeanOption::~EuropeanOption() {}

double EuropeanOption::CalcOptionPrice() { 

	double price;
	double d1val;
	double d2val;

	normal_distribution<> N(0.0, 1.0);

	d1val = d1(T, K, S, sigma, b);
	d2val = d1val - sigma * sqrt(T);

	if (type == 1) {
		price = S * exp((b - r) * T) * cdf(N, d1val) - K * exp(-r * T) * cdf(N, d2val);		// Price for Call option
	}
	else {
		price = K * exp(-r * T) * cdf(N, -d2val) - S * exp((b - r) * T) * cdf(N, -d1val);	// Price for Put option
	}

	return price;
}

double EuropeanOption::CalcOptionPrice(const double& newS) { // Dividend q = r - b
															   															   
	double price;
	double d1val;
	double d2val;			

	normal_distribution<> N(0.0, 1.0);	

	d1val = d1(T, K, newS, sigma, b);
	d2val = d1val - sigma * sqrt(T);

	// Implement formulas to calculate Option Prices for Put and Calls depending on optiontype
	if (type == 1) {	
		price = newS * exp((b - r) * T) * cdf(N, d1val) - K * exp(-r * T) * cdf(N, d2val);	// Price for Call option
	}
	else {           
		price = K * exp(-r * T) * cdf(N, -d2val) - newS * exp((b - r) * T) * cdf(N, -d1val);	// Price for Put option
	}
	
	return price;
}

// Implement Option Vector and Matric member functions
void EuropeanOption::RangeofOptionPrices(const double& startValue, const double& interval, const int& size) {

	vector<double> RangeofS = MeshArray(startValue, interval, size);
	vector<double> OptionCallPrices;

	for (int i = 0; i != size; i++) {
		OptionCallPrices.push_back(CalcOptionPrice(RangeofS[i]));

		cout << "Underlying Stock Price: " << RangeofS[i] << ", Option Price: " << OptionCallPrices[i]<< endl;
	}
}

void EuropeanOption::RangeofOptionPrices(const vector<vector<double>>& source, const std::string& stringtype) {

	vector<double> optionPrices;
	
	for (unsigned int i = 0; i < source.size(); i++) {
		T = source[i][0];
		K = source[i][1];
		sigma = source[i][2];
		r = source[i][3];
		S = source[i][4];
		b = source[i][5];
		type = (int)source[i][6];

		// Push back array depending on what type is required - Option, Delta or Gamma
		if (stringtype == "Option") {
			optionPrices.push_back(CalcOptionPrice());
		} 
		else if (stringtype == "Delta") {
			optionPrices.push_back(Delta());
		} 
		else {
			optionPrices.push_back(Gamma());
		}
	}

	for (unsigned int i = 0; i < optionPrices.size(); i++) {
		
		// Print price of each option depending on what type is given
		if (stringtype == "Option") {
			cout << "Option " << i + 1 << ", Price: " << optionPrices[i] << ", Type: " << source[i][6] << endl;
		}
		else if (stringtype == "Delta") {
			cout << "Option " << i + 1 << ", Delta: " << optionPrices[i] << ", Type: " << source[i][6] << endl;
		}
		else {
			cout << "Option " << i + 1 << ", Gamma: " << optionPrices[i] << ", Type: " << source[i][6] << endl;
		}
	}
}

void EuropeanOption::RangeofDeltas(const double& startValue, const double& interval, const int& size) {

	vector<double> RangeofSGreeks = MeshArray(startValue, interval, size);
	vector<double> optionCallDeltas;

	for (int i = 0; i != size; i++) {
		optionCallDeltas.push_back(Delta(RangeofSGreeks[i]));
		cout << "Underlying Stock Price: " << RangeofSGreeks[i] << ", Call Delta Price: " << optionCallDeltas[i] << endl;
	}
}

void EuropeanOption::RangeofDeltas(const double& startValue, const double& interval, const double& startValueh, const double& intervalh, const int& size) {

	// Initialize a vector of doubles for Underlying Stock Prices
	vector<double> RangeofSGreeks = MeshArray(startValue, interval, size);
	vector<double> Rangeofh = MeshArray(startValueh, intervalh, size);
	vector<double> optionCallDeltas;

	for (int i = 0; i != size; i++) {
		optionCallDeltas.push_back(ApproximateDelta(RangeofSGreeks[i], Rangeofh[i]));
		cout << "Underlying Stock Price: " << RangeofSGreeks[i] << ", Call Delta Price: " << optionCallDeltas[i] << ", h: "<< Rangeofh[i] << endl;
	}
}

// Implement Greeks

// Delta  
double EuropeanOption::Delta() {

	double delta;
	normal_distribution<> N(0.0, 1.0);
	double d1val = d1(T, K, S, sigma, b);

	// Calculate Delta depending on Put or Call
	if (type == 1) {						// Calculate Delta given a Call
		delta = exp((b - r) * T) * cdf(N, d1val);
	}
	else {											// Calculate Delta given a Put
		delta = -exp((b - r) * T) * cdf(N, -d1val);
	}

	return delta;									
}

// Delta - With S argument 
double EuropeanOption::Delta(const double& newS) {

	double delta;
	normal_distribution<> N(0.0, 1.0);
	double d1val = d1(T, K, newS, sigma, b);

	// Calculate Delta depending on Put or Call
	if (type == 1) {						// Calculate Delta given a Call
		delta  = exp((b - r) * T) * cdf(N, d1val);
	}
	else {											// Calculate Delta given a Put
		delta = -exp((b - r) * T) * cdf(N, -d1val);
	}
	
	return delta;								
}

double EuropeanOption::Gamma() {

	double gamma;
	normal_distribution<> N(0.0, 1.0);

	double d1val = d1(T, K, S, sigma, b);
	
	gamma = (pdf(N, d1val) * exp((b - r) * T)) / (S * sigma * sqrt(T));

	return gamma;
}

// Approximate Delta
double EuropeanOption::ApproximateDelta(const double& newS, const double& h) {

	// Apply formula to calculate Approx. Delta
	double approxDeltaPrice = (CalcOptionPrice(newS + h) - CalcOptionPrice(newS - h)) / (2 * h);

	return approxDeltaPrice;
}

// Approximate Gamma
double EuropeanOption::ApproximateGamma(const double& newS, const double& h) {
	
	// Apply formula to calculate Approx. Gamma
	double approxGammaPrice = (CalcOptionPrice(newS + h) - 2 * CalcOptionPrice(newS) + CalcOptionPrice(newS - h)) / (h * h);

	return approxGammaPrice;
}

// Implement Overloaded Operators
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source) {

	// Avoid doing assign to myself
	if (this == &source)
		return *this;

	Option::operator = (source);

	return *this;
}
