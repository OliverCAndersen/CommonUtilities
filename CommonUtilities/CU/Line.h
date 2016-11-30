#pragma once
#include "Vector2.h"

namespace CommonUtilities
{
	template <class T>
	class Line
	{
	public:
		Line();
		Line(const Vector2<T> & aPoint0, const Vector2<T> & aPoint1);
		void InitWith2Points(const Vector2<T> & aPoint0, const Vector2<T> & aPoint1);
		void InitWithPointAndDirection(const Vector2<T> & aPoint, const Vector2<T> & aDirection);
		bool Inside(const Vector2<T> & aPosition) const;

	private:
		Vector2<T> myPoint;
		Vector2<T> myDirection;
		Vector2<T> myNormal;
	};

	template<class T>
	inline Line<T>::Line()
	{
		myPoint = Vector2<T>(0, 0);
		myDirection = Vector2<T>(0, 0);
		myNormal = Vector2<T>(0, 0);
	}

	template<class T>
	inline Line<T>::Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myPoint = aPoint0;
		myDirection = aPoint1 - aPoint0;
		myNormal = Vector2<T>(-myDirection.y, myDirection.x);
		myNormal.Normalize();
	}

	template<class T>
	inline void Line<T>::InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myPoint = aPoint0;
		myDirection = aPoint1 - aPoint0;
		myNormal = Vector2<T>(-myDirection.y, myDirection.x);
		myNormal.Normalize();
	}

	template<class T>
	inline void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myPoint = aPoint;
		myDirection = aDirection;
		myNormal = Vector2<T>(-myDirection.y, myDirection.x);
		myNormal.Normalize();
	}

	template<class T>
	inline bool Line<T>::Inside(const Vector2<T>& aPosition) const
	{
		T result = myNormal.Dot((aPosition - myPoint));

		if (result < 0)
		{
			return true;
		}
		return false;
	}
}

namespace CU = CommonUtilities;