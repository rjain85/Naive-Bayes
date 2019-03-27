#include "naive_bayes.h"

// compute a training model for either black(1) or white(0) feature
vector <vector< vector<double> > > training_model::ComputeFeaturesModel(std::string images_file, std::string images_labels, bool is_feature_one) {
	vector <vector< vector<char> > > training_images = ReadFileStoreImages("trainingimages");
	vector <vector< vector<double> > > features;
	features.resize(kDigits);

	for (int i = 0; i < kDigits; i++) {
		// Get a list of possible indexes for the digit in the training images file
		vector<int> indexes = GetIndexesForDigit(i, images_labels);
		features[i].resize(kDimension);
		// The following steps will be repeated for every image of that digit
		for (int index : indexes) {
			// Store the image at the index
			vector< vector<char> > image = training_images[index];
			for (int j = 0; j < image.size(); j++) {
				features[i][j].resize(kDimension);
				for (int k = 0; k < image.size(); k++) {
					// if that pixel in the image is black or gray, add 1 to the corresponding place in the 3d array
					features[i][j][k] += 0;
					if (is_feature_one && (image[j][k] == kBlack || image[j][k] == kGray)) {
						features[i][j][k] += 1;
					}
					// if the pixel in the image of white, add 1 to the corresponding place in the 3d array
					if (!is_feature_one && image[j][k] == kWhite) {
						features[i][j][k] += 1;
					}
				}
			}
		}
		// divide by number of training examples and apply Laplace smoothing
		for (int j = 0; j < features[i].size(); j++) {
			for (int k = 0; k < features[i][j].size(); k++) {
				features[i][j][k] += kLaplaceVal;
				features[i][j][k] = features[i][j][k] / (indexes.size() + 2 * kLaplaceVal);
			}
		}
	}
	return features;
}

// Generate composite images based off of a training model
vector <vector< vector<double> > > training_model::CreateComposites(vector <vector< vector<double> > > training_model) {
	for (int i = 0; i < training_model.size(); i++) {
		for (int j = 0; j < training_model[i].size(); j++) {
			for (int k = 0; k < training_model[i][j].size(); k++) {
				training_model[i][j][k] = round(training_model[i][j][k]);
			}
		}
	}
	return training_model;
}

// Estimate the priors P(class = c) or the probability of each class independent of the features
 vector <double> training_model::ComputeIndependentClassPriors(std::string file_name) {
	vector <double> priors;
	priors.resize(kDigits);
	double total_training_images = ReadIntsFromFile(file_name).size();
	for (int i = 0; i < priors.size(); i++) {
		double num_training_images_for_digit = GetIndexesForDigit(i, file_name).size();
		priors[i] = (num_training_images_for_digit / total_training_images);
	}
	return priors;
}

 // Open a file and load independent class priors to it
int training_model::WriteIndependentClassPriorsToFile(std::string training_labels, std::string file_name) {
	std::ofstream out_file;
	out_file.open(file_name);

	vector <double> independent_class_priors = ComputeIndependentClassPriors(training_labels);

	if (out_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (out_file.is_open()) {
		for (double i : independent_class_priors) {
			out_file << i << endl;
		}
	}
	return 0;
}

// Open a file and load features probabilities to it
int training_model::WriteFeaturesProbabilitiesToFile(vector <vector< vector<double> > > training_model, std::string file_name) {
	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (out_file.is_open()) {
		for (int i = 0; i < training_model.size(); i++) {
			for (int j = 0; j < training_model[i].size(); j++) {
				for (int k = 0; k < training_model[i][j].size(); k++) {
					out_file << training_model[i][j][k] << endl;
				}
			}
		}
	}

	return 0;
}




