#include "number.h"

int main(int argc, char *argv[]) {	
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
	}*/

	

	/*vector<double> priors = model.ComputeIndependentClassPriors("traininglabels");
	for (int i = 0; i < priors.size(); i++) {
		cout << i << ": " << priors[i] << endl;
	}*/

	/*model.WriteIndependentClassPriorsToFile("traininglabels", "independentclasspriors.txt");
	model.WriteFeaturesProbabilitiesToFile(black_features, "blackfeaturesprobabilities.txt");
	model.WriteFeaturesProbabilitiesToFile(white_features, "whitefeaturesprobabilities.txt");*/

	vector <vector< vector<double> > > black = ReadProbabilitiesFromFile("blackfeaturesprobabilities.txt");
	vector <vector< vector<double> > > composite_images = model.CreateComposites(black);
	PrintThreeDVector(composite_images);
	vector<vector<vector<double>>> white = ReadProbabilitiesFromFile("whitefeaturesprobabilities.txt");
	vector <double> priors = ReadDoublesFromFile("independentclasspriors.txt");
	vector<int> classifications = classy.ClassifyImages("testimages", black, white, priors);
	classy.ReportClassificationAccuracy(classifications, "testlabels");
	vector <vector <double> > confusion_matrix = classy.ComputeConfusionMatrix(classifications, "testlabels");
	classy.PrintConfusionMatrix(confusion_matrix);
}