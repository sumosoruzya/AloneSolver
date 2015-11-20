#include "AloneSolver.hpp"

int main() {
	vector<vector<int>> problem;

	AloneSolver alone = AloneSolver(problem);
	vector<vector<int>> solution = alone.solve();

	return 0;
}