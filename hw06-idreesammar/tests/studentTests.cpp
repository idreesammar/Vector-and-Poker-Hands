#include "catch.hpp"

#include "Cards.h"
#include "ITPVector.hpp"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests
TEST_CASE("Vector tests", "[student]") 
{
	// Complete tests are worth 2 points for each test

	
	SECTION("Default constructor, size, capacity, and destructor")
	{
		ITPVector<int> testVect; // vector to be tested (created with default constructor)

		// check size, capacity
		REQUIRE(testVect.size() == 0);
		REQUIRE(testVect.capacity() == 10); // should match initial capacity
		
		// testVect.~ITPVector(); // call destructor for testing (if test runs fine, it works)
	}

	SECTION("Parameterized constructor, size, capacity, and destructor")
	{		
		ITPVector<int> testVect(4); // vector to be tested (created with param constructor)

		// check size, capacity 
		REQUIRE(testVect.size() == 0);
		REQUIRE(testVect.capacity() == 4); // should match inputted capacity

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	// test vector for sections below (note: it used the param constructor)
	ITPVector<int> testVect(3);

	SECTION("Push_back x1, back, pop_back, destructor")  // NOTE: this test is not checking exceptions 
	{
		testVect.push_back(5); // add an element with pushback
		REQUIRE(testVect[0] == 5); // confirm element was placed in vector
		REQUIRE(testVect.size() == 1); // check size of vector increased

		// test back and popback
		REQUIRE(testVect.back() == 5);
		testVect.pop_back(); 
		REQUIRE(testVect.size() == 0); // make sure pop_back decremented

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	SECTION("Push_back x3, operator[], destructor") // note: this test is not checking exception cases to []
	{
		// add 3 elements with push back (still within capacity)
		testVect.push_back(5); 
		testVect.push_back(6);
		testVect.push_back(7);
		REQUIRE(testVect.size() == 3);

		// check using [] operator
		REQUIRE(testVect[0] == 5); 
		REQUIRE(testVect[1] == 6);
		REQUIRE(testVect[2] == 7);

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	SECTION("Push_back (over capacity), size, capacity, destructor")
	{
		// add 4 elements with push back (goes over capacity of 3)
		testVect.push_back(5);
		int* origAddress = &testVect.data()[0]; // will hold address of first array element before vector is resized (and new array is made)

		testVect.push_back(6);
		testVect.push_back(7);
		testVect.push_back(8);

		// check size, capacity
		REQUIRE(testVect.size() == 4);
		REQUIRE(testVect.capacity() == 6); // capacity should have doubled due to Capacity multiplier

		REQUIRE(&testVect.data()[0] != origAddress); // should have changed as new array was dynamically allocated

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	SECTION("Push_back (over capacity), operator[], destructor")
	{
		// add 4 elements with push back (goes over capacity of 3)
		testVect.push_back(5);
		testVect.push_back(6);
		testVect.push_back(7);
		testVect.push_back(8);

		// check operator[]
		REQUIRE(testVect[0] == 5);
		REQUIRE(testVect[1] == 6);
		REQUIRE(testVect[2] == 7);
		REQUIRE(testVect[3] == 8);

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	SECTION("Push_back, pop_back, back, operator[], exceptions") // will check exceptions cases for these functions (normal cases already tested in other sections)
	{
		// currently, testVect has capacity 3, but size = 0 (no elements)
		std::ostringstream oss; // output string stream

		///////////////////////////////////////////////////////////////////////////////////
		// check back exceptions
		try
		{
			testVect.back(); // will cause error due to 0 elements in vector
		}
		catch (const std::exception& e)
		{
			oss << e.what();  // output error message to stream
		}
		REQUIRE(oss.str() == "Invalid function call. No elements in vector!"); // confirm stream error message
		oss.clear();  // clear the output stream
		oss.str("");

		////////////////////////////////////////////////////////////////////////////////////
		// check pop_back exception
		try
		{
			testVect.pop_back(); // will cause error due to 0 elements in vector
		}
		catch (const std::exception& e)
		{
			oss << e.what();  // output error message to stream
		}
		REQUIRE(oss.str() == "Invalid function call. No elements in vector!"); // confirm stream error message
		oss.clear();  // clear the output stream
		oss.str("");

		///////////////////////////////////////////////////////////////////////////////////
		// test push_back exception (over capacity) -- check new underlying array made when going over capacity
		// add 4 elements with push back (goes over capacity of 3)
		testVect.push_back(5);
		int* origAddress = &testVect.data()[0]; // will hold address of first array element before vector is resized (and new array is made)
		testVect.push_back(6);
		int* origAddress2 = &testVect.data()[1]; // will hold address of second array element before vector is resized (and new array is made)
		testVect.push_back(7);
		int* origAddress3 = &testVect.data()[2]; // will hold address of third array element before vector is resized (and new array is made)
		testVect.push_back(8);

		REQUIRE(testVect.capacity() == 6); // capacity should have doubled due to Capacity multiplier

		// check to see if address changed since new array should have been dynamically allocated (only for first three elements, 4th added to new array only)
		REQUIRE(&testVect.data()[0] != origAddress);
		REQUIRE(&testVect.data()[1] != origAddress2);
		REQUIRE(&testVect.data()[2] != origAddress3);

		//////////////////////////////////////////////////////////////////////////////////
		// check [] operator exceptions
		try
		{
			testVect[4]; // will cause error since testVect only has size 4 at the moment (no fifth element)
		}
		catch (const std::exception& e)
		{
			oss << e.what();  // output error message to stream
		}
		REQUIRE(oss.str() == "Invalid function call. Index is out of vector size bounds!"); // confirm stream error message
		oss.clear();  // clear the output stream
		oss.str("");

		try
		{
			testVect[4] = 5; // will cause error since testVect only has size 4 at the moment (no fifth element)
		}
		catch (const std::exception& e)
		{
			oss << e.what();  // output error message to stream
		}
		REQUIRE(oss.str() == "Invalid function call. Index is out of vector size bounds!"); // confirm stream error message
		oss.clear();  // clear the output stream
		oss.str("");
	}

	SECTION("Push_back (over capacity), operator[] (with assignment), destructor")
	{
		// add 4 elements with push back (goes over capacity of 3)
		testVect.push_back(5);
		testVect.push_back(6);
		testVect.push_back(7);
		testVect.push_back(8);

		// check [] assignment by reassigning some values using []
		testVect[0] = 15;
		REQUIRE(testVect[0] == 15); // make sure assignment worked
		testVect[3] = 18;
		REQUIRE(testVect[3] == 18); // make sure assignment worked

		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	SECTION("Clear")
	{
		// first add elements
		testVect.push_back(1);
		testVect.push_back(2); // so now size is 2

		int origCapacity = testVect.capacity(); // holds original capacity
		
		testVect.clear(); // call clear
		REQUIRE(testVect.size() == 0); // size should reset to 0 (no longer 2)
		REQUIRE(testVect.capacity() == origCapacity); // capacity should be same
	}

	SECTION("Destructor")
	{
		// will be using testVect declared above
		// testVect.~ITPVector(); // call destructor (if test runs fine, it works)
	}

	// for last 2 unit tests, will add elements to be used for previously made testVect
	testVect.push_back(1);
	testVect.push_back(2);
	testVect.push_back(3);

	SECTION("Copy constructor deep copies")
	{
		ITPVector<int> newVect = testVect; // calling the copy constructor

		// using a for loop, compare element values and addresses
		for (int i = 0; i < testVect.size(); i++)
		{
			REQUIRE(newVect[i] == testVect[i]);  // make sure values are same
			REQUIRE(&(newVect[i]) != &(testVect[i]));  // make sure addresses are DIFFERENT (for deep copies)
		}
	}

	SECTION("Assignment operator deep copies")
	{
		ITPVector<int> newVect; // create new vector (but not assignment yet, so no copy constructor called)
		// now use assignment operator 
		newVect = testVect;

		// using a for loop, compare element values and addresses
		for (int i = 0; i < testVect.size(); i++)
		{
			REQUIRE(newVect[i] == testVect[i]);  // make sure values are same
			REQUIRE(&(newVect[i]) != &(testVect[i]));  // make sure addresses are DIFFERENT (for deep copies)
		}
	}

	// Complete tests for this section is worth 24 points
}


