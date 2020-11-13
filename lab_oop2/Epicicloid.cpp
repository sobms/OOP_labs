#define _USE_MATH_DEFINES
#include "pch.h"
#include "Epicicloid.h"
#include <iostream>
#include <math.h>
#include <cmath>
#define M_PI 3.141592653589793

namespace epicicloid1 {
	// constructors
	Epicicloid::Epicicloid() : r(1.0), R(1.0), d(1.0), p() {}
	Epicicloid::Epicicloid(const point& p0, double r0, double R0, double d0) : p(p0) {
		if (R0 < 0) { // разделить exeption, сделать для каждого условия+
			throw std::invalid_argument("the negative value of radius R");
		}
		if ((-1) * d0 > R0) {
			throw std::length_error("the negative value of d more then radius R");
		}
		if ((-1) * r0 > R0) {
			throw std::length_error("the negative value of r more then radius R");
		}
		this->R = R0;
		this->d = d0;
		this->r = r0;
	}
	Epicicloid::Epicicloid(double x0, double y0, double r0, double R0, double d0) : p(x0, y0) {
		if (R0 < 0) {
			throw std::invalid_argument("the negative value of radius R");
		}
		if ((-1) * r0 > R0) {
			throw std::length_error("the negative value of r more then radius R");
		}
		if ((-1) * d0 > R0)  {
			throw std::length_error("the negative value of d more then radius R");
		}
		this->R = R0;
		this->d = d0;
		this->r = r0;
	}
	//set'теры
	Epicicloid& Epicicloid::set_r(double r0) {
		if ((-1) * r0 > R) {
			throw std::length_error("the negative value of r more then radius R");
		}
		r = r0;
		return *this;
	}
	Epicicloid& Epicicloid::set_d(double d0) {
		if ((-1) * d0 > R) {
			throw std::length_error("the negative value of d more then radius R");
		}
		d = d0;
		return *this;
	}
	Epicicloid& Epicicloid::set_R(double R0) {
		if (R0 < 0) {
			throw std::invalid_argument("the negative value of radius R");
		}
		R = R0;
		return *this;
	}
	point Epicicloid::get_coordinates(double angle) const {
		point p0;
		const double angle_rad = angle / 180 * M_PI;
		p0.x = p.x + (R + r) * cos(angle_rad) - d * cos((R + r) * angle_rad / r);
		p0.y = p.y + (R + r) * sin(angle_rad) - d * sin((R + r) * angle_rad / r);
		return p0;
	}
	double Epicicloid::get_curv_rad(double angle) const {
		const double angle_rad = angle / 180 * M_PI;         // использовать константу+
		return (R + r) * pow((pow(r, 2) + pow(d, 2) - 2 * d * r * cos(R * angle_rad / r)), 1.5) / abs(pow(r, 3) + pow(d, 2) * (R + r) - d * r * (R + 2 * r) * cos(R * angle_rad / r));
	}
	int Epicicloid::get_type() const { //использовать enum предпочтительнее+
		enum Epicicloid_type {
			Shortened = 1,
			Extended,
			Ordinary
		};
		int type;
		if (d < r) {
			type = Shortened;
		}
		else if (d > r) {
			type = Extended;
		}
		else {
			type = Ordinary;
		}
		return type;
	}
	double Epicicloid::sect_area(double angle) const {
		double angle_rad = angle / 180 * 3.14159;
		return ((R + r) / 2) * ((R + r + pow(d, 2) / r) * angle_rad - d * ((R + 2 * r) / R) * sin(R * angle_rad / r));
	}
	bool Epicicloid::Is_astroid() const {
		return ((r < 0) && (abs(R) == 4 * abs(r)) && (r == d));
	}
}