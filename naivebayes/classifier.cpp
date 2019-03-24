#include "number.h"

vector<int> classifier::ClassifyImages(std::string images_to_classify, vector<vector<vector<double>>> black_feature_probabilities, vector<vector<vector<double>>> white_feature_probabilities, vector<double> independent_class_priors) {
	vector <vector< vector<char> > > to_classify = ReadFileStoreImages(images_to_classify);

	vector <int> classifications;
	classifications.resize(to_classify.size());

	// loop through every image that is to be classified
	for (int i = 0; i < to_classify.size(); i++) {
		//initialize a vector of posterior probabilties for each digit
		vector<double> posterior_probabilities;
		posterior_probabilities.resize(kDigits);
		//loop through each digit
		for (int digit = 0; digit < kDigits; digit++) {
			posterior_probabilities[digit] += log10(independent_class_priors[digit]);
			for (int j = 0; j < to_classify[i].size(); j++) {
				for (int k = 0; k < to_classify[i][j].size(); k++) {
					if (to_classify[i][j][k] == kWhite) {
						posterior_probabilities[digit] += log10(white_feature_probabilities[digit][j][k]);

					}
					if (to_classify[i][j][k] == kGray || to_classify[i][j][k] == kBlack) {
						posterior_probabilities[digit] += log10(black_feature_probabilities[digit][j][k]);
					}
				}
			}
		}
		classifications[i] = ReturnIndexOfMaxValue(posterior_probabilities);
	}
	return classifications;
}

double classifier::ReportClassificationAccuracy(vector<int> classifications, std::string test_labels) {
	vector<int> answers = ReadIntsFromFile(test_labels);
	double accuracy = 0;
	for (int i = 0; i < classifications.size(); i++) {
		if (classifications[i] == answers[i]) {
			accuracy++;
		}
	}
	return accuracy/classifications.size();
}

vector<vector<double>> classifier::ComputeConfusionMatrix(vector<int> classifications, std::string test_labels)
{
	return vector<vector<double>>();
}


