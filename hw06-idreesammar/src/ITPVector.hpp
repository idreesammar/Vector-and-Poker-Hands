#pragma once
#include <sstream>
#include <ostream>
#include <stdexcept>

template <typename T>
class ITPVector
{
	const unsigned INITIAL_CAPACITY = 10;
	const unsigned CAPACITY_MULTIPLIER = 2;
public:
	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of INITIAL_SIZE and a size of 0.
	// It also dynamically allocates the underlining array data
	// Input: None
	// Returns: Nothing
	ITPVector()
	{
		// set initial values for member variables
		mCapacity = INITIAL_CAPACITY; // Set the capacity to the initial default
		mSize = 0; // Set the size to 0
		
		// dynamically allocate array of initial capcity plus save address
		mArray = new T[mCapacity];
	}

	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of inputted value.
	// It also dynamically allocates the underlining array data
	// Input: Unsigned integer
	// Returns: Nothing
	ITPVector(unsigned inCapacity)
	{
		// set initial values for member variables
		mCapacity = inCapacity; // set to inputted capacity value
		mSize = 0; // Set the size to 0

		// dynamically allocate array of inputted capcity plus save address
		mArray = new T[mCapacity];
	}

	// Function: Copy Constructor
	// Purpose: Initializes the ITP vector to have a
	// copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector(const ITPVector<T>& other)
	{
		// 1. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size(); // set capacity to other vector's size
		mSize = 0; // set size to 0

		// 2. Create a new underlying array with the new capacity
		mArray = new T[mCapacity]; 

		// 3. Iterate over the other vector and push_back items to the new vector
		for (int i = 0; i < other.size(); i++)
		{
			this->push_back(other[i]); // using push_back function
		}
	}

	// Function: Assignment operator
	// Purpose: Clears the current vector and sets
	// the vector to have a copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector<T>& operator=(const ITPVector<T>& other)
	{
		this->clear(); // 1. Call the clear function
		delete[] mArray;// 2. Delete the current array

		// 3. Set the new capacity to the other’s size and size = 0
		mCapacity = other.size(); // set capacity to other vector's size
		mSize = 0; // set size to 0
		
		// 4. Create a new underlying array with the new capacity
		mArray = new T[mCapacity]; 

		// 5. Iterate over the other vector and push_back items to the new vector
		for (int i = 0; i < other.size(); i++)
		{
			this->push_back(other[i]); // using push_back function
		}

		return *this; // 6. By convention, operator= returns *this
	}

	// Function: Destructor
	// Purpose: Deletes the underlying array and
	// sets size/capacity to zero
	// Input: None
	// Returns: Nothing
	~ITPVector()
	{
		// delete the underlying array
		delete[] mArray;
		mArray = nullptr;

		// set other member variables to 0
		mCapacity = 0;
		mSize = 0;
	}

	// Function: clear
	// Purpose: Emptys the current vector
	// Input: None
	// Returns: None
	void clear()
	{
		delete[] mArray; // 1. Call delete[] on the underlying array
		mArray = new T[mCapacity]; // 2. Create a new underlying array using the old capacity 
		mSize = 0; // 3. Set size back to 0
	}

	// Function: empty
	// Purpose: Returns true if the vector is empty
	// Input: None
	// Returns: Boolean
	bool empty()
	{
		bool outcome = false; // boolean indicating outcome of this function

		// check if size is 0
		if (mSize == 0)
		{
			outcome = true;
		}

		return outcome; // return the result
	}
	
	// Function: capacity
	// Purpose: Returns the current capacity of the underlying array data
	// Input: None
	// Returns: Capacity of underlying array data
	unsigned capacity() const
	{
		// return the vector's capacity value
		return mCapacity;
	}

	// Function: size
	// Purpose: Returns the current size of the vector
	// Input: None
	// Returns: Size of vector
	unsigned size() const
	{
		// return the vector's size
		return mSize;
	}

	// Function: data
	// Purpose: Returns the pointer to the underlying array
	// Input: None
	// Returns: T*
	T* data() const
	{
		// returns the pointer to the vectors data array
		return mArray;
	}

	// Function: Subscript operator (read/write version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	T& operator[](unsigned index)
	{
		// 1. If index >= size – error!
		if (index >= mSize)
		{
			throw std::out_of_range("Invalid function call. Index is out of vector size bounds!");
		}

		return mArray[index]; // 2. Return the value at the requested index
	}

	// Function: Subscript operator (read-only version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	const T& operator[](unsigned index) const
	{
		// 1. If index >= size – error!
		if (index >= mSize)
		{
			throw std::out_of_range("Invalid function call. Index is out of vector size bounds!");
		}

		return mArray[index]; // 2. Return the value at the requested index
	}

	// Function: insert_back
	// Purpose: Adds the specified element to the end of the ITPVector
	// It automatically reallocates the underlying array if we are
	// going over capacity
	// Input: Value to add (by const reference)
	// Returns: Nothing
	void push_back(const T& value)
	{
		// when size is equal to capacity (NOTE: it will never go over, due to how this function is set up)
		if (mSize == mCapacity)
		{
			mCapacity = mCapacity * CAPACITY_MULTIPLIER; // Increase the capacity 
			T* newArray = new T[mCapacity]; // Dynamically allocate a new underlying array w/ new capacity

			// Copy the data from the old array to the new array
			for (int i = 0; i < mSize; i++)
			{
				newArray[i] = mArray[i]; // carry over the data values
			}

			delete[] mArray; // Delete the old array
			mArray = newArray; // Set pointer to the new array
		}

		// the rest occurs whether the size is less than OR equal to the capacity
		mArray[mSize] = value; // Add an element at index, size
		mSize++; // Increment size by 1
	}

	// Function: get_back
	// Purpose: Returns the current last element in the vector
	// Does not remove this element from the vector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Value at back of vector, by reference
	T& back()
	{
		// 1. If size == 0 – error!
		if (mSize == 0)
		{
			throw std::out_of_range("Invalid function call. No elements in vector!");
		}
		return mArray[mSize - 1]; // 2. Return the element at size - 1 (last element)
	}

	// Function: remove_back
	// Purpose: Removes the last element from the ITPVector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Nothing
	void pop_back()
	{
		// 1. If size == 0 – error!
		if (mSize == 0)
		{
			throw std::out_of_range("Invalid function call. No elements in vector!");
		}

		mSize--; // 2. Decrement size by 1
	}

	// Function: Output Stream Operator
	// Purpose: Prints the contents of the vector to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, vector to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPVector<T>& vector)
	{
		os << "{"; // first output the starting brace

		// loop through contents and display values
		for (int i = 0; i < vector.size(); i++)
		{
			if (i == vector.size() - 1)  // for last element in vector
			{
				os << vector[i] << "}"; // needs ending brace
			}
			else  // not the last element in vector
			{
				os << vector[i] << ", "; // needs comma and space
			}
		}

		return os; // return the output stream with values written
	}

private:
	// Define member variables 
	unsigned mCapacity; // holds the vector's data capacity
	unsigned mSize; // the current # of elements in the vector
	T* mArray; // pointer to an underlying array 
};
