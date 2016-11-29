#pragma once
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2<T>();

		Vector2<T>(const T& aX, const T& aY);

		Vector2<T>(const Vector2<T>& aVector) = default;

		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;

		~Vector2<T>() = default;

		void Set(const T& aX, const T& aY);

		T Length2() const;

		T Length() const;

		Vector2<T> GetNormalized() const;

		void Normalize();

		T Dot(const Vector2<T>& aVector) const;
	};

	template <class T> Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
	}

	template <class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
	}

	template <class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
	}

	template <class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return Vector2<T>(aScalar * aVector.x, aScalar * aVector.y);
	}

	template <class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T>(aVector.x / aScalar, aVector.y / aScalar);
	}

	template <class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}

	template <class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}

	template <class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}

	template <class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}

	template<class T> inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template<class T> inline Vector2<T>::Vector2(const T & aX, const T & aY)
	{
		x = aX;
		y = aY;
	}

	template<class T> inline void Vector2<T>::Set(const T& aX, const T& aY)
	{
		x = aX;
		y = aY;
	}

	template<class T> inline T Vector2<T>::Length2() const
	{
		return (x*x + y*y);
	}

	template<class T>
	inline T Vector2<T>::Length() const
	{
		return sqrt(x*x + y*y);
	}

	template<class T> inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = sqrt(x*x + y*y);
		Vector2<T> normalized;
		normalized.x = x / length;
		normalized.y = y / length;
		return normalized;
	}

	template<class T> inline void Vector2<T>::Normalize()
	{
		T length = sqrt(x*x + y*y);
		x /= length;
		y /= length;
	}

	template<class T> inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		return{ (x * aVector.x) + (y * aVector.y) };
	}
}

namespace CU = CommonUtilities;