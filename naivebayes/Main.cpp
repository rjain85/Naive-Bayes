#include "number.h"

int main(int argc, char *argv[]) {
	vector <int> indexes = GetIndexesForDigit(5, "traininglabels");
	
	training_model model;
	vector <vector< vector<double> > > features = model.CreateFeaturesModel("trainingimages", "traininglabels", true);
	/*for (vector< vector<double> > d : features) {
		for (int i = 0; i < d.size(); i++) {
			for (int j = 0; j < d.size(); j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/

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

}