#include "number.h"

vector <vector< vector<double> > > training_model::CreateFeaturesModel(std::string images_file, std::string images_labels, bool is_feature_one) {
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
					if (!is_feature_one && image[j][k] == kWhite) {
						features[i][j][k] += 1;
					}
				}
			}
		}
		for (int j = 0; j < features[i].size(); j++) {
			for (int k = 0; k < features[i][j].size(); k++) {
				features[i][j][k] += kLaplaceVal;
				features[i][j][k] = features[i][j][k] / (indexes.size() + 2 * kLaplaceVal);
			}
		}
	}
	return features;
}

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


