#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <ostream>

namespace simulbody {

struct vector3D {
	double x, y, z;

	vector3D()
			: x(0.0), y(0.0), z(0.0) {
	}

	vector3D(double x, double y, double z)
			: x(x), y(y), z(z) {
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

	vector3D vectorProduct(const vector3D &v2) const {
		vector3D product;
		product.x = y * v2.z - v2.y * z;
		product.y = z * v2.x - v2.z * x;
		product.z = x * v2.y - v2.x * y;
		return product;
	}

	double distance(const vector3D &v2) const {
		return sqrt((x - v2.x) * (x - v2.x) + (y - v2.y) * (y - v2.y) + (z - v2.z) * (z - v2.z));
	}

	double abs() const {
		return sqrt(x * x + y * y + z * z);
	}

	vector3D eulerRotation(double phi, double theta, double eta) const {
		vector3D result;

		result.x = x * (-sin(phi) * sin(eta) + cos(phi) * cos(theta) * cos(eta));
		result.x += y * (-sin(phi) * cos(eta) - cos(phi) * cos(theta) * sin(eta));
		result.x += z * (cos(phi) * sin(theta));

		result.y = x * (cos(phi) * sin(eta) + sin(phi) * cos(theta) * cos(eta));
		result.y += y * (cos(phi) * cos(eta) - sin(phi) * cos(theta) * sin(eta));
		result.y += z * (sin(phi) * sin(theta));

		result.z = x * (-sin(theta) * cos(eta));
		result.z += y * (sin(theta) * sin(eta));
		result.z += z * (cos(theta));

		return result;
	}

	vector3D convertFromSphericalToCartesian() {
		return vector3D(x * sin(y) * cos(z), x * sin(y) * sin(z), x * cos(y));
	}

};

inline std::ostream& operator<<(std::ostream &out, const vector3D &v) {
	return out << v.x << "\t" << v.y << "\t" << v.z;
}

} /* NAMESPACE SIMULBODY */

#endif /* VECTOR3D_HPP */
