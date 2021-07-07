/*
Class - PerpetualAmericanOption 

This is a class that is derived from the Base Option Class. Since it's a Perpetual Option, it won't have a parameter T (Time to Maturity).

The Class has the following Private Data Member and Public Member Function functionality:

Private: 

/ Inherit from Base class

Public
- Constructors
- Destructor
- Calculate Price
- Print() function
- Overloaded Assignment Operator 
*/

using namespace std;
#include <cmath>
#include <vector>
#include <iostream>
#include "Option.hpp"

#ifndef PERPAMERICANOPTION_HPP
#define PERPAMERICANOPTION_HPP

class PerpetualAmericanOption : public Option {

public:

	PerpetualAmericanOption();																				// Default Constructor
	PerpetualAmericanOption(const PerpetualAmericanOption& source);											// Copy Constructor
	PerpetualAmericanOption(double newK, double newSigma, double newr, double newS, double	newb, int newtype);	// Parameterized Constructor 

	virtual ~PerpetualAmericanOption();

	double CalcOptionPrice(const double& newS);
	double CalcOptionPrice();

	void RangeofOptionPrices(const double& startValue, const double& interval, const int& size);
	void RangeofOptionPrices(const vector<vector<double>>& source);

	std::string Print() const;

	PerpetualAmericanOption& operator = (const PerpetualAmericanOption& source);
};

#endif

