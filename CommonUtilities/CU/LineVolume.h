#pragma once
#include <vector>
#include "Line.h"
namespace CommonUtilities
{

	template <class T>
	class LineVolume
	{
	public:
		LineVolume();
		LineVolume(const std::vector<Line<T>>& aLineList);
		void AddLine(const Line<T>& aLine);
		bool Inside(const Vector2<T>& aPosition);

	private:
		std::vector<Line<T>> myLineList;
	};

	template<class T>
	inline LineVolume<T>::LineVolume()
	{
	}

	template<class T>
	inline LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLineList = aLineList;
	}

	template<class T>
	inline void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLineList.push_back(aLine);
	}

	template<class T>
	inline bool LineVolume<T>::Inside(const Vector2<T>& aPosition)
	{
		for (auto line : myLineList)
		{
			if (!line.Inside(aPosition))
			{
				return false;
			}
		}

		return true;
	}
}

namespace CU = CommonUtilities;