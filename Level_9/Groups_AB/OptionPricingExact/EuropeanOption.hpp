/*
Derived Class - EuropeanOption

This is a class that is derived from the Base Option Class. 

The Class has the following Private Data Member and Public Member Function functionality:

Private:

/ Inherit from Base class

Public
- Constructors
- Destructor
- Calculate Price
- Greeks (Delta, Gamma, Approximate methods)
- Print() function
- Overloaded Assignment Operator

*/

using namespace std;
#include <cmath>
#include <iostream>
#include <vector>
#include "Option.hpp"
#include <boost/math/distributions/normal.hpp>

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

class EuropeanOption : public Option {

private:
	
public:
	
	EuropeanOption();																										// Default Constructor
	EuropeanOption(const EuropeanOption& source);																			// Copy Constructor
	EuropeanOption(double newT, double newK, double newSigma, double newr, double newS, double newb, int newtype);			// Parameterized Constructor 

	virtual ~EuropeanOption();

	double CalcOptionPrice(const double& newS);
	double CalcOptionPrice();

	void RangeofOptionPrices(const double& startValue, const double& interval, const int& size);
	void RangeofOptionPrices(const vector<vector<double>>& source, const std::string& stringtype);
	void RangeofDeltas(const double& startValue, const double& interval, const int& size);
	void RangeofDeltas(const double& startValue, const double& interval, const double& startValueh, const double& intervalh, const int& size);

	double Delta(const double& newS);								// Delta - With S as argument
	double Delta();													// Delta
	double Gamma();													// Gamma
	double ApproximateDelta(const double& newS, const double& h);	// Approx Delta
	double ApproximateGamma(const double& newS, const double& h);	// Approx Gamma

	EuropeanOption& operator = (const EuropeanOption& source);
};

#endif