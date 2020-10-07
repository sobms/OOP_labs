#pragma once
namespace epicicloid1 {
	typedef struct point {
		double x, y;
		point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {};
	}point;
	typedef struct border_rads {
		double r, R;
	}border_rads;

	class Epicicloid {
	private:
		point p;
		double r, R, d;
	public:
		//constructors
		Epicicloid();
		Epicicloid(const point& p, double r = 1, double R = 1, double d = 1);
		Epicicloid(double x, double y, double r = 1, double R = 1, double d = 1);
		//set'теры
		Epicicloid& set_r(double r);
		Epicicloid& set_R(double R);
		Epicicloid& set_d(double d);
		Epicicloid& set_point(const point& p0) { p = p0; return *this; };
		//get'теры
		double get_r() const { return r; };
		double get_R() const { return R; };
		double get_d() const { return d; };
		point get_p() const { return p; };
		// other methods
		point get_coordinates(double angle) const;
		border_rads get_border_rads() const {
			border_rads rads; rads.R = R + r + d; rads.r = R + r - d; return rads;
		}
		double get_curv_rad(double angle) const;
		const char* get_type() const;
		double sect_area(double angle) const;
		bool Is_astroid() const;
	};

}

