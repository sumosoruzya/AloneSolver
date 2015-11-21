#include <fstream>
#include <iostream>
#include <string>

#include "AloneSolver.hpp"

vector<int> dec2bin(vector<vector<int>> dec) {
	vector<int> bin;

	for (auto vec : dec) {
		for (auto num : vec) {
			if (num == 0) {
				bin.push_back(1);
			}
			else {
				bin.push_back(0);
			}
		}
	}

	return bin;
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cout << "ERROR : Number of argument is not enough" << endl;
		return EXIT_FAILURE;
	}
	if (strstr(argv[1], ".csv") == NULL) {
		cout << "ERROR : Type of input file must be \".csv\"" << endl;
		return EXIT_FAILURE;
	}
	if (strstr(argv[2], ".csv") == NULL) {
		cout << "ERROR : Type of output file must be \".csv\"" << endl;
		return EXIT_FAILURE;
	}

	ifstream ifs(argv[1]);
	if (!ifs) {
		cout << "ERROR : This input file don't exist" << endl;
		return EXIT_FAILURE;
	}

	int p;
	string str;
	vector<vector<int>> problem_list;
	while (getline(ifs, str)) {
		vector<int> prob;

		//�R���}�����邩��T���A�����܂ł�values�Ɋi�[
		while ((p = str.find(",")) != str.npos) {
			prob.push_back(atoi(str.substr(0, p).c_str()));

			//str�̒��g��", "��2�������΂�
			str = str.substr(p + 1);
		}
		prob.push_back(atoi(str.c_str()));
		problem_list.push_back(prob);
	}

	vector<vector<int>> solution_list;
	for (auto vec : problem_list) {
		vector<vector<int>> problem;

		AloneSolver alone = AloneSolver(problem);
		auto solution = alone.solve();

		solution_list.push_back(dec2bin(solution));
	}
	
	// csv�`���ŏo��
	ofstream ofs(argv[2]);
	for (auto vec : solution_list) {
		for (auto num : vec) {
			ofs << num << ",";
		}
	}
	ofs << endl;

	return EXIT_SUCCESS;
}