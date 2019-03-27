#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "naive_bayes.h"

using std::string;

TEST_CASE("Check if image vector is being populated by checking vector size and one pixel") {
	vector <vector< vector<char> > > test_vector = ReadFileStoreImages("trainingimages");
	REQUIRE((test_vector.size() == 5000));
	REQUIRE((test_vector[0].size() == 28));
	REQUIRE((test_vector[0][0].size() == 28));
	REQUIRE((test_vector[4999][27][27] == ' '));
}

TEST_CASE("Check if probabilities vector is being populated by checking vector size and one probability") {
	vector <vector< vector<double> > > test_vector = ReadProbabilitiesFromFile("blackfeaturesprobabilities.txt");
	REQUIRE((test_vector.size() == 10));
	REQUIRE((test_vector[0].size() == 28));
	REQUIRE((test_vector[0][0].size() == 28));
	REQUIRE((test_vector[9][27][27] == 0));
}

TEST_CASE("Read ints from file and put into a vector") {
	vector<int> test_vector; 
	test_vector.push_back(1);
	test_vector.push_back(2);
	test_vector.push_back(3);
	REQUIRE((ReadIntsFromFile("intsfromfile.txt") == test_vector));
}

TEST_CASE("Read doubles from file and put into a vector") {
	vector<int> test_vector;
	test_vector.push_back(1.5);
	test_vector.push_back(2.5);
	test_vector.push_back(3.5);
	REQUIRE((ReadIntsFromFile("doublesfromfile.txt") == test_vector));
}

TEST_CASE("Pass a digit and get indexes for every instance of that digit in the file") {
	vector<int> test_vector;
	test_vector.push_back(0);
	test_vector.push_back(3);
	REQUIRE((GetIndexesForDigit(1, "getindexesfordigit.txt") == test_vector));
}

TEST_CASE("Return index of maximum value in vector") {
	vector<double> test_vector;
	test_vector.push_back(0);
	test_vector.push_back(3.5);
	test_vector.push_back(1.5);
	test_vector.push_back(3.9);
	REQUIRE((ReturnIndexOfMaxValue(test_vector) == 3));
}

TEST_CASE("Takes a vector of indexes and returns the integers in a vector of values at those indexes") {
	vector<int> values_vector;
	values_vector.push_back(0);
	values_vector.push_back(4);
	values_vector.push_back(2);

	vector<int> indexes_vector;
	indexes_vector.push_back(1);
	indexes_vector.push_back(2);

	vector<int> answer_vector;
	answer_vector.push_back(4);
	answer_vector.push_back(2);

	REQUIRE((FindValuesAtIndexes(indexes_vector, values_vector) == answer_vector));
}

TEST_CASE("Take vector and count instances of specified digit") {
	vector<int> test_vector;
	test_vector.push_back(0);
	test_vector.push_back(3);
	test_vector.push_back(4);
	test_vector.push_back(4);
	REQUIRE((CountInstancesOfDigit(4, test_vector) == 2));
}
