#pragma once
#include <vector>
#include "Plane.h"

namespace CommonUtilities 
{
	template <class T>
	class PlaneVolume
	{
	public:
		PlaneVolume();
		PlaneVolume(const std::vector<Plane<T>>& aPlaneList);
		void AddPlane(const Plane<T>& aPlane);
		bool Inside(const Vector3<T>& aPosition);

	private:
		std::vector<Plane<T>> myPlaneList;
	};

	template<class T>
	inline PlaneVolume<T>::PlaneVolume()
	{
	}

	template<class T>
	inline PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
	{
		myPlaneList = aPlaneList;
	}

	template<class T>
	inline void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
	{
		myPlaneList.push_back(aPlane);
	}

	template<class T>
	inline bool PlaneVolume<T>::Inside(const Vector3<T>& aPosition)
	{
		for (auto plane : myPlaneList)
		{
			if (!plane.Inside(aPosition))
			{
				return false;
			}
		}

		return true;
	}
}

namespace CU = CommonUtilities;