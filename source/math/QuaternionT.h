/**
* Flow Libs - Math
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_MATH_QUATERNIONT_H
#define _FLOWLIBS_MATH_QUATERNIONT_H

#include "library.h"

#include "Vector3T.h"
#include "Vector4T.h"

#include "../core/json.h"

#include <stdlib.h>
#include <math.h>


namespace flow
{
	/// Quaternion with imaginary components x, y, and z and real component w. 
	template <typename REAL>
	class QuaternionT
	{
		//  Public data members ------------------------------------------

	public:
		union
		{
			struct
			{
				REAL x;
				REAL y;
				REAL z;
				REAL w;
			};
			REAL v[4];
		};

		//  Constructors and destructor ----------------------------------

	public:
		/// Default constructor. Creates an uninitialized quaternion.
		QuaternionT() { }
		/// Creates a quaternion from 4 scalar values.
		QuaternionT(REAL x, REAL y, REAL z, REAL w);
		/// Creates a quaternion from a 3-vector.
		QuaternionT(const Vector3T<REAL>& vector);
		/// Creates a quaternion from a 4-vector.
		QuaternionT(const Vector4T<REAL>& vector);
		/// Creates a unit rotation quaternion from an axis (unit vector) and an angle.
		QuaternionT(const Vector3T<REAL>& axis, REAL angle);
		/// Creates a unit rotation quaternion from an axis (homogeneous unit vector) and an angle.
		QuaternionT(const Vector4T<REAL>& axis, REAL angle);

		//  Access -------------------------------------------------------

		/// Subscript operator.
		REAL& operator[](size_t index);
		/// Const subscript operator.
		const REAL& operator[](size_t index) const;
		/// Returns a 4-vector with the components of the quaternion.
		Vector4T<REAL> toVector4() const;
		/// Returns a 3-vector with the first 3 components of the unit quaternion.
		Vector3T<REAL> toVector3() const;

		//  Operators ----------------------------------------------------

		/// Addition of two quaternions, compound-assignment.
		QuaternionT<REAL>& operator+=(const QuaternionT<REAL>& other);
		/// Subtraction of two quaternions, compound-assignment.
		QuaternionT<REAL>& operator-=(const QuaternionT<REAL>& other);
		/// Multiplication of two quaternions, compound-assignment.
		QuaternionT<REAL>& operator*=(const QuaternionT<REAL>& other);

		//  Public commands ----------------------------------------------

		/// Sets all components to zero.
		void makeZero();
		/// Initializes a rotation quaternion representing a zero rotation.
		void makeZeroRotation();
		/// Normalizes the quaternion.
		void normalize();
		/// Inverts the quaternion.
		void invert();
		/// Conjugates the quaternion.
		void conjugate();

		//  Public queries -----------------------------------------------

		/// Returns the 2-norm (euclidean length) of the quaternion.
		REAL length() const;
		/// Returns the squared length of the quaternion.
		REAL lengthSquared() const;
		/// Returns the unit quaternion.
		QuaternionT<REAL> normalized() const;
		/// Returns the conjugate.
		QuaternionT<REAL> conjugated() const;
		/// Returns the inverse.
		QuaternionT<REAL> inverse() const;
		/// Returns the angle of a unit rotation quaternion.
		REAL angle() const;
		/// Returns the axis of a unit rotation quaternion.
		Vector3T<REAL> axis() const;
		/// Applies the quaternion rotation to the given 4-vector.
		Vector4T<REAL> rotate(const Vector4T<REAL>& v) const;
		/// Applies the quaternion rotation to the given 3-vector.
		Vector3T<REAL> rotate(const Vector3T<REAL>& v) const;

		/// Converts the quaternion to a JSON array.
		json toJSON() const;
	};

	// Constructors and destructor -------------------------------------------------

	template <typename REAL>
	QuaternionT<REAL>::QuaternionT(REAL _x, REAL _y, REAL _z, REAL _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	template <typename REAL>
	QuaternionT<REAL>::QuaternionT(const Vector3T<REAL>& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(REAL(1.0))
	{
	}

	template <typename REAL>
	QuaternionT<REAL>::QuaternionT(const Vector4T<REAL>& vec)
		: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
	{
	}

	template <typename REAL>
	QuaternionT<REAL>::QuaternionT(const Vector3T<REAL>& axis, REAL angle)
	{
		REAL angle2 = angle * REAL(0.5);
		REAL sin2 = sin(angle2);
		x = axis.x() * sin2;
		y = axis.y() * sin2;
		z = axis.z() * sin2;
		w = cos(angle2);
	}

	template <typename REAL>
	QuaternionT<REAL>::QuaternionT(const Vector4T<REAL>& axis, REAL angle)
	{
		// axis is a vector, not a point, the w component must be zero
		F_ASSERT(axis.w() == REAL(0.0));

		REAL angle2 = angle * REAL(0.5);
		REAL sin2 = sin(angle2);
		x = axis.x() * sin2;
		y = axis.y() * sin2;
		z = axis.z() * sin2;
		w = cos(angle2);
	}

	// Access ----------------------------------------------------------------------

	template <typename REAL>
	inline REAL& QuaternionT<REAL>::operator[](size_t index)
	{
		F_ASSERT(index < 4);
		return v[index];
	}

	template <typename REAL>
	inline const REAL& QuaternionT<REAL>::operator[](size_t index) const
	{
		F_ASSERT(index < 4);
		return v[index];
	}

	template <typename REAL>
	inline Vector4T<REAL> QuaternionT<REAL>::toVector4() const
	{
		return Vector4T<REAL>(x, y, z, w);
	}

	template <typename REAL>
	inline Vector3T<REAL> QuaternionT<REAL>::toVector3() const
	{
		if (w != REAL(0.0))
			return Vector3T<REAL>(x / w, y / w, z / w);
		else
			return Vector3T<REAL>(x, y, z);
	}

	// Operators -------------------------------------------------------------------

	template <typename REAL>
	inline QuaternionT<REAL>& QuaternionT<REAL>::operator+=(const QuaternionT<REAL>& other)
	{
		for (size_t i = 0; i < 4; i++)
			v[i] += other.v[i];
		return *this;
	}

	template <typename REAL>
	inline QuaternionT<REAL>& QuaternionT<REAL>::operator-=(const QuaternionT<REAL>& other)
	{
		for (size_t i = 0; i < 4; i++)
			v[i] -= other.v[i];
		return *this;
	}

	template <typename REAL>
	inline QuaternionT<REAL>& QuaternionT<REAL>::operator*=(const QuaternionT<REAL>& other)
	{
		*this = *this * other;
		return *this;
	}

	// Public commands -------------------------------------------------------------

	template <typename REAL>
	inline void QuaternionT<REAL>::makeZero()
	{
		x = y = z = w = REAL(0.0);
	}

	template <typename REAL>
	inline void QuaternionT<REAL>::makeZeroRotation()
	{
		x = y = z = REAL(0.0);
		w = REAL(1.0);
	}

	template <typename REAL>
	inline void QuaternionT<REAL>::normalize()
	{
		REAL f = REAL(1.0) / length();
		x *= f; y *= f; z *= f; w *= f;
	}

	template <typename REAL>
	inline void QuaternionT<REAL>::invert()
	{
		REAL f = REAL(1.0) / lengthSquared();
		x = f * -x; y = f * -y; z = f * -z;
		w = f * w;
	}

	template <typename REAL>
	inline void QuaternionT<REAL>::conjugate()
	{
		x = -x; y = -y; z = -z;
	}

	// Public queries --------------------------------------------------------------

	template <typename REAL>
	inline REAL QuaternionT<REAL>::length() const
	{
		return sqrt(x*x + y * y + z * z + w * w);
	}

	template <typename REAL>
	inline REAL QuaternionT<REAL>::lengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <typename REAL>
	inline QuaternionT<REAL> QuaternionT<REAL>::normalized() const
	{
		REAL f = REAL(1.0) / length();
		return QuaternionT<REAL>(x*f, y*f, z*f, w*f);
	}

	template <typename REAL>
	inline QuaternionT<REAL> QuaternionT<REAL>::conjugated() const
	{
		return QuaternionT<REAL>(-x, -y, -z, w);
	}

	template <typename REAL>
	inline QuaternionT<REAL> QuaternionT<REAL>::inverse() const
	{
		REAL f = REAL(1.0) / lengthSquared();
		return QuaternionT<REAL>(f * -x, f * -y, f * -z, f * w);
	}

	template <typename REAL>
	inline REAL QuaternionT<REAL>::angle() const
	{
		return REAL(2.0) * acos(w);
	}

	template <typename REAL>
	inline Vector3T<REAL> QuaternionT<REAL>::axis() const
	{
		REAL s = sqrt(REAL(1.0) - w * w);
		if (s != REAL(0.0))
			return Vector3T<REAL>(x / s, y / s, z / s);
		else
			return Vector3T<REAL>(x, y, z);
	}

	template <typename REAL>
	inline Vector4T<REAL> QuaternionT<REAL>::rotate(const Vector4T<REAL>& v) const
	{
		return ((*this) * QuaternionT<REAL>(v) * conjugated()).toVector4();
	}

	template <typename REAL>
	inline Vector3T<REAL> QuaternionT<REAL>::rotate(const Vector3T<REAL>& v) const
	{
		return ((*this) * QuaternionT<REAL>(v) * conjugated()).toVector3();
	}

	template <typename REAL>
	inline json QuaternionT<REAL>::toJSON() const
	{
		return json::array({ x, y, z, w });
	}

	// Related non-member functions ------------------------------------------------

	/// Addition of two quaternions.
	template <typename REAL>
	inline QuaternionT<REAL> operator+(
		const QuaternionT<REAL>& q1, const QuaternionT<REAL>& q2)
	{
		QuaternionT<REAL> result;
		for (size_t i = 0; i < 4; i++)
			result[i] = q1[i] + q2[i];
		return result;
	}

	/// Subtraction of two quaternions.
	template <typename REAL>
	inline QuaternionT<REAL> operator-(
		const QuaternionT<REAL>& q1, const QuaternionT<REAL>& q2)
	{
		QuaternionT<REAL> result;
		for (size_t i = 0; i < 4; i++)
			result[i] = q1[i] - q2[i];
		return result;
	}

	/// Multiplication of two quaternions.
	template <typename REAL>
	inline QuaternionT<REAL> operator*(
		const QuaternionT<REAL>& q1, const QuaternionT<REAL>& q2)
	{
		QuaternionT<REAL> result;
		result.x = q1.y * q2.z - q1.z * q2.y + q1.x * q2.w + q1.w * q2.x;
		result.y = q1.z * q2.x - q1.x * q2.z + q1.y * q2.w + q1.w * q2.y;
		result.z = q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
		result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		return result;
	}

	// Typedefs --------------------------------------------------------------------

	/// Quaternion of type float
	typedef F_ALIGN(16) QuaternionT<float> Quaternion4f;

	/// Quaternion of type double
	typedef QuaternionT<double> Quaternion4d;
}

#endif // _FLOWLIBS_MATH_QUATERNIONT_H
