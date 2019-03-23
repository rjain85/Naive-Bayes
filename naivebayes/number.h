#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector< vector<char> > ReadFileStoreImage(std::string file_name, int index);

vector< vector<char> > CreateCharVector(vector<std::string> &lines_from_file);

int PrintTwoDVector(vector< vector<char> > to_print);

const int kDimension = 28;

vector<int> ReadNumbersFromFile(std::string file_name);

vector<int> GetIndexesForDigit(int digit, std::string file_name);

vector <vector< vector<char> > > ReadFileStoreImages(std::string file_name);


class training_model {
public:
	const int kLaplaceVal = .1;
	const char kWhite = ' ';
	const char kGray = '+';
	const char kBlack = '#';
	const int kDigits = 10;
	vector <vector< vector<double> > > CreateFeaturesModel(std::string images_file, std::string images_label, bool is_feature_one);
	vector <vector< vector<double> > > CreateComposites(vector <vector< vector<double> > > training_model);
};