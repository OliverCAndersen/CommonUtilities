#pragma once
#include "Matrix44.h"
#include "Vector.h"
#include <array>
#include <cmath>
#include "assert.h"

namespace CommonUtilities
{
	template <class T>
	class Matrix33
	{
	public:
		Matrix33<T>();
		Matrix33(const T & a0, const T & a1, const T & a2, const T & a3, const T & a4, const T & a5, const T & a6, const T & a7, const T & a8);
		Matrix33<T>(const Matrix33<T>& aMatrix);
		Matrix33<T>(const Matrix44<T>& aMatrix);

		static Matrix33<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundZ(T aAngleInRadians);

		static Matrix33<T> Transpose(const Matrix33<T>& aMatrixToTranspose);

		std::array<T, 9> myMatrix;		

		inline Matrix33<T> & Matrix33<T>::operator=(const Matrix33<T>& aMatrix);
		inline T& operator[](const int & aIndex);
		inline const T& operator[](const int & aIndex) const;
		inline Matrix33<T> operator+=(const Matrix33<T>& aMatrix);
		inline Matrix33<T> operator-=(const Matrix33<T>& aMatrix);
		inline Matrix33<T> operator*=(const Matrix33<T>& aMatrix);
	};

	template<class T>
	inline Matrix33<T>::Matrix33()
	{
		myMatrix = {static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
					static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
					static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)};
	}

	template<class T>
	inline Matrix33<T>::Matrix33(const T & a0, const T & a1, const T & a2, const T & a3, const T & a4, const T & a5, const T & a6, const T & a7, const T & a8)
	{
		myMatrix = { a0, a1, a2, a3, a4, a5, a6, a7, a8 };
	}

	template<class T>
	inline Matrix33<T>::Matrix33(const Matrix33<T>& aMatrix)
	{
		myMatrix = aMatrix.myMatrix;
	}

	template<class T>
	inline Matrix33<T>::Matrix33(const Matrix44<T>& aMatrix)
	{
		myMatrix[0] = aMatrix[0];
		myMatrix[1] = aMatrix[1];
		myMatrix[2] = aMatrix[2];
		myMatrix[3] = aMatrix[4];
		myMatrix[4] = aMatrix[5];
		myMatrix[5] = aMatrix[6];
		myMatrix[6] = aMatrix[8];
		myMatrix[7] = aMatrix[9];
		myMatrix[8] = aMatrix[10];
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);

		Matrix33<T> xRotationMatrix = { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
										static_cast<T>(0), cosOfAngle, sinOfAngle,
										static_cast<T>(0), -sinOfAngle, cosOfAngle };

		return xRotationMatrix;
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);
		Matrix33<T> yRotationMatrix = { cosOfAngle, static_cast<T>(0), -sinOfAngle,
										static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
										sinOfAngle, static_cast<T>(0), cosOfAngle };

		return yRotationMatrix;
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);
		Matrix33<T> zRotationMatrix = { cosOfAngle, sinOfAngle, static_cast<T>(0),
										-sinOfAngle, cosOfAngle, static_cast<T>(0),
										static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };

		return zRotationMatrix;
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::Transpose(const Matrix33<T>& aMatrixToTranspose)
	{
		Matrix33<T> transposedMatrix;

		transposedMatrix[0] = aMatrixToTranspose[0];
		transposedMatrix[1] = aMatrixToTranspose[3];
		transposedMatrix[2] = aMatrixToTranspose[6];

		transposedMatrix[3] = aMatrixToTranspose[1];
		transposedMatrix[4] = aMatrixToTranspose[4];
		transposedMatrix[5] = aMatrixToTranspose[7];

		transposedMatrix[6] = aMatrixToTranspose[2];
		transposedMatrix[7] = aMatrixToTranspose[5];
		transposedMatrix[8] = aMatrixToTranspose[8];

		return transposedMatrix;
	}

	template<class T>
	inline T& Matrix33<T>::operator[](const int & aIndex)
	{
		assert((aIndex >= 0 && aIndex < 9) && "Index out of range.");
		return myMatrix[aIndex];
	}

	template<class T>
	inline const T& Matrix33<T>::operator[](const int & aIndex) const
	{
		assert((aIndex >= 0 && aIndex < 9) && "Index out of range.");
		return myMatrix[aIndex];
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::operator+=(const Matrix33<T>& aMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			myMatrix[i] += aMatrix[i];
		}

		return *this;
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::operator-=(const Matrix33<T>& aMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			myMatrix[i] -= aMatrix[i];
		}

		return *this;
	}

	template<class T>
	inline Matrix33<T> operator*(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		const std::array<T, 9>& m0 = aMatrix0.myMatrix;
		const std::array<T, 9>& m1 = aMatrix1.myMatrix;

		Matrix33<T> result;
		result[0] = (m0[0] * m1[0]) + (m0[1] * m1[3]) + (m0[2] * m1[6]);
		result[1] = (m0[0] * m1[1]) + (m0[1] * m1[4]) + (m0[2] * m1[7]);
		result[2] = (m0[0] * m1[2]) + (m0[1] * m1[5]) + (m0[2] * m1[8]);

		result[3] = (m0[3] * m1[0]) + (m0[4] * m1[3]) + (m0[5] * m1[6]);
		result[4] = (m0[3] * m1[1]) + (m0[4] * m1[4]) + (m0[5] * m1[7]);
		result[5] = (m0[3] * m1[2]) + (m0[4] * m1[5]) + (m0[5] * m1[8]);

		result[6] = (m0[6] * m1[0]) + (m0[7] * m1[3]) + (m0[8] * m1[6]);
		result[7] = (m0[6] * m1[1]) + (m0[7] * m1[4]) + (m0[8] * m1[7]);
		result[8] = (m0[6] * m1[2]) + (m0[7] * m1[5]) + (m0[8] * m1[8]);

		return result;
	}

	template<class T>
	inline Vector3<T> operator*(const Vector3<T>& aVector, const Matrix33<T>& aMatrix)
	{
		const std::array<T, 9>& matrix = aMatrix.myMatrix;

		Vector3<T> result;
		result.x = (aVector.x * matrix[0]) + (aVector.y * matrix[3]) + (aVector.z * matrix[6]);
		result.y = (aVector.x * matrix[1]) + (aVector.y * matrix[4]) + (aVector.z * matrix[7]);
		result.z = (aVector.x * matrix[2]) + (aVector.y * matrix[5]) + (aVector.z * matrix[8]);

		return result;
	}

	template<class T>
	inline Matrix33<T> Matrix33<T>::operator*=(const Matrix33<T>& aMatrix)
	{
		const std::array<T, 9>& m0 = myMatrix;
		const std::array<T, 9>& m1 = aMatrix.myMatrix;

		Matrix33<T> result;
		result[0] = (m0[0] * m1[0]) + (m0[1] * m1[3]) + (m0[2] * m1[6]);
		result[1] = (m0[0] * m1[1]) + (m0[1] * m1[4]) + (m0[2] * m1[7]);
		result[2] = (m0[0] * m1[2]) + (m0[1] * m1[5]) + (m0[2] * m1[8]);

		result[3] = (m0[3] * m1[0]) + (m0[4] * m1[3]) + (m0[5] * m1[6]);
		result[4] = (m0[3] * m1[1]) + (m0[4] * m1[4]) + (m0[5] * m1[7]);
		result[5] = (m0[3] * m1[2]) + (m0[4] * m1[5]) + (m0[5] * m1[8]);

		result[6] = (m0[6] * m1[0]) + (m0[7] * m1[3]) + (m0[8] * m1[6]);
		result[7] = (m0[6] * m1[1]) + (m0[7] * m1[4]) + (m0[8] * m1[7]);
		result[8] = (m0[6] * m1[2]) + (m0[7] * m1[5]) + (m0[8] * m1[8]);

		*this = result;

		return result;
	}

	template<class T>
	inline Matrix33<T> operator+(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		Matrix33<T> result;
		for (int i = 0; i < 9; ++i)
		{
			result[i] = aMatrix0[i] + aMatrix1[i];
		}

		return result;
	}

	template<class T>
	inline Matrix33<T> operator-(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		Matrix33<T> result;
		for (int i = 0; i < 9; ++i)
		{
			result[i] = aMatrix0[i] - aMatrix1[i];
		}

		return result;
	}

	template<class T>
	inline bool operator==(const Matrix33<T>& aMatrix0, const Matrix33<T>& aMatrix1)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (aMatrix0[i] != aMatrix1[i])
			{
				return false;
			}
		}

		return true;
	}

	template<class T>
	inline Matrix33<T>& Matrix33<T>::operator=(const Matrix33<T>& aMatrix)
	{
		for (int i = 0; i < 9; ++i)
		{
			myMatrix[i] = aMatrix[i];
		}

		return *this;
	}
}

namespace CU = CommonUtilities;