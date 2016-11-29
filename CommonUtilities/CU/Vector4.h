#pragma once
#include <cmath>

namespace CommonUtilities
{

	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4<T>();

		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);

		Vector4<T>(const Vector4<T>& aVector) = default;

		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;

		~Vector4<T>() = default;

		void Set(const T& aX, const T& aY, const T& aZ, const T& aW);

		T Length2() const;

		T Length() const;

		Vector4<T> GetNormalized() const;

		void Normalize();

		T Dot(const Vector4<T>& aVector) const;
	};

	template <class T> Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z, aVector0.w + aVector1.w);
	}

	template <class T> Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		return Vector4<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z, aVector0.w - aVector1.w);
	}

	template <class T> Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}

	template <class T> Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return Vector4<T>(aScalar * aVector.x, aScalar * aVector.y, aScalar * aVector.z, aVector.w * aScalar);
	}

	template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T>(aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar, aVector.w / aScalar);
	}

	template <class T> void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}

	template <class T> void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}

	template <class T> void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}

	template <class T> void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
	}

	template<class T> inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<class T> inline Vector4<T>::Vector4(const T & aX, const T & aY, const T & aZ, const T & aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<class T> inline void Vector4<T>::Set(const T& aX, const T& aY, const T& aZ, const T& aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<class T> inline T Vector4<T>::Length2() const
	{
		return (x*x + y*y + z*z + w*w);
	}

	template<class T> inline T Vector4<T>::Length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}

	template<class T> inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = sqrt(x*x + y*y + z*z + w*w);
		Vector4<T> normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		normalized.z = z / length;
		normalized.w = w / length;
		return normalized;

	}

	template<class T> inline void Vector4<T>::Normalize()
	{
		T length = sqrt(x*x + y*y + z*z + w*w);
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	template<class T> inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		return (x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w);
	}
}

namespace CU = CommonUtilities;