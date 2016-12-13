#pragma once
#include <cmath>

namespace CommonUtilities 
{

template <class T>
class Vector3
{ 
public:
	T x;
	T y;
	T z;

	Vector3<T>();

	Vector3<T>(const T& aX, const T& aY, const T& aZ);

	Vector3<T>(const Vector3<T>& aVector) = default;

	Vector3<T>& operator=(const Vector3<T>& aVector3) = default;

	~Vector3<T>() = default;

	void Set(const T& aX, const T& aY, const T& aZ);

	T Length2() const;

	T Length() const;

	Vector3<T> GetNormalized() const;

	void Normalize();

	T Dot(const Vector3<T>& aVector) const;

	Vector3<T> Cross(const Vector3<T>& aVector) const;
};

	template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1) 
	{
		return Vector3<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y, aVector0.z + aVector1.z);
	}

	template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1) 
	{
		return Vector3<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y, aVector0.z - aVector1.z);
	}

	template <class T> Vector3<T> operator-(const Vector3<T>& aVector)
	{
		return Vector3<T>(-aVector.x, -aVector.y, -aVector.z);
	}

	template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar) 
	{
		return Vector3<T>(aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}

	template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return Vector3<T>(aScalar * aVector.x, aScalar * aVector.y, aScalar * aVector.z);
	}

	template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T>(aVector.x / aScalar, aVector.y / aScalar, aVector.z / aScalar);
	}

	template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}

	template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}

	template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}

	template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}

	template<class T> inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template<class T> inline Vector3<T>::Vector3(const T & aX, const T & aY, const T & aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T> inline void Vector3<T>::Set(const T& aX, const T& aY, const T& aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T> inline T Vector3<T>::Length2() const
	{
		return (x*x + y*y + z*z);
	}

	template<class T> inline T Vector3<T>::Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	template<class T> inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		T length = sqrt(x*x + y*y + z*z);
		Vector3<T> normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		normalized.z = z / length;
		return normalized;
	}

	template<class T> inline void Vector3<T>::Normalize()
	{
		T length = sqrt(x*x + y*y + z*z);
		x /= length;
		y /= length;
		z /= length;
	}

	template<class T> inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		return (x * aVector.x) + (y * aVector.y) + (z * aVector.z);
	}

	template<class T> inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		Vector3<T> crossProduct;
		crossProduct.x = (y * aVector.z) - (z * aVector.y);
		crossProduct.y = (z * aVector.x) - (x * aVector.z);
		crossProduct.z = (x * aVector.y) - (y * aVector.x);
		return crossProduct;
	}
}

namespace CU = CommonUtilities;