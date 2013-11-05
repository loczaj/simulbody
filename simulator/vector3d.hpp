#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

struct vector3D {
	double x, y, z;

	vector3D()
			: x(0.0), y(0.0), z(0.0) {
	}

	vector3D(double xyz)
			: x(xyz), y(xyz), z(xyz) {
	}

	vector3D(double vx, double vy, double vz)
			: x(vx), y(vy), z(vz) {
	}

	vector3D& operator+=(const vector3D &term) {
		x += term.x;
		y += term.y;
		z += term.z;
		return *this;
	}

	vector3D& operator-=(const vector3D &term) {
		x -= term.x;
		y -= term.y;
		z -= term.z;
		return *this;
	}

	vector3D& operator*=(const double &factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	vector3D& operator/=(const double &divisor) {
		x /= divisor;
		y /= divisor;
		z /= divisor;
		return *this;
	}

	vector3D operator+(const vector3D &term) const {
		vector3D sum(*this);
		sum.x += term.x;
		sum.y += term.y;
		sum.z += term.z;
		return sum;
	}

	vector3D operator-(const vector3D &term) const {
		vector3D difference(*this);
		difference.x -= term.x;
		difference.y -= term.y;
		difference.z -= term.z;
		return difference;
	}

	vector3D operator*(const double &factor) const {
		vector3D product(*this);
		product.x *= factor;
		product.y *= factor;
		product.z *= factor;
		return product;
	}

	vector3D operator/(const double &divisor) const {
		vector3D quotient(*this);
		quotient.x /= divisor;
		quotient.y /= divisor;
		quotient.z /= divisor;
		return quotient;
	}

	vector3D operator-() const {
		vector3D negative;
		negative.x = -x;
		negative.y = -y;
		negative.z = -z;
		return negative;
	}

	double scalarProduct(const vector3D &v2) const {
		return x * v2.x + y * v2.y + z * v2.z;
	}

	double abs() const {
		return sqrt(x * x + y * y + z * z);
	}
};

#endif /* VECTOR3D_HPP */
