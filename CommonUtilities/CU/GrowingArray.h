#pragma once

#include <cstring>
#include <assert.h>
#include "Macros.h"

namespace CommonUtilities
{
	template<typename Type, typename CountType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(CountType aCapacity, bool aUseSafeMode = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray);

		void Init(CountType aCapacity, bool aUseSafeMode = true);
		void ReInit(CountType aCapacity, bool aUseSafeMode = true);

		inline Type& operator[](const CountType& aIndex);
		inline const Type& operator[](const CountType& aIndex) const;

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aIndex);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aIndex);
		inline CountType Find(const Type& aObject);

		inline Type& GetLast();
		inline const Type& GetLast() const;

		static const CountType FoundNone = -1;

		inline void RemoveAll();
		inline void DeleteAll();

		void Optimize();
		__forceinline CountType Size() const;
		inline void Resize(CountType aNewSize);
		inline void Reserve(CountType aNewCapacity);

	private:
		Type *myData;
		CountType mySize;
		CountType myCapacity;
		bool myUseSafeMode;
	};
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType>::GrowingArray()
	{
		mySize = static_cast<CountType>(0);
		myCapacity = static_cast<CountType>(0);
		myUseSafeMode = true;
		myData = nullptr;
	}

	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType>::GrowingArray(CountType aCapacity, bool aUseSafeMode)
	{
		mySize = static_cast<CountType>(0);
		myCapacity = aCapacity;
		myData = new Type[aCapacity];
		myUseSafeMode = aUseSafeMode;
	}
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType>::GrowingArray(const GrowingArray & aGrowingArray)
	{
		myCapacity = aGrowingArray.myCapacity;
		myData = new Type[myCapacity];
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		mySize = aGrowingArray.Size();

		if (myUseSafeMode || aGrowingArray.myUseSafeMode)
		{
			for (CountType i = 0; i < aGrowingArray.Size(); ++i)
			{
				myData[i] = aGrowingArray[i];
			}
		}
		else
		{
			memcpy(myData, aGrowingArray.myData, sizeof(Type) * mySize);
		}
	}
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType>::GrowingArray(GrowingArray && aGrowingArray)
	{
		myData = aGrowingArray.myData;
		aGrowingArray.myData = nullptr;
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
	}
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType>::~GrowingArray()
	{
		if (myData != nullptr)
		{
			delete[] myData;
			myData = nullptr;
		}
		mySize = static_cast<CountType>(0);
		myCapacity = static_cast<CountType>(0);
		myUseSafeMode = true;
	}
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType> & GrowingArray<Type, CountType>::operator=(const GrowingArray & aGrowingArray)
	{
		myCapacity = aGrowingArray.myCapacity;
		myData = new Type[myCapacity];
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		mySize = aGrowingArray.Size();

		if (myUseSafeMode || aGrowingArray.myUseSafeMode)
		{
			for (CountType i = 0; i < aGrowingArray.Size(); ++i)
			{
				myData[i] = aGrowingArray[i];
			}
		}
		else
		{
			memcpy(myData, aGrowingArray.myData, sizeof(Type) * mySize);
		}
		return *this;
	}
	template<typename Type, typename CountType>
	inline GrowingArray<Type, CountType> & GrowingArray<Type, CountType>::operator=(GrowingArray && aGrowingArray)
	{
		myData = aGrowingArray.myData;
		aGrowingArray.myData = nullptr;
		myCapacity = aGrowingArray.myCapacity;
		mySize = aGrowingArray.mySize;
		myUseSafeMode = aGrowingArray.myUseSafeMode;

		return *this;
	}
	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Init(CountType aCapacity, bool aUseSafeMode)
	{
		mySize = static_cast<CountType>(0);
		myCapacity = aCapacity;
		myData = new Type[myCapacity];
		myUseSafeMode = aUseSafeMode;
	}
	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::ReInit(CountType aCapacity, bool aUseSafeMode)
	{
		if (myData != nullptr)
		{
			delete[] myData;
		}
		myData = new Type[aCapacity];
		mySize = static_cast<CountType>(0);
		myCapacity = aCapacity;
		myUseSafeMode = aUseSafeMode;
	}
	template<typename Type, typename CountType>
	inline Type & GrowingArray<Type, CountType>::operator[](const CountType & aIndex)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert((aIndex >= static_cast<CountType>(0) && aIndex < mySize) && "Index out of range.");
		return myData[aIndex];
	}
	template<typename Type, typename CountType>
	inline const Type & GrowingArray<Type, CountType>::operator[](const CountType & aIndex) const
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert((aIndex >= static_cast<CountType>(0) && aIndex < mySize) && "Index out of range.");
		return myData[aIndex];
	}
	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Add(const Type & aObject)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		
		if (mySize == myCapacity)
		{
			Reserve(myCapacity * 2);
		}

		myData[mySize] = aObject;
		++mySize;
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Insert(CountType aIndex, Type & aObject)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert((aIndex >= static_cast<CountType>(0) && aIndex < mySize) && "Invalid index");
		
		if (mySize >= myCapacity)
		{
			Reserve(myCapacity * 2);
		}

		for (CountType i = mySize; i > aIndex; --i)
		{
			myData[i] = myData[i - 1];
		}
		mySize += 1;
		myData[aIndex] = aObject;
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::DeleteCyclic(Type & aObject)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		for (CountType i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				SAFE_DELETE(myData[i]);

				myData[i] = myData[mySize - 1];

				mySize -= 1;
				return;
			}
		}
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::DeleteCyclicAtIndex(CountType aIndex)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert((aIndex >= static_cast<CountType>(0) && aIndex < mySize) && "Index out of range.");

		SAFE_DELETE(myData[aIndex]);

		myData[aIndex] = myData[mySize - 1];

		mySize -= 1;
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::RemoveCyclic(const Type & aObject)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		for (CountType i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				myData[i] = myData[mySize - 1];
				mySize -= 1;
				return;
			}
		}
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::RemoveCyclicAtIndex(CountType aIndex)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert((aIndex >= static_cast<CountType>(0) && aIndex < mySize) && "Index out of range.");

		myData[aIndex] = myData[mySize - 1];

		mySize -= 1;
	}

	template<typename Type, typename CountType>
	inline CountType GrowingArray<Type, CountType>::Find(const Type & aObject)
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		for (CountType i = 0; i < mySize; ++i)
		{
			if (myData[i] == aObject)
			{
				return i;
			}
		}

		return FoundNone;
	}

	template<typename Type, typename CountType>
	inline Type & GrowingArray<Type, CountType>::GetLast()
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert(mySize > static_cast<CountType>(0) && "Array is empty");
		return myData[mySize - 1];
	}

	template<typename Type, typename CountType>
	inline const Type & GrowingArray<Type, CountType>::GetLast() const
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		assert(mySize > static_cast<CountType>(0) && "Array is empty");
		return myData[mySize - 1];
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::RemoveAll()
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		mySize = static_cast<CountType>(0);
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::DeleteAll()
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		for (CountType i = 0; i < mySize; ++i)
		{
			SAFE_DELETE(myData[i]);
		}
		mySize = static_cast<CountType>(0);
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Optimize()
	{
		assert(myData != nullptr && "GrowingArray is not initialised yet.");
		
		if (mySize < mySize)
		{
			Type* data = new Type[mySize];

			if (myUseSafeMode)
			{
				for (CountType i = 0; i < mySize; ++i)
				{
					data[i] = myData[i];
				}
			}
			else
			{
				memcpy(data, myData, sizeof(Type)*mySize);
			}
			delete[] myData;
			myData = data;
			myCapacity = mySize;
		}
	}

	template<typename Type, typename CountType>
	inline CountType GrowingArray<Type, CountType>::Size() const
	{
		return mySize;
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Resize(CountType aNewSize)
	{
		if (aNewSize > myCapacity)
		{
			Reserve(aNewSize);
		}
		else
		{
			mySize = aNewSize;
		}
	}

	template<typename Type, typename CountType>
	inline void GrowingArray<Type, CountType>::Reserve(CountType aNewCapacity)
	{
		assert((aNewCapacity >= myCapacity) && "You can't reserve a lower capacity than your current capacity");

		if (aNewCapacity > myCapacity)
		{
			Type* data = new Type[aNewCapacity];
			if (myUseSafeMode)
			{
				for (CountType i = 0; i < mySize; ++i)
				{
					data[i] = myData[i];
				}
			}
			else
			{
				memcpy(data, myData, sizeof(Type) * mySize);
			}
			delete[] myData;
			myData = data;
			myCapacity = aNewCapacity;
		}
	}
};

namespace CU = CommonUtilities;

