#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <iostream>
#include "../library/Epicicloid.h"

int main() {
	namespace epc = epicicloid1;
	epc::Epicicloid new_epc1(0, 0, 4, 5, 3);
	while (true) {
		std::cout << "Enter angle: " << std::endl;
		double angle;
		std::cin >> angle;
		if (!std::cin.good()) {
			break;
		}
		epc::point p0 = new_epc1.get_coordinates(angle);
		std::cout << "Epicicloid new_epc1" << std::endl;
		std::cout << "r = " << new_epc1.get_r() << std::endl;
		std::cout << "R = " << new_epc1.get_R() << std::endl;
		std::cout << "d = " << new_epc1.get_d() << std::endl;
		std::cout << "Cordinartes of point belonging the epicicloid with angle: " << angle << " (" << p0.x << "," << p0.y << ")" << std::endl;
		std::cout << "Curv rad = " << new_epc1.get_curv_rad(angle) << std::endl;
		epc::border_rads rads = new_epc1.get_border_rads();
		std::cout << "Big radius " << rads.R << " -- " << "small radius " << rads.r << std::endl;
		std::cout << "type of new_epc1 " << new_epc1.get_type() << std::endl;
		std::cout << "Sectorial square " << new_epc1.sect_area(angle) << std::endl;
		std::cout << "Is_astroid: " << new_epc1.Is_astroid() << std::endl;

		std::cout << "Enter new point, r, R, and d" << std::endl;
		std::cin.clear();
		epc::point p1;
		double new_r, new_R, new_d;
		std::cin >> p1.x>>p1.y>>new_r>>new_R>>new_d;
		if (!std::cin.good()) {
			break;
		}
		else {
			new_epc1.set_point(p1);
			try {
				
				new_epc1.set_r(new_r);
				new_epc1.set_R(new_R);
				new_epc1.set_d(new_d);
			}
			catch (std::exception &ex){
				std::cout << ex.what() << std::endl;
			}
		}
	}
	return 0;
}