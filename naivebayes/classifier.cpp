#include "number.h"

// Take a vector of images and identify which digit each one represents
vector<int> classifier::ClassifyImages(std::string images_to_classify, vector<vector<vector<double>>> black_feature_probabilities, vector<vector<vector<double>>> white_feature_probabilities, vector<double> independent_class_priors) {
	vector <vector< vector<char> > > to_classify = ReadFileStoreImages(images_to_classify);

	vector <int> classifications;
	classifications.resize(to_classify.size());

	// loop through every image that is to be classified
	for (int i = 0; i < to_classify.size(); i++) {
		// initialize a vector of posterior probabilties for each digit
		vector<double> posterior_probabilities;
		posterior_probabilities.resize(kDigits);
		// loop through each digit
		for (int digit = 0; digit < kDigits; digit++) {
			// add the log of the independent class prior for that digit
			posterior_probabilities[digit] += log10(independent_class_priors[digit]);
			for (int j = 0; j < to_classify[i].size(); j++) {
				for (int k = 0; k < to_classify[i][j].size(); k++) {
					// if the pixel is white, add the log of the corresponding probability from the white feature vector
					if (to_classify[i][j][k] == kWhite) {
						posterior_probabilities[digit] += log10(white_feature_probabilities[digit][j][k]);

					}
					// if the pixel is gray or black, add the log of the corresponding probability from the black feature vector
					if (to_classify[i][j][k] == kGray || to_classify[i][j][k] == kBlack) {
						posterior_probabilities[digit] += log10(black_feature_probabilities[digit][j][k]);
					}
				}
			}
		}
		// find the digit with maximum posterior probability
		classifications[i] = ReturnIndexOfMaxValue(posterior_probabilities);
	}
	return classifications;
}

// Compare classifications to labels and return the accuracy percentage
double classifier::ReportClassificationAccuracy(vector<int> classifications, std::string test_labels) {
	vector<int> answers = ReadIntsFromFile(test_labels);
	double accuracy = 0;
	for (int i = 0; i < classifications.size(); i++) {
		if (classifications[i] == answers[i]) {
			accuracy++;
		}
	}
	accuracy = accuracy / classifications.size() * 100;
	cout << "Accuracy: " << accuracy << "%" << endl;
	return accuracy;
}

// Take the classifications and compare to labels to generate the confusion matrix
vector<vector<double>> classifier::ComputeConfusionMatrix(vector<int> classifications, std::string test_labels) {
	vector<vector<double>> confusion_matrix;
	confusion_matrix.resize(kDigits);

	// Go through each column (digits 0 - 9) of the matrix
	for (int column = 0; column < kDigits; column++) {
		// resize the matrix to accomodate the incoming values
		confusion_matrix[column].resize(kDigits);
		// Get the indexes for each digit in the test labels vector
		vector <int> indexes = GetIndexesForDigit(column, test_labels);
		double num_of_digits = indexes.size();
		// Find what we classified each digit as
		vector <int> classifications_of_digit = FindValuesAtIndexes(indexes, classifications);
		for (int row = 0; row < kDigits; row++) {
			// Compute the percentage of test images for that column that are classified as the digit.
			double instances_of_digit = CountInstancesOfDigit(row, classifications_of_digit);
			confusion_matrix[column][row] = instances_of_digit/num_of_digits;
		}
	}
	return confusion_matrix;
}

// Print the confusion matrix so that it is neat and aligned
int classifier::PrintConfusionMatrix(vector<vector<double>> to_print) {
	for (int i = 0; i < to_print.size(); i++) {
		for (int j = 0; j < to_print[i].size(); j++) {
			printf("%2f  ", to_print[i][j]);
		}
		cout << endl;
	}
	return 0;
}
