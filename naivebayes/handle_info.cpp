#include "naive_bayes.h"

// opens a file and stores all the images in a 3d char vector
vector <vector< vector<char> > > ReadFileStoreImages(std::string file_name) {
	vector <vector< vector<char> > > images;
	vector<std::string> single_image;

	std::ifstream my_file;
	my_file.open(file_name);

	int counter = 0;
	if (my_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (my_file.is_open()) {
		std::string line;
		while (getline(my_file, line)) {
			single_image.push_back(line);
			counter++;
			if (counter == kDimension) {
				images.push_back(CreateCharVector(single_image));
				counter = 0;
				single_image.clear();
			}
		}
	}
	my_file.close();

	return images;
}

// open a file full of pregenerated probabilities, read it, and store the probabilities in a 3d vector
vector<vector<vector<double>>> ReadProbabilitiesFromFile(std::string file_name) {
	vector<vector<vector<double>>> features;
	features.resize(kDigits);

	vector<std::string> file_contents;
	std::ifstream my_file;
	my_file.open(file_name);

	if (my_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (my_file.is_open()) {
		std::string line;
		while (getline(my_file, line)) {
			file_contents.push_back(line);
		}
	}
	my_file.close();

	int index = 0;
	for (int i = 0; i < features.size(); i++) {
		features[i].resize(kDimension);
		for (int j = 0; j < features[i].size(); j++) {
			features[i][j].resize(kDimension);
			for (int k = 0; k < features[i][j].size(); k++) {
				double to_add = atof(file_contents[index].c_str());
				features[i][j][k] = to_add;
				index++;
			}
		}
	}
	return features;
}

// takes a vector of strings and creates a character vector
vector < vector <char> > CreateCharVector(vector<std::string> &lines_from_file) {
	vector < vector <char> > to_return;
	to_return.resize(kDimension);
	for (int i = 0; i < lines_from_file.size(); i++) {
		to_return[i].resize(kDimension);
		for (int j = 0; j < lines_from_file[i].length(); j++) {
			to_return[i][j] = lines_from_file[i].at(j);
		}
	}
	return to_return;
}

// takes a 3d vector and prints it in a neat format
int PrintThreeDVector(vector <vector< vector<double> > > to_print) {
	for (int i = 0; i < to_print.size(); i++) {
		for (int j = 0; j < to_print[i].size(); j++) {
			for (int k = 0; k < to_print[i][j].size(); k++) {
				cout << to_print[i][j][k];
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

// opens a file, reads integers, and stores them
vector<int> ReadIntsFromFile(std::string file_name) {
	std::ifstream my_file;
	my_file.open(file_name);
	vector<int> file_contents;

	if (my_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (my_file.is_open()) {
		std::string line;
		int counter = 0;
		while (getline(my_file, line)) {
			int num = atoi(line.c_str()); 
			file_contents.push_back(num);
		}
	}
	my_file.close();
	return file_contents;
}

// opens a file, reads doubles, and stores them
vector<double> ReadDoublesFromFile(std::string file_name) {
	std::ifstream my_file;
	my_file.open(file_name);
	vector<double> file_contents;

	if (my_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (my_file.is_open()) {
		std::string line;
		int counter = 0;
		while (getline(my_file, line)) {
			double num = atof(line.c_str());
			file_contents.push_back(num);
		}
	}
	my_file.close();
	return file_contents;
}

// opens a file, takes a digit, and finds the line index for every instance of that digit in the file
vector<int> GetIndexesForDigit(int digit, std::string file_name) {
	vector<int> indexes;
	vector<int> file_contents = ReadIntsFromFile(file_name);
	for (int i = 0; i < file_contents.size(); i++) {
		if (file_contents[i] == digit) {
			indexes.push_back(i);
		}
	}
	return indexes;
}

// takes a vector of numbers, finds the maximum number, and returns its index
int ReturnIndexOfMaxValue(vector<double> numbers) {
	double maximum = numbers[0];
	int index = 0;

	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] > maximum) {
			maximum = numbers[i];
			index = i;
		}
	}
	return index;
}

// takes a vector of indexes and vector of values, returns the integers in the vector of values at the specified indexes
vector <int> FindValuesAtIndexes(vector <int> indexes, vector<int> values) {
	vector <int> values_at_indexes;
	for (int index : indexes) {
		values_at_indexes.push_back(values[index]);
	}
	return values_at_indexes;
}

// takes a digit and a vector of numbers, returns the number of instances of that digit
int CountInstancesOfDigit(int digit, vector<int> numbers) {
	int counter = 0;
	for (int number : numbers) {
		if (number == digit) {
			counter++;
		}
	}
	return counter;
}

// runs the Naive Bayes classifier, taking in user input from the command line
int HandleUserInput(int argc, char *argv[]) {
	training_model model;
	classifier classifier;
	
	//if the user enters one argument, a brand new training model is generated
	if (argc == 2) {
		vector <vector< vector<double> > > black_features = model.ComputeFeaturesModel("trainingimages", "traininglabels", true);
		vector <vector< vector<double> > > white_features = model.ComputeFeaturesModel("trainingimages", "traininglabels", false);
		vector <double> priors = ReadDoublesFromFile("independentclasspriors.txt");
		vector <vector< vector<double> > > composite_images = model.CreateComposites(black_features);
		PrintThreeDVector(composite_images);
		vector<int> classifications = classifier.ClassifyImages("testimages", black_features, white_features, priors);
		classifier.ReportClassificationAccuracy(classifications, "testlabels");
		vector <vector <double> > confusion_matrix = classifier.ComputeConfusionMatrix(classifications, "testlabels");
		classifier.PrintConfusionMatrix(confusion_matrix);

	// if the user enters three arguments, the arguments are interpreted as file names and the training data is loaded from those files
	} else if(argc == 4) {
		vector <vector< vector<double> > > black_features = ReadProbabilitiesFromFile(argv[1]);
		vector <vector< vector<double> > > composite_images = model.CreateComposites(black_features);
		vector<vector<vector<double>>> white_features = ReadProbabilitiesFromFile(argv[2]);
		vector <double> priors = ReadDoublesFromFile(argv[3]);
		PrintThreeDVector(composite_images);
		vector<int> classifications = classifier.ClassifyImages("testimages", black_features, white_features, priors);
		classifier.ReportClassificationAccuracy(classifications, "testlabels");
		vector <vector <double> > confusion_matrix = classifier.ComputeConfusionMatrix(classifications, "testlabels");
		classifier.PrintConfusionMatrix(confusion_matrix);
	
	// if the user enters no arguments, a previously generated training model is use
	} else {
		vector <vector< vector<double> > > black_features = ReadProbabilitiesFromFile("blackfeaturesprobabilities.txt");
		vector <vector< vector<double> > > composite_images = model.CreateComposites(black_features);
		vector<vector<vector<double>>> white_features = ReadProbabilitiesFromFile("whitefeaturesprobabilities.txt");
		vector <double> priors = ReadDoublesFromFile("independentclasspriors.txt");
		PrintThreeDVector(composite_images);
		vector<int> classifications = classifier.ClassifyImages("testimages", black_features, white_features, priors);
		classifier.ReportClassificationAccuracy(classifications, "testlabels");
		vector <vector <double> > confusion_matrix = classifier.ComputeConfusionMatrix(classifications, "testlabels");
		classifier.PrintConfusionMatrix(confusion_matrix);
	}
	return 0;
}