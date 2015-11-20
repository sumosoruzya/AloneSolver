#include "AloneSolver.hpp"

vector<vector<int>> AloneSolver::solve() {
	//初期適用解法
	auto answer = grow_three_line(problem);
	answer = grow_two_one_line(answer);
	answer = negation_between_same_number(answer);

	// 単純否定と単純発生のコンボ
	answer = simple_negation(answer);
	answer = simple_grow(answer);

	vector<vector<int>> solution;
	for (auto vec : answer) {
		vector<int> col;
		for (auto a : vec) {
			col.push_back(a.to_i());
		}
		solution.push_back(col);
	}
	return solution;
}

vector<vector<a_data>> AloneSolver::grow_three_line(vector<vector<a_data>> prob) {
	// 同じ3つ数字が並んでいたら、両端が黒マス
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (prob[i][j].flag == 0) {
				if (j < matrix_size - 2) {
					if (prob[i][j].num == prob[i][j + 1].num && prob[i][j + 1].num == prob[i][j + 2].num) {
						prob[i][j].num = 0;
						prob[i][j].flag = 1;
						prob[i][j + 2].num = 0;
						prob[i][j + 2].flag = 1;
					}
				}
				
				if (i < matrix_size - 2) {
					if (prob[i][j].num == prob[i + 1][j].num && prob[i + 1][j].num == prob[i + 2][j].num) {
						prob[i][j].num = 0;
						prob[i][j].flag = 1;
						prob[i + 2][j].num = 0;
						prob[i + 2][j].flag = 1;
					}
				}
			}
		}
	}
	return prob;
}

vector<vector<a_data>> AloneSolver::grow_two_one_line(vector<vector<a_data>> prob) {
	// 同じ数字が2つ並んで、離れて1つあった場合、離れている1つは黒マス
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (j < matrix_size - 1) {
				if (prob[i][j].num == prob[i][j + 1].num) {
					for (int k = 0; k < matrix_size; k++) {
						if (k == j) {
							k++;
							continue;
						}

						if (prob[i][k].num == prob[i][j].num && prob[i][k].flag == 0) {
							prob[i][k].num = 0;
							prob[i][k].flag = 1;
						}
					}
				}
			}

			if (i < matrix_size - 1) {
				if (prob[i][j].num == prob[i + 1][j].num) {
					for (int k = 0; k < matrix_size; k++) {
						if (k == i) {
							k++;
							continue;
						}

						if (prob[k][j].num == prob[i][j].num && prob[k][j].flag == 0) {
							prob[k][j].num = 0;
							prob[k][j].flag = 1;
						}
					}
				}
			}
		}
	}
	return prob;
}

vector<vector<a_data>> AloneSolver::negation_between_same_number(vector<vector<a_data>> prob) {
	// 同じ数字に挟まれた別の数字は白マス確定
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (j < matrix_size - 2) {
				if (prob[i][j].num == prob[i][j + 2].num) {
					prob[i][j].flag = -1;
				}
			}
			if (i < matrix_size - 2) {
				if (prob[i][j].num == prob[i + 2][j].num) {
					prob[i][j].flag = -1;
				}
			}
		}
	}
	return prob;
}

vector<vector<a_data>> AloneSolver::simple_negation(vector<vector<a_data>> prob) {
	// 自身が黒マスなら、周囲のマスは白マス
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (prob[i][j].flag == 1) {
				prob[i][j - 1].flag = -1;
				prob[i][j + 1].flag = -1;
				prob[i - 1][j].flag = -1;
				prob[i + 1][j].flag = -1;
			}
		}
	}
}

vector<vector<a_data>> AloneSolver::simple_grow(vector<vector<a_data>> prob) {
	// 自身が白マス確定なら、同じ数字のマスは全て黒マス
	for (int i = 0; i < matrix_size; i++) {
		for (int j = 0; j < matrix_size; j++) {
			if (prob[i][j].flag == -1) {
				for (int k = 0; k < matrix_size; k++) {
					if (k != j) {
						if (prob[i][k].flag == 0 && prob[i][k].num == prob[i][j].num) {
							prob[i][k].num = 0;
							prob[i][k].flag = 1;
						}
					}

					if (k != i) {
						if (prob[k][j].flag == 0 && prob[k][j].num == prob[i][j].num) {
							prob[k][j].num = 0;
							prob[k][j].flag = 1;
						}
					}
				}
			}
		}
	}
}