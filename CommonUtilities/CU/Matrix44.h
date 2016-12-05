#pragma once
#include "Vector.h"
#include <array>
#include <cmath>
#include "assert.h"

namespace CommonUtilities
{
	template <class T>
	class Matrix44
	{
	public:
		Matrix44<T>();
		Matrix44<T>(const T& a0, const T& a1, const T& a2, const T& a3, const T& a4, const T& a5, const T& a6, const T& a7, const T& a8, const T& a9, const T& a10, const T& a11, const T& a12, const T& a13, const T& a14, const T& a15);
		Matrix44<T>(const Matrix44<T>& aMatrix);

		static Matrix44<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundZ(T aAngleInRadians);

		static Matrix44<T> Transpose(const Matrix44<T>& aMatrixToTranspose);

		std::array<T, 16> myMatrix;


		inline Matrix44<T> & Matrix44<T>::operator=(const Matrix44<T>& aMatrix);
		inline T& operator[](const int & aIndex);
		inline const T& operator[](const int & aIndex) const;
		inline Matrix44<T> operator+=(const Matrix44<T>& aMatrix);
		inline Matrix44<T> operator-=(const Matrix44<T>& aMatrix);
		inline Matrix44<T> operator*=(const Matrix44<T>& aMatrix);
	};

	template<class T>
	inline Matrix44<T>::Matrix44()
	{
		myMatrix = {static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
					static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
					static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
					static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)};
	}

	template<class T>
	inline Matrix44<T>::Matrix44(const T & a0, const T & a1, const T & a2, const T & a3, const T & a4, const T & a5, const T & a6, const T & a7, const T & a8, const T & a9, const T & a10, const T & a11, const T & a12, const T & a13, const T & a14, const T & a15)
	{
		myMatrix = { a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15 };
	}

	template<class T>
	inline Matrix44<T>::Matrix44(const Matrix44<T>& aMatrix)
	{
		myMatrix = aMatrix.myMatrix;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);
		Matrix44<T> xRotationMatrix = { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), cosOfAngle, -sinOfAngle, static_cast<T>(0),
			static_cast<T>(0), sinOfAngle, cosOfAngle, static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };

		return xRotationMatrix;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);
		Matrix44<T> yRotationMatrix = { cosOfAngle, static_cast<T>(0), sinOfAngle, static_cast<T>(0),
										static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
										-sinOfAngle, static_cast<T>(0), cosOfAngle, static_cast<T>(0),
										static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };

		return yRotationMatrix;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		T cosOfAngle = cos(aAngleInRadians);
		T sinOfAngle = sin(aAngleInRadians);
		Matrix44<T> zRotationMatrix = { cosOfAngle, -sinOfAngle, static_cast<T>(0), static_cast<T>(0),
										sinOfAngle, cosOfAngle, static_cast<T>(0), static_cast<T>(0),
										static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
										static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) };

		return zRotationMatrix;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::Transpose(const Matrix44<T>& aMatrixToTranspose)
	{
		Matrix44<T> transposedMatrix;

		transposedMatrix[0] = aMatrixToTranspose[0];
		transposedMatrix[1] = aMatrixToTranspose[4];
		transposedMatrix[2] = aMatrixToTranspose[8];
		transposedMatrix[3] = aMatrixToTranspose[12];

		transposedMatrix[4] = aMatrixToTranspose[1];
		transposedMatrix[5] = aMatrixToTranspose[5];
		transposedMatrix[6] = aMatrixToTranspose[9];
		transposedMatrix[7] = aMatrixToTranspose[13];

		transposedMatrix[8] = aMatrixToTranspose[2];
		transposedMatrix[9] = aMatrixToTranspose[6];
		transposedMatrix[10] = aMatrixToTranspose[10];
		transposedMatrix[11] = aMatrixToTranspose[14];

		transposedMatrix[12] = aMatrixToTranspose[3];
		transposedMatrix[13] = aMatrixToTranspose[7];
		transposedMatrix[14] = aMatrixToTranspose[11];
		transposedMatrix[15] = aMatrixToTranspose[15];

		return transposedMatrix;
	}

	template<class T>
	inline T& Matrix44<T>::operator[](const int & aIndex)
	{
		assert((aIndex >= 0 && aIndex < 16) && "Index out of range.");
		return myMatrix[aIndex];
	}

	template<class T>
	inline const T& Matrix44<T>::operator[](const int & aIndex) const
	{
		assert((aIndex >= 0 && aIndex < 16) && "Index out of range.");
		return myMatrix[aIndex];
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::operator+=(const Matrix44<T>& aMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			myMatrix[i] += aMatrix[i];
		}

		return *this;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::operator-=(const Matrix44<T>& aMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			myMatrix[i] -= aMatrix[i];
		}

		return *this;
	}

	template<class T>
	inline Matrix44<T> operator*(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		const std::array<T, 16>& m0 = aMatrix0.myMatrix;
		const std::array<T, 16>& m1 = aMatrix1.myMatrix;

		Matrix44<T> result;
		result[0] = (m0[0] * m1[0]) + (m0[1] * m1[4]) + (m0[2] * m1[8]) + (m0[3] * m1[12]);
		result[1] = (m0[0] * m1[1]) + (m0[1] * m1[5]) + (m0[2] * m1[9]) + (m0[3] * m1[13]);
		result[2] = (m0[0] * m1[2]) + (m0[1] * m1[6]) + (m0[2] * m1[10]) + (m0[3] * m1[14]);
		result[3] = (m0[0] * m1[3]) + (m0[1] * m1[7]) + (m0[2] * m1[11]) + (m0[3] * m1[15]);

		result[4] = (m0[4] * m1[0]) + (m0[5] * m1[4]) + (m0[6] * m1[8]) + (m0[7] * m1[12]);
		result[5] = (m0[4] * m1[1]) + (m0[5] * m1[5]) + (m0[6] * m1[9]) + (m0[7] * m1[13]);
		result[6] = (m0[4] * m1[2]) + (m0[5] * m1[6]) + (m0[6] * m1[10]) + (m0[7] * m1[14]);
		result[7] = (m0[4] * m1[3]) + (m0[5] * m1[7]) + (m0[6] * m1[11]) + (m0[7] * m1[15]);

		result[8] = (m0[8] * m1[0]) + (m0[9] * m1[4]) + (m0[10] * m1[8]) + (m0[11] * m1[12]);
		result[9] = (m0[8] * m1[1]) + (m0[9] * m1[5]) + (m0[10] * m1[9]) + (m0[11] * m1[13]);
		result[10] = (m0[8] * m1[2]) + (m0[9] * m1[6]) + (m0[10] * m1[10]) + (m0[11] * m1[14]);
		result[11] = (m0[8] * m1[3]) + (m0[9] * m1[7]) + (m0[10] * m1[11]) + (m0[11] * m1[15]);

		result[12] = (m0[12] * m1[0]) + (m0[13] * m1[4]) + (m0[14] * m1[8]) + (m0[15] * m1[12]);
		result[13] = (m0[12] * m1[1]) + (m0[13] * m1[5]) + (m0[14] * m1[9]) + (m0[15] * m1[13]);
		result[14] = (m0[12] * m1[2]) + (m0[13] * m1[6]) + (m0[14] * m1[10]) + (m0[15] * m1[14]);
		result[15] = (m0[12] * m1[3]) + (m0[13] * m1[7]) + (m0[14] * m1[11]) + (m0[15] * m1[15]);

		return result;
	}

	template<class T>
	inline Vector4<T> operator*(const Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		const std::array<T, 16> & matrix = aMatrix.myMatrix;

		Vector4<T> result;
		result.x = (aVector.x * matrix[0]) + (aVector.y * matrix[4]) + (aVector.z * matrix[8]) + (aVector.w * matrix[12]);
		result.y = (aVector.x * matrix[1]) + (aVector.y * matrix[5]) + (aVector.z * matrix[9]) + (aVector.w * matrix[13]);
		result.z = (aVector.x * matrix[2]) + (aVector.y * matrix[6]) + (aVector.z * matrix[10]) + (aVector.w * matrix[14]);
		result.w = (aVector.x * matrix[3]) + (aVector.y * matrix[7]) + (aVector.z * matrix[11]) + (aVector.w * matrix[15]);

		return result;
	}

	template<class T>
	inline Matrix44<T> Matrix44<T>::operator*=(const Matrix44<T>& aMatrix)
	{
		const std::array<T, 16>& m0 = myMatrix;
		const std::array<T, 16>& m1 = aMatrix.myMatrix;

		Matrix44<T> result;
		result[0] = (m0[0] * m1[0]) + (m0[1] * m1[4]) + (m0[2] * m1[8]) + (m0[3] * m1[12]);
		result[1] = (m0[0] * m1[1]) + (m0[1] * m1[5]) + (m0[2] * m1[9]) + (m0[3] * m1[13]);
		result[2] = (m0[0] * m1[2]) + (m0[1] * m1[6]) + (m0[2] * m1[10]) + (m0[3] * m1[14]);
		result[3] = (m0[0] * m1[3]) + (m0[1] * m1[7]) + (m0[2] * m1[11]) + (m0[3] * m1[15]);

		result[4] = (m0[4] * m1[0]) + (m0[5] * m1[4]) + (m0[6] * m1[8]) + (m0[7] * m1[12]);
		result[5] = (m0[4] * m1[1]) + (m0[5] * m1[5]) + (m0[6] * m1[9]) + (m0[7] * m1[13]);
		result[6] = (m0[4] * m1[2]) + (m0[5] * m1[6]) + (m0[6] * m1[10]) + (m0[7] * m1[14]);
		result[7] = (m0[4] * m1[3]) + (m0[5] * m1[7]) + (m0[6] * m1[11]) + (m0[7] * m1[15]);

		result[8] = (m0[8] * m1[0]) + (m0[9] * m1[4]) + (m0[10] * m1[8]) + (m0[11] * m1[12]);
		result[9] = (m0[8] * m1[1]) + (m0[9] * m1[5]) + (m0[10] * m1[9]) + (m0[11] * m1[13]);
		result[10] = (m0[8] * m1[2]) + (m0[9] * m1[6]) + (m0[10] * m1[10]) + (m0[11] * m1[14]);
		result[11] = (m0[8] * m1[3]) + (m0[9] * m1[7]) + (m0[10] * m1[11]) + (m0[11] * m1[15]);

		result[12] = (m0[12] * m1[0]) + (m0[13] * m1[4]) + (m0[14] * m1[8]) + (m0[15] * m1[12]);
		result[13] = (m0[12] * m1[1]) + (m0[13] * m1[5]) + (m0[14] * m1[9]) + (m0[15] * m1[13]);
		result[14] = (m0[12] * m1[2]) + (m0[13] * m1[6]) + (m0[14] * m1[10]) + (m0[15] * m1[14]);
		result[15] = (m0[12] * m1[3]) + (m0[13] * m1[7]) + (m0[14] * m1[11]) + (m0[15] * m1[15]);

		*this = result;

		return result;
	}

	template<class T>
	inline Matrix44<T> operator+(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		Matrix44<T> result;
		for (int i = 0; i < 16; ++i)
		{
			result[i] = aMatrix0[i] + aMatrix1[i];
		}

		return result;
	}

	template<class T>
	inline Matrix44<T> operator-(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		Matrix44<T> result;
		for (int i = 0; i < 16; ++i)
		{
			result[i] = aMatrix0[i] - aMatrix1[i];
		}

		return result;
	}

	template<class T>
	inline bool operator==(const Matrix44<T>& aMatrix0, const Matrix44<T>& aMatrix1)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (aMatrix0[i] != aMatrix1[i])
			{
				return false;
			}
		}

		return true;
	}

	template<class T>
	inline Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T>& aMatrix)
	{
		for (int i = 0; i < 16; ++i)
		{
			myMatrix[i] = aMatrix[i];
		}

		return *this;
	}
}

namespace CU = CommonUtilities;