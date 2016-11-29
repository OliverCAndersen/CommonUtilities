#pragma once
#include <assert.h>

#include "Macros.h"

#include <cstring>

namespace CommonUtilities
{
	template <typename Type, int capacity, typename CountType = unsigned short, bool useSafeMode = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);

		~VectorOnStack();

		VectorOnStack<Type, capacity, CountType, useSafeMode> & operator=(const VectorOnStack & aVectorOnStack);

		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aIndex);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aIndex);

		inline void Clear();
		inline void DeleteAll();

		inline CountType Size() const;

		//inline const Type& GetLast() const;
		inline Type GetLast() const;

	private:
		Type myData[capacity];
		CountType mySize;
	};

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline VectorOnStack<Type, capacity, CountType, useSafeMode>::VectorOnStack()
	{
		mySize = 0;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline VectorOnStack<Type, capacity, CountType, useSafeMode>::VectorOnStack(const VectorOnStack & aVectorOnStack)
	{
		*this = aVectorOnStack;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline VectorOnStack<Type, capacity, CountType, useSafeMode>::~VectorOnStack()
	{
		mySize = 0;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline VectorOnStack<Type, capacity, CountType, useSafeMode> & VectorOnStack<Type, capacity, CountType, useSafeMode>::operator=(const VectorOnStack & aVectorOnStack)
	{
		mySize = 0;

		if (useSafeMode)
		{
			for (CountType i = 0; i < aVectorOnStack.Size(); ++i)
			{
				myData[i] = aVectorOnStack[i];
			}
		}
		else
		{
			memcpy(myData, aVectorOnStack.myData, sizeof(Type) * capacity);
		}

		mySize = aVectorOnStack.Size();

		return *this;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline const Type & VectorOnStack<Type, capacity, CountType, useSafeMode>::operator[](const CountType & aIndex) const
	{
		assert((aIndex >= 0 && aIndex <= mySize - 1) && "Index out of range.");
		return myData[aIndex];
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline Type & VectorOnStack<Type, capacity, CountType, useSafeMode>::operator[](const CountType & aIndex)
	{
		assert((aIndex >= 0 && aIndex <= mySize - 1) && "Index out of range.");
		return myData[aIndex];
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::Add(const Type & aObject)
	{
		assert((mySize < capacity) && "VectorOnStack is full.");
		myData[mySize] = aObject;
		mySize += 1;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::Insert(CountType aIndex, Type & aObject)
	{
		assert(((aIndex >= 0 && aIndex <= mySize - 1) && mySize < capacity) && "VectorOnStack is full");

		for (CountType i = mySize - 1; i >= aIndex; --i)
		{
			myData[i + 1] = myData[i];
		}

		mySize += 1;

		myData[aIndex] = aObject;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::DeleteCyclic(Type & aObject)
	{
		for (CountType i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				SAFEDELETE(myData[i]);

				myData[i] = myData[mySize - 1];

				mySize -= 1;
				return;
			}
		}

		assert(false && "Could not find a matching object in the VectorOnStack")
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::DeleteCyclicAtIndex(CountType aIndex)
	{
		assert((aIndex >= 0 && aIndex <= mySize - 1) && "Index out of range.");

		SAFEDELETE(myData[aIndex]);

		myData[aIndex] = myData[mySize - 1];

		mySize -= 1;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::RemoveCyclic(const Type & aObject)
	{
		for (CountType i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				myData[i] = myData[mySize - 1];
				mySize -= 1;
				return;
			}
		}

		assert(false && "Could not find a matching object in the VectorOnStack");
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::RemoveCyclicAtIndex(CountType aIndex)
	{
		assert((aIndex >= 0 && aIndex <= mySize - 1) && "Index out of range.");

		myData[aIndex] = myData[mySize - 1];

		mySize -= 1;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::Clear()
	{
		mySize = 0;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline void VectorOnStack<Type, capacity, CountType, useSafeMode>::DeleteAll()
	{
		for (CountType i = 0; i < mySize; ++i)
		{
			SAFEDELETE(myData[i]);
		}

		mySize = 0;
	}

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	__forceinline CountType VectorOnStack<Type, capacity, CountType, useSafeMode>::Size() const
	{
		return mySize;
	}

	/*template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline const Type & VectorOnStack<Type, capacity, CountType, useSafeMode>::GetLast() const
	{
		assert(mySize - 1 >= 0 && "Index out of range");
		return myData[mySize - 1];
	}*/

	template<typename Type, int capacity, typename CountType, bool useSafeMode>
	inline Type VectorOnStack<Type, capacity, CountType, useSafeMode>::GetLast() const
	{
		assert(mySize - 1 >= 0 && "Index out of range");
		return myData[mySize - 1];
	}
}

namespace CU = CommonUtilities;
