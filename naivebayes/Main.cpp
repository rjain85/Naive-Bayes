#include "number.h"

int main(int argc, char *argv[]) {
	vector <int> indexes = GetIndexesForDigit(5, "traininglabels");
	
	training_model model;
	classifier classy;
	//vector <vector< vector<double> > > black_features = model.ComputeFeaturesModel("trainingimages", "traininglabels", true);
	//vector <vector< vector<double> > > white_features = model.ComputeFeaturesModel("trainingimages", "traininglabels", false);

	/*for (vector< vector<double> > d : features) {
		for (int i = 0; i < d.size(); i++) {
			for (int j = 0; j < d.size(); j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	vector <vector< vector<double> > > composite_images = model.CreateComposites(features);
	for (vector< vector<double> > image : composite_images) {
		for (int i = 0; i < image.size(); i++) {
			for (int j = 0; j < image.size(); j++) {
				cout << image[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	vector<double> priors = model.ComputeIndependentClassPriors("traininglabels");
	for (int i = 0; i < priors.size(); i++) {
		cout << i << ": " << priors[i] << endl;
	}*/

	/*model.WriteIndependentClassPriorsToFile("traininglabels", "independentclasspriors.txt");
	model.WriteFeaturesProbabilitiesToFile(black_features, "blackfeaturesprobabilities.txt");
	model.WriteFeaturesProbabilitiesToFile(white_features, "whitefeaturesprobabilities.txt");*/

	vector<vector<vector<double>>> black = ReadProbabilitiesFromFile("blackfeaturesprobabilities.txt");
	vector<vector<vector<double>>> white = ReadProbabilitiesFromFile("whitefeaturesprobabilities.txt");
	vector <double> priors = ReadDoublesFromFile("independentclasspriors.txt");
	vector<int> classifications = classy.ClassifyImages("testimages", black, white, priors);
	double accuracy = classy.ReportClassificationAccuracy(classifications, "testlabels");
	cout << accuracy << endl;
	vector <vector <double> > confusion_matrix = classy.ComputeConfusionMatrix(classifications, "testlabels");
	
	for (int i = 0; i < confusion_matrix.size(); i++) {
		for (int j = 0; j < confusion_matrix[i].size(); j++) {
			cout << confusion_matrix[i][j] << " ";
		}
		cout << endl;
	}
}