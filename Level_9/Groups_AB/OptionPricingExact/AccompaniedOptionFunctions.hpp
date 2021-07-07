/*
This is a file that declares Global Functions that can be called from different Option Classes or Main programs that are not required to be part of a Class's member functions.
Global functions for Option Pricing include:

- d1()
- CalcPutCallParityPrice()
- CheckPutCallParity()
- MeshArray()

*/

#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>	
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include <boost/math/distributions/normal.hpp>
using namespace boost::math;
using namespace std;

#ifndef OPTIONFUNCTIONS_HPP
#define OPTIONFUNCTIONS_HPP

double d1(const double& T, const double& K, const double& S, const double& sig, const double &b);

double CalcPutCallParityPrice(const EuropeanOption& source, const double& price);

bool CheckPutCallParity(const double& CallPrice, const double& PutPrice, const EuropeanOption& option);

vector<double> MeshArray(const double& startValue, const double& interval, const int& size);

#endif