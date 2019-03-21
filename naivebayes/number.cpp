#include "number.h"

vector< vector<char> > ReadFileStoreImage(std::string file_path, int index) {
	std::ifstream my_file;
	my_file.open(file_path);
	vector<std::string> file_contents;

	if (my_file.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	if (my_file.is_open()) {
		std::string line;
		int counter = 0;
		while (getline(my_file, line)) {
			if (counter >= ((index * kDimension) - (kDimension - 1)) && counter <= kDimension * index) {
				file_contents.push_back(line.c_str());
			}
			counter++;
		}
	}
	my_file.close();
	
	return CreateCharVector(file_contents);
}

vector< vector<char> > CreateCharVector(vector<std::string> lines_from_file) {
	vector< vector<char> > to_return;
	to_return.resize(kDimension);
	for (int i = 0; i < lines_from_file.size(); i++) {
		to_return[i].resize(kDimension);
		for (int j = 0; j < lines_from_file[i].length(); j++) {
			to_return[i][j] = lines_from_file[i].at(j);
		}
	}
	return to_return;
}

int PrintTwoDVector(vector< vector<char> > to_print) {
	for (int i = 0; i < to_print.size(); i++) {
		for (int j = 0; j < to_print[i].size(); j++) {
			cout << to_print[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}


