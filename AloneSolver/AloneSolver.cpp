#include "AloneSolver.hpp"

vector<vector<int>> AloneSolver::solve() {
	//�����K�p��@
	auto answer = grow_three_line(problem);
	answer = grow_two_one_line(answer);
	answer = negation_between_same_number(answer);

	// �P���ے�ƒP�������̃R���{
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
	// ����3����������ł�����A���[�����}�X
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
	// ����������2����ŁA�����1�������ꍇ�A����Ă���1�͍��}�X
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
	// ���������ɋ��܂ꂽ�ʂ̐����͔��}�X�m��
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
	// ���g�����}�X�Ȃ�A���͂̃}�X�͔��}�X
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
	// ���g�����}�X�m��Ȃ�A���������̃}�X�͑S�č��}�X
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