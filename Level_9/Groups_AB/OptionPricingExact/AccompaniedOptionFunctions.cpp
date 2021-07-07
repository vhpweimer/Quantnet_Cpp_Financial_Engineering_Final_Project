/*
This file implements all the global functions declared in AccompaniedOptionFunctions.hpp
*/

#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include "AccompaniedOptionFunctions.hpp"
using namespace boost::math;
using namespace std;


double d1(const double& T, const double& K, const double& S, const double& sig, const double& b) {
	return (log(S / K) + (b + (sig * sig / 2)) * T) / (sig * sqrt(T));
}

double CalcPutCallParityPrice(const EuropeanOption& source, const double& price) {

	if (source.GetType() == 1) {	// Given a Call, calculate Put
		double ParityPutPrice = price + source.GetK() * exp(-source.Getr() * source.GetT()) - source.GetS();
		
		return ParityPutPrice;
	}
	else {							// Given a Put, calculate Call
		double ParityCallPrice = price + source.GetS() - source.GetK() * exp(-source.Getr() * source.GetT());
		
		return ParityCallPrice;
	}
}

bool CheckPutCallParity(double const& CallPrice, double const& PutPrice, const EuropeanOption& source) {
	return CallPrice + source.GetK() * exp(-source.Getr() * source.GetT()) == PutPrice + source.GetS();
}

vector<double> MeshArray(const double& startValue, const double& interval, const int& size) {

	vector<double> mesh;

	mesh.reserve(size);

	for (int i = 0; i != size; i++) {
		mesh.push_back(startValue + interval * i);
	}

	return mesh;
}