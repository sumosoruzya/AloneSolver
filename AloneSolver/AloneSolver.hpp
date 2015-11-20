#pragma once

#include <vector>

using namespace std;

typedef struct a_data
{
	int num;
	int flag;
}a_data;

class AloneSolver
{
public:
	AloneSolver(vector<vector<a_data>> prob) {
		problem = prob;
		matrix_size = prob.size;
	}

	vector<vector<a_data>> solve();

private:
	int matrix_size;
	vector<vector<a_data>> problem;

	vector<vector<a_data>> grow_three_line(vector<vector<a_data>> prob);
	vector<vector<a_data>> grow_two_one_line(vector<vector<a_data>> prob);
	vector<vector<a_data>> negation_between_same_number(vector<vector<a_data>> prob);
	vector<vector<a_data>> simple_negation(vector<vector<a_data>> prob);
	vector<vector<a_data>> simple_grow(vector<vector<a_data>> prob);
};

