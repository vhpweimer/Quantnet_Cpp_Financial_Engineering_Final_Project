/*
Option Class - Base Class

This is a base Option Class that includes private data members and public member function that other Derived Option Classes (European Style, American Style, Exotic Options)
can inherit functionality from. The following private data members and public member functions are included in the Base class.

Private:
 
 - T: Time to maturity
 - K: Strike Price
 - sigma: Volatility
 - r: Risk Free Rate
 - S: Underlying stock price
 - b: Cost of carry
 - type: Type of Option (Call or Put)

 Public:
 - Constructors
 - Destructor
 - CalcOptionPrice: Pure Virtual function (Makes Class Abstract)
 - Getters for OptionType and Parameters
 - Setters for OptionType and Parameters
 - Overloaded assignment Operators
*/

#include <string>
#include <iostream>

#ifndef OPTION_HPP
#define OPTION_HPP

class Option {

protected:

	double T;											// Time to maturity
	double K;											// Strike Price
	double sigma;										// Volatility
	double r;											// Risk Free Rate
	double S;											// Underlying stock price

	double b;											// Cost of Carry

	int type;											// Type of Option - Put or Call

public: 

	Option();																			 // Default Constructor
	Option(const Option& source);														 // Copy Constructor
	Option(double newK, double newSigma, double newr, double newS, double newb, int newtype); // Parameterized Constructor without T
	Option(double newT, double newK, double newSigma, double newr, double newS, double newb, int newtype); // Parameterized Constructor with T 

	virtual ~Option();

	virtual double CalcOptionPrice(const double& newS) = 0; // Takes in S parameter
	virtual double CalcOptionPrice() = 0; // No arguments required

	virtual void OptionParameters(const double& setT, const double& setK, const double& setsigma, const double& setr, const double& setS, const double& setb, const int& settype);
	
	void OptionType(int& settype);

	double GetT() const;
	double GetK() const;
	double Getsig() const;
	double Getr() const;
	double GetS() const;
	double Getb() const;
	int GetType() const;
	
	virtual std::string Print() const;

	Option& operator = (const Option& source);
};

#endif