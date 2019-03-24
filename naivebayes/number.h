#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector< vector<char> > ReadFileStoreImage(std::string file_name, int index);

vector< vector<char> > CreateCharVector(vector<std::string> &lines_from_file);

int PrintTwoDVector(vector< vector<char> > to_print);

const int kDimension = 28;

const int kDigits = 10;

const char kWhite = ' ';

const char kGray = '+';

const char kBlack = '#';

vector<int> ReadIntsFromFile(std::string file_name);

vector<double> ReadDoublesFromFile(std::string file_name);

vector<int> GetIndexesForDigit(int digit, std::string file_name);

vector <vector< vector<char> > > ReadFileStoreImages(std::string file_name);

vector <vector< vector<double> > > ReadProbabilitiesFromFile(std::string file_name);

vector <int> FindValuesAtIndexes(vector <int> indexes, vector<int> values);

int CountInstancesOfDigit(int digit, vector<int> numbers);

int ReturnIndexOfMaxValue(vector<double> numbers);


class training_model {
public:
	const int kLaplaceVal = .1;
	
	vector <vector< vector<double> > > ComputeFeaturesModel(std::string images_file, std::string images_label, bool is_feature_one);
	vector <vector< vector<double> > > CreateComposites(vector <vector< vector<double> > > training_model);
	vector <double> ComputeIndependentClassPriors(std::string file_name);
	int WriteIndependentClassPriorsToFile(std::string training_labels, std::string file_name);
	int WriteFeaturesProbabilitiesToFile(vector <vector< vector<double> > > training_model, std::string file_name);
};

class classifier {
public:
	vector <int> ClassifyImages(std::string images_to_classify, vector <vector< vector<double> > > black_feature_probabilities, vector <vector< vector<double> > > white_feature_probabilities, vector <double> independent_class_priors);
	double ReportClassificationAccuracy(vector<int> classifications, std::string test_labels);
	vector< vector<double> > ComputeConfusionMatrix(vector<int> classifications, std::string test_labels);



};