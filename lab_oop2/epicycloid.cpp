#include "epicycloid.h"
#include <iostream>
#include <math.h>
#include <cmath>

namespace epicicloid1 {
	// constructors
	Epicicloid :: Epicicloid(): r(1.0), R(1.0), d(1.0), p() {}
	Epicicloid::Epicicloid(const point& p0, double r0, double R0, double d0) : p(p0) {
		if ((R0 < 0) || ((-1) * d0 > R0) || ((-1) * r0 > R0)) {
			throw std::exception("invalid value");
		}
		this->R = R0;
		this->d = d0;
		this->r = r0;
	}
	Epicicloid::Epicicloid(double x0, double y0, double r0, double R0, double d0) : p(x0,y0) {
		if ((R0 < 0) || ((-1) * d0 > R0) || ((-1) * r0 > R0)) {
			throw std::exception("invalid value");
		}
		this->R = R0;
		this->d = d0;
		this->r = r0;
	}
	//set'теры
	Epicicloid& Epicicloid::set_r(double r0) {
		if ((-1) * r0 > R) {
			throw std::exception("invalid error");
		}
		r = r0;
		return *this;
	}
	Epicicloid& Epicicloid::set_d(double d0) {
		if ((-1) * d0 > R) {
			throw std::exception("invalid error");
		}
		d = d0;
		return *this;
	}
	Epicicloid& Epicicloid::set_R(double R0) {
		if (R < 0) {
			throw std::exception("invalid value");
		}
		R = R0;
		return *this;
	}
	point Epicicloid::get_coordinates(double angle) const {
		point p0;
		p0.x = p.x + (R + r) * cos(angle) - d * cos((R + r) * angle / r);
		p0.y = p.y + (R + r) * sin(angle) - d * sin((R + r) * angle / r);
		return p0;
	}
	double Epicicloid::get_curv_rad(double angle) const {
		angle = angle / 180 * 3.14159;
		return (R + r) * pow((pow(r,2)+pow(d,2)-2*d*r*cos(R*angle/r)),1.5) / abs(pow(r,3)+pow(d,2)*(R+r)-d*r*(R+2*r)*cos(R*angle/r));
	}
	const char* Epicicloid::get_type() const{
		const char *type;
		if (d < r) {
			type = "shortened\0";
		}
		else if (d > r) {
			type = "extended\0";
		}
		else {
			type = "ordinary\0";
		}
		return type;
	}
	double Epicicloid::sect_area(double angle) const {
		angle = angle / 180 * 3.14159;
		return ((R + r) / 2) * ((R + r + pow(d, 2) / r) * angle - d * ((R + 2 * r) / R) * sin(R * angle / r));
	}
	bool Epicicloid::Is_astroid() const{
		return ((r < 0) && (abs(R) == 4 * abs(r)) && (r==d)) ? true : false;
	}
}