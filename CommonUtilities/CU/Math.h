#pragma once

namespace CommonUtilities
{
	namespace Math
	{
		template<typename T>
		T Clamp(T aValue, T aMinValue, T aMaxValue)
		{
			if (aValue >= aMaxValue)
			{
				return aMaxValue;
			}
			else if (aValue <= aMinValue)
			{
				return aMinValue;
			}
			return aValue;
		}
	}
}

namespace CU = CommonUtilities;