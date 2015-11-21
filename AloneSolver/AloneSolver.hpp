#pragma once

#include <vector>

using namespace std;

typedef struct alone_data
{
	int num;
	int flag;

	alone_data(int n) {
		num = n;
		flag = 0;
	}
	alone_data(int n, int f) {
		num = n;
		flag = f;
	}

	int to_i() {
		if (flag == 1)return 0;
		else return num;
	}
}a_data;

class AloneSolver
{
public:
	AloneSolver(vector<vector<a_data>> prob) {
		problem = prob;
		matrix_size = prob.size;
	}

	AloneSolver(vector<vector<int>> prob) {
		for(auto vec: prob) {
			vector<a_data> col;
			for (auto num : vec) {
				col.push_back(a_data(num));
			}
			problem.push_back(col);
		}
		matrix_size = prob.size;
	}

	AloneSolver(int n, const int& prob) {
		for (int i = 0; i < n; i++) {
			vector<a_data> col;
			for (int j = 0; j < n; j++) {
				col.push_back(a_data((&prob)[n * i + j]));
			}
			problem.push_back(col);
		}
		matrix_size = n;
	}

	vector<vector<int>> solve();

private:
	int matrix_size;
	vector<vector<a_data>> problem;

	vector<vector<a_data>> grow_three_line(vector<vector<a_data>> prob);
	vector<vector<a_data>> grow_two_one_line(vector<vector<a_data>> prob);
	vector<vector<a_data>> negation_between_same_number(vector<vector<a_data>> prob);
	vector<vector<a_data>> negation_exit(vector<vector<a_data>> prob);
	vector<vector<a_data>> simple_negation(vector<vector<a_data>> prob);
	vector<vector<a_data>> simple_grow(vector<vector<a_data>> prob);
};

