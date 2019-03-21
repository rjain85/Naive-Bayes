#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector< vector<char> > ReadFileStoreImage(std::string file_path, int index);

vector< vector<char> > CreateCharVector(vector<std::string> lines_from_file);

int PrintTwoDVector(vector< vector<char> > to_print);

const int kDimension = 28;