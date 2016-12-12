#pragma once
/*
#include <type_traits>

namespace CommonUtilities
{
	enum class CompareType
	{
		Equals,
		GreaterThan,
		LesserThan
	};

	template <typename T, typename Q>
	bool EraseLoop(T& aContainer, Q aValue)//, CompareType aCompareType)
	{
		if (std::is_same<Q, decltype(*(aContainer.begin()))>::value == true)
		{
			for (auto it = aContainer.rbegin(); it != aContainer.rend(); it--)
			{
				if ((*it) == aValue)
				{
					aContainer.erase(it);
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}
}

namespace CU = CommonUtilities;

*/