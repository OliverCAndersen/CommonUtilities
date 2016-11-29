#pragma once
#include <assert.h>
#include "Macros.h"

namespace CommonUtilities
{
	template <typename Type, int size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		StaticArray<Type, size> & operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int& aIndex) const;
		inline Type& operator[](const int& aIndex);


		// Utility functions
		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();

	private:
		Type myData[size];
	};

	template<typename Type, int size>
	inline StaticArray<Type, size>::StaticArray() {}

	template<typename Type, int size>
	inline StaticArray<Type, size>::~StaticArray() {}

	template<typename Type, int size>
	inline StaticArray<Type, size>::StaticArray(const StaticArray & aStaticArray)
	{
		*this = aStaticArray;
	}

	template<typename Type, int size>
	inline StaticArray<Type, size> & StaticArray<Type, size>::operator=(const StaticArray & aStaticArray)
	{
		for (int i = 0; i < size; ++i)
		{
			myData[i] = aStaticArray[i];
		}

		return *this;
	}

	template<typename Type, int size>
	inline const Type & StaticArray<Type, size>::operator[](const int & aIndex) const
	{
		assert((aIndex >= 0 && aIndex <= size - 1) && "Index out of range.");
		return myData[aIndex];
	}

	template<typename Type, int size>
	inline Type & StaticArray<Type, size>::operator[](const int & aIndex)
	{
		assert((aIndex >= 0 && aIndex <= size - 1) && "Index out of range.");
		return myData[aIndex];
	}

	template<typename Type, int size>
	inline void StaticArray<Type, size>::Insert(int aIndex, Type & aObject)
	{
		assert((aIndex >= 0 && aIndex <= size - 1) && "Index out of range.");
		for (int i = size - 2; i >= aIndex; --i)
		{
			myData[i + 1] = myData[i];
		}

		myData[aIndex] = aObject;
	}

	template<typename Type, int size>
	inline void StaticArray<Type, size>::DeleteAll()
	{
		for (int i = size - 1; i >= 0; --i)
		{
			SAFEDELETE(myData[i]);
		}
	}
}