/*
This part of the C++ program implements the Option class defined in the header file Option.hpp
The constructors, getters & setters, and the overloaded assignment operator are implemented below
*/

#include <string>	
#include <cmath>	
#include <iostream>
#include <sstream>	
#include "Option.hpp" 
#include "AccompaniedOptionFunctions.hpp"
using namespace std;

Option::Option() : T(0),  K(0), sigma(0), r(0), S(0), b(0), type(1) {}								
Option::Option(const Option& source) : T(source.T), K(source.K), sigma(source.sigma), r(source.r), S(source.S), type(source.type) {} 		
Option::Option(double newK, double newSigma, double newr, double newS, double newb, int newtype) : K(newK), sigma(newSigma), r(newr), S(newS), b(newb), type(newtype) {}	
Option::Option(double newT, double newK, double newSigma, double newr, double newS, double newb, int newtype) : T(newT), K(newK), sigma(newSigma), r(newr), S(newS), b(newb), type(newtype) {}

Option::~Option() {}

void Option::OptionParameters(const double& setT, const double& setK, const double& setsigma, const double& setr, const double& setS, const double& setb, const int& settype) {
	T = setT;
	K = setK;
	sigma = setsigma;
	r = setr;
	S = setS;
	b = setb;
	type = settype;
}

void Option::OptionType(int& settype) {
	type = settype;
}

double Option::GetT() const {
	return T;
}

double Option::GetK() const {
	return K;
}

double Option::Getsig() const {
	return sigma;
}

double Option::Getr() const {
	return r;
}

double Option::GetS() const {
	return S;
}

double Option::Getb() const {
	return b;
}

int Option::GetType() const {
	return type;
}

std::string Option::Print() const {							
	std::stringstream temp;									
	temp << GetType() << " Option(Time to maturity: " << GetT() << ", Strike Price: " << GetK() << ", sigma: " << Getsig() << ", risk free rate: " << Getr() << ", Stock Price: " << GetS() << ")";
	return temp.str();										
}

// Overloaded Operators

Option& Option::operator = (const Option& source) {

	// Avoid doing assign to myself
	if (this == &source)
		return *this;

	T = source.T;
	K = source.K;
	sigma = source.sigma;
	r = source.r;
	S = source.S;
	b = source.b;
	type = source.type;
	
	return *this;
}