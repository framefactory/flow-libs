/**
* Flow Libs - Math
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_MATH_MATRIX3T_H
#define _FLOWLIBS_MATH_MATRIX3T_H

#include "library.h"

#include "Vector3T.h"
#include "QuaternionT.h"

#include "../core/json.h"

#include <stdlib.h>
#include <math.h>


namespace flow
{
	template <typename REAL>
	class Matrix3T
	{
		//  Public types -------------------------------------------------

	public:
		enum storage_t
		{
			RowMajor,
			ColumnMajor
		};

		//  Constructors and destructor ----------------------------------

		/// Default constructor.
		Matrix3T() { }

		/// Create a 3 by 3 matrix from 9 scalar values.
		Matrix3T(REAL m00, REAL m01, REAL m02,
			REAL m10, REAL m11, REAL m12, REAL m20, REAL m21, REAL m22);
		/// Create a 3 by 3 matrix from 3 vectors.
		Matrix3T(const Vector3T<REAL>& v0, const Vector3T<REAL>& v1,
			const Vector3T<REAL>& v2, storage_t storageOrder = RowMajor);
		/// Create a 3 by 3 matrix from an array of 9 scalar values.
		Matrix3T(const REAL* pValues, storage_t storageOrder = RowMajor);

		//  Conversions --------------------------------------------------

		/// Returns a pointer to an array of 9 scalar values, row-major layout.
		REAL* ptr() { return m_row[0].ptr(); }
		/// Returns a pointer to a const array of 9 scalar values, row-major layout.
		const REAL* ptr() const { return m_row[0].ptr(); }

		/// Conversion between 3 by 3 matrices of different numeric types.
		template <typename T>
		operator Matrix3T<T>() const {
			return Matrix3T<T>((Vector3T<T>)m_row[0],
				(Vector3T<T>)m_row[1], (Vector3T<T>)m_row[2]);
		}

		//  Access -------------------------------------------------------

		/// Set all elements to zero.
		void setZero();
		/// Set all elements to zero and diagonal elements to one.
		void setIdentity();

		/// Replaces all components of the matrix by the given scalar values.
		void set(REAL m00, REAL m01, REAL m02,
			REAL m10, REAL m11, REAL m12, REAL m20, REAL m21, REAL m22);
		/// Replaces all elements of the matrix by the given vectors.
		void set(const Vector3T<REAL>& v0, const Vector3T<REAL>& v1,
			const Vector3T<REAL>& v2, storage_t storageOrder = RowMajor);

		/// Replaces one row of the matrix by the given vector.
		void setRow(size_t index, const Vector3T<REAL>& vec);
		/// Replaces one column of the matrix by the given vector.
		void setColumn(size_t index, const Vector3T<REAL>& vec);
		/// Returns the row with the given index.
		const Vector3T<REAL>& row(size_t index) const;
		/// Returns the column with the given index.
		const Vector3T<REAL> column(size_t index) const;

		/// Subscript operator. Returns the row vector at the given index.
		Vector3T<REAL>& operator[](size_t index);
		/// Const subscript operator. Returns the row vector at the given index.
		const Vector3T<REAL>& operator[] (size_t index) const;

		/// Function-call operator. Returns the element at the given row and column.
		REAL& operator()(size_t row, size_t column);
		/// Const function-call operator. Returns the element at the given row and column.
		const REAL& operator()(size_t row, size_t column) const;
		/// Returns the element at the given row and column.
		REAL& at(size_t row, size_t column);
		/// Returns the element at the given row and column.
		const REAL& at(size_t row, size_t column) const;

		/// Replaces all elements of the matrix by the values of the given array.
		void copyFrom(const REAL* pValues, storage_t storageOrder = RowMajor);
		/// Copies all elements of the matrix to the given array.
		void copyTo(REAL* pValues, storage_t storageOrder = RowMajor) const;

		//  Operators ----------------------------------------------------

		/// Matrix addition, compound operator.
		Matrix3T<REAL>& operator+=(const Matrix3T<REAL>& other);
		/// Addition of a scalar, compound operator.
		Matrix3T<REAL>& operator+=(REAL scalar);
		/// Matrix subtraction, compound operator.
		Matrix3T<REAL>& operator-=(const Matrix3T<REAL>& other);
		/// Subtraction of a scalar, compound operator.
		Matrix3T<REAL>& operator-=(REAL scalar);
		/// Matrix multiplication, compound operator.
		Matrix3T<REAL>& operator*=(const Matrix3T<REAL>& other);
		/// Component-wise multiplication, compound operator.
		Matrix3T<REAL>& operator*=(REAL scalar);
		/// Component-wise division, compound operator.
		Matrix3T<REAL>& operator/=(REAL scalar);

		//  Public commands ----------------------------------------------

		/// Transpose the matrix.
		void transpose();
		/// Invert the matrix.
		void invert(bool* pSuccess = NULL);
		/// Homogenizes the matrix by dividing all elements by the last element e[2][2];
		void homogenize();

		/// Make a 2d translation matrix using the given translation values.
		void makeTranslation(REAL tx, REAL ty);
		/// Make a 2d translation matrix using the given translation vector.
		void makeTranslation(const Vector2T<REAL>& translation);

		/// Make a 2d rotation matrix using the given angle.
		void makeRotation2D(REAL angle);
		/// Make a 3d rotation matrix using the given x-angle.
		void makeRotationX(REAL angle);
		/// Make a 3d rotation matrix using the given y-angle.
		void makeRotationY(REAL angle);
		/// Make a 3d rotation matrix using the given z-angle.
		void makeRotationZ(REAL angle) { return makeRotation2D(angle); }
		/// Make a 3d rotation matrix using the given Euler angles.
		void makeRotationYPR(const Vector3T<REAL>& yawPitchRoll);
		/// Make a 3d rotation by the given angle about the given axis.
		void makeRotation(const Vector3T<REAL>& axis, REAL angle);
		/// Make a 3d rotation from the given unit quaternion.
		void makeRotation(const QuaternionT<REAL>& rotation);

		/// Make a 2d scale matrix using the given scaling factors.
		void makeScale(const Vector2T<REAL>& scalingFactors);
		/// Make a 2d scale matrix using the given scaling factors.
		void makeScale(REAL sx, REAL sy);
		/// Make a 2d uniform scale matrix using the given scaling factor.
		void makeScale(REAL s) { return makeScale(s, s); }

		//  Public queries -----------------------------------------------

		/// Returns the transpose of the matrix.
		Matrix3T<REAL> transposed() const;
		/// Returns the inverse of the matrix.
		Matrix3T<REAL> inverted() const;
		/// Returns the homogenized matrix.
		Matrix3T<REAL> homogenized() const;

		/// Calculates and returns the determinant of the matrix.
		REAL determinant() const;
		/// Returns the unit rotation quaternion if this is a rotation matrix.
		void getRotation(QuaternionT<REAL>& rotation) const;
		/// Calculates and returns the Frobenius norm of the matrix.
		REAL frobeniusNorm() const;
		/// Calculates and returns the square of the Frobenius norm of the matrix.
		REAL frobeniusNormSquared() const;

		/// Converts the matrix to a JSON array.
		json toJSON() const;

		//  Internal data members ----------------------------------------

	private:
		Vector3T<REAL> m_row[3];
	};

	// Constructors ----------------------------------------------------------------

	template <typename REAL>
	inline Matrix3T<REAL>::Matrix3T(REAL m00, REAL m01, REAL m02,
		REAL m10, REAL m11, REAL m12, REAL m20, REAL m21, REAL m22)
	{
		m_row[0].set(m00, m01, m02);
		m_row[1].set(m10, m11, m12);
		m_row[2].set(m20, m21, m22);
	}

	template <typename REAL>
	Matrix3T<REAL>::Matrix3T(const Vector3T<REAL>& v0, const Vector3T<REAL>& v1,
		const Vector3T<REAL>& v2, storage_t storageOrder /* = RowMajor */)
	{
		if (storageOrder == RowMajor)
		{
			m_row[0] = v0;
			m_row[1] = v1;
			m_row[2] = v2;
		}
		else // ColumnMajor
		{
			m_row[0].set(v0.x, v1.x, v2.x);
			m_row[1].set(v0.y, v1.y, v2.y);
			m_row[2].set(v0.z, v1.z, v2.z);
		}
	}

	template <typename REAL>
	Matrix3T<REAL>::Matrix3T(const REAL* pValues, storage_t storageOrder /* = RowMajor */)
	{
		if (storageOrder == RowMajor)
		{
			m_row[0].set(pValues[0], pValues[1], pValues[2]);
			m_row[1].set(pValues[3], pValues[4], pValues[5]);
			m_row[2].set(pValues[6], pValues[7], pValues[8]);
		}
		else // ColumnMajor
		{
			m_row[0].set(pValues[0], pValues[3], pValues[6]);
			m_row[1].set(pValues[1], pValues[4], pValues[7]);
			m_row[2].set(pValues[2], pValues[5], pValues[8]);
		}
	}

	// Access ----------------------------------------------------------------------

	template <typename REAL>
	inline void Matrix3T<REAL>::setZero()
	{
		m_row[0].setZero();
		m_row[1].setZero();
		m_row[2].setZero();
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::setIdentity()
	{
		m_row[0].set(REAL(1.0), REAL(0.0), REAL(0.0));
		m_row[1].set(REAL(0.0), REAL(1.0), REAL(0.0));
		m_row[2].set(REAL(0.0), REAL(0.0), REAL(1.0));
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::set(REAL m00, REAL m01, REAL m02,
		REAL m10, REAL m11, REAL m12, REAL m20, REAL m21, REAL m22)
	{
		m_row[0].set(m00, m01, m02);
		m_row[1].set(m10, m11, m12);
		m_row[2].set(m20, m21, m22);
	}

	template <typename REAL>
	void Matrix3T<REAL>::set(const Vector3T<REAL>& v0, const Vector3T<REAL>& v1,
		const Vector3T<REAL>& v2, storage_t storageOrder /* = RowMajor */)
	{
		if (storageOrder == RowMajor)
		{
			m_row[0] = v0;
			m_row[1] = v1;
			m_row[2] = v2;
		}
		else // ColumnMajor
		{
			m_row[0].set(v0.x, v1.x, v2.x);
			m_row[1].set(v0.y, v1.y, v2.y);
			m_row[2].set(v0.z, v1.z, v2.z);
		}
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::setRow(size_t index, const Vector3T<REAL>& vec)
	{
		F_ASSERT(index < 3);
		m_row[index] = vec;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::setColumn(size_t index, const Vector3T<REAL>& vec)
	{
		F_ASSERT(index < 3);
		m_row[0][index] = vec[0];
		m_row[1][index] = vec[1];
		m_row[2][index] = vec[2];
	}

	template <typename REAL>
	inline const Vector3T<REAL>& Matrix3T<REAL>::row(size_t index) const
	{
		F_ASSERT(index < 3);
		return m_row[index];
	}

	template <typename REAL>
	inline const Vector3T<REAL> Matrix3T<REAL>::column(size_t index) const
	{
		F_ASSERT(index < 3);
		return Vector3T<REAL>(m_row[0][index], m_row[1][index], m_row[2][index]);
	}

	template <typename REAL>
	inline Vector3T<REAL>& Matrix3T<REAL>::operator[](size_t index)
	{
		F_ASSERT(index < 3);
		return m_row[index];
	}

	template <typename REAL>
	inline const Vector3T<REAL>& Matrix3T<REAL>::operator[] (size_t index) const
	{
		F_ASSERT(index < 3);
		return m_row[index];
	}

	template <typename REAL>
	inline REAL& Matrix3T<REAL>::operator()(size_t row, size_t column)
	{
		F_ASSERT(row < 3 && column < 3);
		return m_row[row][column];
	}

	template <typename REAL>
	inline const REAL& Matrix3T<REAL>::operator()(size_t row, size_t column) const
	{
		F_ASSERT(row < 3 && column < 3);
		return m_row[row][column];
	}

	template <typename REAL>
	inline REAL& Matrix3T<REAL>::at(size_t row, size_t column)
	{
		F_ASSERT(row < 3 && column < 3);
		return m_row[row][column];
	}

	template <typename REAL>
	inline const REAL& Matrix3T<REAL>::at(size_t row, size_t column) const
	{
		F_ASSERT(row < 3 && column < 3);
		return m_row[row][column];
	}

	template <typename REAL>
	void Matrix3T<REAL>::copyFrom(const REAL* pValues, storage_t storageOrder /* = RowMajor */)
	{
		if (storageOrder == RowMajor)
		{
			m_row[0].set(pValues[0], pValues[1], pValues[2]);
			m_row[1].set(pValues[3], pValues[4], pValues[5]);
			m_row[2].set(pValues[6], pValues[7], pValues[8]);
		}
		else // ColumnMajor
		{
			m_row[0].set(pValues[0], pValues[3], pValues[6]);
			m_row[1].set(pValues[1], pValues[4], pValues[7]);
			m_row[2].set(pValues[2], pValues[5], pValues[8]);
		}
	}

	template <typename REAL>
	void Matrix3T<REAL>::copyTo(REAL* pValues, storage_t storageOrder /* = RowMajor */) const
	{
		if (storageOrder == RowMajor)
		{
			pValues[0] = m_row[0].x; pValues[1] = m_row[0].y; pValues[2] = m_row[0].z;
			pValues[3] = m_row[1].x; pValues[4] = m_row[1].y; pValues[5] = m_row[1].z;
			pValues[6] = m_row[2].x; pValues[7] = m_row[2].y; pValues[8] = m_row[2].z;
		}
		else // ColumnMajor
		{
			pValues[0] = m_row[0].x; pValues[1] = m_row[1].x; pValues[2] = m_row[2].x;
			pValues[3] = m_row[0].y; pValues[4] = m_row[1].y; pValues[5] = m_row[2].y;
			pValues[6] = m_row[0].z; pValues[7] = m_row[1].z; pValues[8] = m_row[2].z;
		}
	}

	// Operators -------------------------------------------------------------------

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator+=(const Matrix3T<REAL>& other)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] += other.m_row[i];
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator+=(REAL scalar)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] += scalar;
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator-=(const Matrix3T<REAL>& other)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] -= other.m_row[i];
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator-=(REAL scalar)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] -= scalar;
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator*=(const Matrix3T<REAL>& other)
	{
		Matrix3T<REAL> result;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				REAL s = REAL(0.0);
				for (size_t k = 0; k < 3; k++)
					s += m_row[i][k] * other.m_row[k][j];
				result.m_row[i][j] = s;
			}
		}

		*this = result;
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator*=(REAL scalar)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] *= scalar;
		return *this;
	}

	template <typename REAL>
	inline Matrix3T<REAL>& Matrix3T<REAL>::operator/=(REAL scalar)
	{
		for (size_t i = 0; i < 3; i++)
			m_row[i] /= scalar;
		return *this;
	}

	// Public commands -------------------------------------------------------------

	template <typename REAL>
	inline void Matrix3T<REAL>::transpose()
	{
		REAL t0 = m_row[0][1]; m_row[0][1] = m_row[1][0]; m_row[1][0] = t0;
		REAL t1 = m_row[0][2]; m_row[0][2] = m_row[2][0]; m_row[2][0] = t1;
		REAL t2 = m_row[1][2]; m_row[1][2] = m_row[2][1]; m_row[2][1] = t2;
	}

	template <typename REAL>
	void Matrix3T<REAL>::invert(bool* pSuccess /* = NULL */)
	{
		REAL d = determinant();
		if (d == REAL(0.0))
		{
			if (pSuccess)
				*pSuccess = false;
			return;
		}

		Matrix3T<REAL> result;
		result(0, 0) = (m_row[1][1] * m_row[2][2] - m_row[1][2] * m_row[2][1]) / d;
		result(0, 1) = (m_row[0][2] * m_row[2][1] - m_row[0][1] * m_row[2][2]) / d;
		result(0, 2) = (m_row[0][1] * m_row[1][2] - m_row[0][2] * m_row[1][1]) / d;
		result(1, 0) = (m_row[2][0] * m_row[1][2] - m_row[1][0] * m_row[2][2]) / d;
		result(1, 1) = (m_row[0][0] * m_row[2][2] - m_row[2][0] * m_row[0][2]) / d;
		result(1, 2) = (m_row[1][0] * m_row[0][2] - m_row[0][0] * m_row[1][2]) / d;
		result(2, 0) = (m_row[1][0] * m_row[2][1] - m_row[2][0] * m_row[1][1]) / d;
		result(2, 1) = (m_row[2][0] * m_row[0][1] - m_row[0][0] * m_row[2][1]) / d;
		result(2, 2) = (m_row[0][0] * m_row[1][1] - m_row[1][0] * m_row[0][1]) / d;

		if (pSuccess)
			*pSuccess = true;
		*this = result;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::homogenize()
	{
		REAL f = REAL(1.0) / m_row[2][2];
		for (size_t i = 0; i < 3; ++i)
			m_row[i] *= f;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeTranslation(const Vector2T<REAL>& translation)
	{
		makeTranslation(translation.x(), translation.y());
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeTranslation(REAL tx, REAL ty)
	{
		m_row[0][0] = REAL(1.0); m_row[0][1] = REAL(0.0); m_row[0][2] = tx;
		m_row[1][0] = REAL(0.0); m_row[1][1] = REAL(1.0); m_row[1][2] = ty;
		m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = REAL(1.0);
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotation2D(REAL angle)
	{
		REAL si = sin(angle);
		REAL co = cos(angle);

		m_row[0][0] = co;        m_row[0][1] = -si;       m_row[0][2] = REAL(0.0);
		m_row[1][0] = si;        m_row[1][1] = co;        m_row[1][2] = REAL(0.0);
		m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = REAL(1.0);
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotationX(REAL angle)
	{
		REAL si = sin(angle);
		REAL co = cos(angle);

		m_row[0][0] = REAL(1.0); m_row[0][1] = REAL(0.0); m_row[0][2] = REAL(0.0);
		m_row[1][0] = REAL(0.0); m_row[1][1] = co;        m_row[1][2] = -si;
		m_row[2][0] = REAL(0.0); m_row[2][1] = si;        m_row[2][2] = co;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotationY(REAL angle)
	{
		REAL si = sin(angle);
		REAL co = cos(angle);

		m_row[0][0] = co;        m_row[0][1] = REAL(0.0); m_row[0][2] = si;
		m_row[1][0] = REAL(0.0); m_row[1][1] = REAL(1.0); m_row[1][2] = REAL(0.0);
		m_row[2][0] = -si;       m_row[2][1] = REAL(0.0); m_row[2][2] = co;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotationYPR(const Vector3T<REAL>& yawPitchRoll)
	{
		REAL sy = sin(yawPitchRoll.x());
		REAL cy = cos(yawPitchRoll.x());
		REAL sp = sin(yawPitchRoll.y());
		REAL cp = cos(yawPitchRoll.y());
		REAL sr = sin(yawPitchRoll.z());
		REAL cr = cos(yawPitchRoll.z());

		m_row[0][0] = cr * cy - sr * sp * sy;
		m_row[0][1] = -sr * cp;
		m_row[0][2] = cr * sy + sr * sp * cy;
		m_row[1][0] = sr * cy + cr * sp * sy;
		m_row[1][1] = cr * cp;
		m_row[1][2] = sr * sy - cr * sp * cy;
		m_row[2][0] = -cp * sy;
		m_row[2][1] = sp;
		m_row[2][2] = cp * cy;
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotation(const Vector3T<REAL>& axis, REAL angle)
	{
		REAL si = (REAL)sin(angle);
		REAL co = (REAL)cos(angle);
		REAL co1 = REAL(1.0) - co;

		m_row[0][0] = co + co1 * axis.x() * axis.x();
		m_row[0][1] = co1 * axis.x() * axis.y() - axis.z() * si;
		m_row[0][2] = co1 * axis.x() * axis.z() + axis.y() * si;
		m_row[1][0] = co1 * axis.x() * axis.y() + axis.z() * si;
		m_row[1][1] = co + co1 * axis.y() * axis.y();
		m_row[1][2] = co1 * axis.y() * axis.z() - axis.x() * si;
		m_row[2][0] = co1 * axis.x() * axis.z() - axis.y() * si;
		m_row[2][1] = co1 * axis.y() * axis.z() + axis.x() * si;
		m_row[2][2] = co + co1 * axis.z() * axis.z();
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeRotation(const QuaternionT<REAL>& rotation)
	{
		REAL x = rotation.x;
		REAL y = rotation.y;
		REAL z = rotation.z;
		REAL w = rotation.w;
		REAL xx = x * x;
		REAL yy = y * y;
		REAL zz = z * z;

		m_row[0][0] = REAL(1.0) - REAL(2.0) * (yy + zz);
		m_row[0][1] = REAL(2.0) * (x * y - w * z);
		m_row[0][2] = REAL(2.0) * (x * z + w * y);
		m_row[1][0] = REAL(2.0) * (x * y + w * z);
		m_row[1][1] = REAL(1.0) - REAL(2.0) * (xx + zz);
		m_row[1][2] = REAL(2.0) * (y * z - w * x);
		m_row[2][0] = REAL(2.0) * (x * z - w * y);
		m_row[2][1] = REAL(2.0) * (y * z + w * x);
		m_row[2][2] = REAL(1.0) - REAL(2.0) * (xx + yy);
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeScale(const Vector2T<REAL>& scalingFactors)
	{
		makeScale(scalingFactors.x(), scalingFactors.y());
	}

	template <typename REAL>
	inline void Matrix3T<REAL>::makeScale(REAL sx, REAL sy)
	{
		m_row[0][0] = sx;        m_row[0][1] = REAL(0.0); m_row[0][2] = REAL(0.0);
		m_row[1][0] = REAL(0.0); m_row[1][1] = sy;        m_row[1][2] = REAL(0.0);
		m_row[2][0] = REAL(0.0); m_row[2][1] = REAL(0.0); m_row[2][2] = REAL(1.0);
	}

	// Public queries -------------------------------------------------------------------------------------

	template <typename REAL>
	inline Matrix3T<REAL> Matrix3T<REAL>::transposed() const
	{
		Matrix3T<REAL> t;

		t[0][0] = m_row[0][0]; t[0][1] = m_row[1][0]; t[0][2] = m_row[2][0];
		t[1][0] = m_row[0][1]; t[1][1] = m_row[1][1]; t[1][2] = m_row[2][1];
		t[2][0] = m_row[0][2]; t[2][1] = m_row[1][2]; t[2][2] = m_row[2][2];
		return t;
	}



	template <typename REAL>
	inline Matrix3T<REAL> Matrix3T<REAL>::inverted() const
	{
		Matrix3T<REAL> result(*this);
		return result.invert();
	}



	template <typename REAL>
	inline Matrix3T<REAL> Matrix3T<REAL>::homogenized() const
	{
		Matrix3T<REAL> result(*this);
		return result.homogenize();
	}

	template <typename REAL>
	inline REAL Matrix3T<REAL>::determinant() const
	{
		return   m_row[2][0] * m_row[0][1] * m_row[1][2] - m_row[2][0] * m_row[0][2] * m_row[1][1]
			- m_row[1][0] * m_row[0][1] * m_row[2][2] + m_row[1][0] * m_row[0][2] * m_row[2][1]
			- m_row[0][0] * m_row[2][1] * m_row[1][2] + m_row[0][0] * m_row[1][1] * m_row[2][2];
	}

	template <typename REAL>
	void Matrix3T<REAL>::getRotation(QuaternionT<REAL>& rotation) const
	{
		// source: http://plib.sourceforge.net/sg/index.html

		REAL tr, s, q[4];
		int i, j, k;

		int nxt[3] = { 1, 2, 0 };

		tr = m_row[0][0] + m_row[1][1] + m_row[2][2];

		// check the trace
		if (tr > REAL(0.0))
		{
			s = sqrt(tr + REAL(1.0));
			rotation.w = s / REAL(2.0);
			s = REAL(0.5) / s;
			rotation.x = (m_row[1][2] - m_row[2][1]) * s;
			rotation.y = (m_row[2][0] - m_row[0][2]) * s;
			rotation.z = (m_row[0][1] - m_row[1][0]) * s;
		}
		else // negative trace
		{
			i = 0;
			if (m_row[1][1] > m_row[0][0])
				i = 1;
			if (m_row[2][2] > m_row[i][i])
				i = 2;

			j = nxt[i];
			k = nxt[j];
			s = sqrt((m_row[i][i] - (m_row[j][j] + m_row[k][k])) + REAL(1.0));
			q[i] = s * REAL(0.5);

			if (s != REAL(0.0))
				s = REAL(0.5) / s;

			q[3] = (m_row[j][k] - m_row[k][j]) * s;
			q[j] = (m_row[i][j] + m_row[j][i]) * s;
			q[k] = (m_row[i][k] + m_row[k][i]) * s;

			rotation.x = q[0];
			rotation.y = q[1];
			rotation.z = q[2];
			rotation.w = q[3];
		}

		// seems to yield the inverse rotation, so:
		rotation.w = -rotation.w;
	}

	template <typename REAL>
	inline REAL Matrix3T<REAL>::frobeniusNorm() const
	{
		REAL sum = REAL(0.0);
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				REAL e = m_row[r][c];
				sum += e * e;
			}
		}
		return sqrt(sum);
	}

	template <typename REAL>
	inline REAL Matrix3T<REAL>::frobeniusNormSquared() const
	{
		REAL sum = REAL(0.0);
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				REAL e = m_row[r][c];
				sum += e * e;
			}
		}
		return sum;
	}

	template <typename REAL>
	inline json Matrix3T<REAL>::toJSON() const
	{
		auto arr = json::array();

		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				arr.push_back(m_row[r][c]);
			}
		}

		return arr;
	}

	// Related non-member functions ------------------------------------------------

	/// Component-wise addition of two matrices.
	template <typename REAL>
	inline Matrix3T<REAL> operator+(const Matrix3T<REAL>& lhs, const Matrix3T<REAL>& rhs)
	{
		Matrix3T<REAL> result;
		for (size_t i = 0; i < 3; i++)
			result[i] = lhs[i] + rhs[i];
		return result;
	}
	/// Component-wise subtraction of two matrices.
	template <typename REAL>
	inline Matrix3T<REAL> operator-(const Matrix3T<REAL>& lhs, const Matrix3T<REAL>& rhs)
	{
		Matrix3T<REAL> result;
		for (size_t i = 0; i < 3; i++)
			result[i] = lhs[i] - rhs[i];
		return result;
	}
	/// Matrix-vector multiplication.
	template <typename REAL>
	inline Vector3T<REAL> operator*(const Matrix3T<REAL>& mat, const Vector3T<REAL>& vec)
	{
		Vector3T<REAL> result;
		for (size_t i = 0; i < 3; i++)
		{
			REAL s = REAL(0.0);
			for (size_t j = 0; j < 3; j++)
				s += mat[i][j] * vec[j];
			result[i] = s;
		}
		return result;
	}
	/// Matrix-matrix multiplication.
	template <typename REAL>
	inline Matrix3T<REAL> operator*(const Matrix3T<REAL>& lhs, const Matrix3T<REAL>& rhs)
	{
		Matrix3T<REAL> result;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				REAL s = REAL(0.0);
				for (size_t k = 0; k < 3; k++)
					s += lhs[i][k] * rhs[k][j];
				result[i][j] = s;
			}
		}
		return result;
	}

	// Typedefs --------------------------------------------------------------------

	/// Matrix of type double.
	typedef Matrix3T<double> Matrix3d;
	/// Matrix of type float.
	typedef Matrix3T<float> Matrix3f;
}

#endif // _FLOWLIBS_MATH_MATRIX3T_H
