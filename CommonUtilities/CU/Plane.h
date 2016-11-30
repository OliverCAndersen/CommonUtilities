#pragma once
#include "Vector3.h"
namespace CommonUtilities
{

	template <class T>
	class Plane
	{
	public:
		Plane();
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);
		void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
		bool Inside(const Vector3<T>& aPosition) const;

	private:
		Vector3<T> myPoint;
		Vector3<T> myNormal;
	};

	template<class T>
	inline Plane<T>::Plane()
	{
		myPoint = Vector3<T>(0, 0, 0);
		myNormal = Vector3<T>(0, 0, 0);
	}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		myNormal = (aPoint1 - aPoint0).Cross((aPoint2 - aPoint0));
		myNormal.Normalize();
	}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
	{
		myPoint = aPoint0;
		myNormal = aNormal;
	}

	template<class T>
	inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		myNormal = (aPoint1 - aPoint0).Cross((aPoint2 - aPoint0));
		myNormal.Normalize();
	}

	template<class T>
	inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
	{
		myPoint = aPoint;
		myNormal = aNormal;
	}

	template<class T>
	inline bool Plane<T>::Inside(const Vector3<T>& aPosition) const
	{
		T result = myNormal.Dot(aPosition - myPoint);

		if (result < 0)
		{
			return true;
		}
		return false;
	}
}

namespace CU = CommonUtilities;