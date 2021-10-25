#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int myMin(int a, int b) {
	return a < b ? a : b;
}

class Solver
{
public:
	ofstream fout;
	vector<vector<int>> field;
	int snowLeftBorder;
	int snowRightBorder;
	int mashineStartPosition;
	int n;

	Solver(vector<vector<int>> field, int snowLeftBorder, int snowRightBorder, int k, int n)
	{
		this->field = field;
		this->snowLeftBorder = snowLeftBorder;
		this->snowRightBorder = snowRightBorder;
		fout = ofstream("out.txt");
		this->mashineStartPosition = k;
		this->n = n;
	}

	int GetMinSeconds(int start, int end)
	{
		vector<vector<int>> dynamic(n, vector<int>(n + 1, 0));

		if (start == end) return 0;

		for (int i = start; i <= end - 1; i++) {
			if (field[0][i] == 1 && field[1][i] == 1) {
				if ((i == start) && (i + 1 == start + 1)) {
					dynamic[i][i + 1] = 2;
				}
				else {
					dynamic[i][i + 1] = 3;
				}
			}
			else {
				dynamic[i][i + 1] = 1;
			}
		}
		for (int i = start; i <= end; i++)
		{
			for (int j = i + 1; j <= end; j++)
			{
				dynamic[i][j] = dynamic[i][j - 1] + dynamic[j - 1][j];
			}
		}

		return myMin(dynamic[start][end], 2 * fabs(start - end));
	}

	int Solve()
	{
		if (snowLeftBorder == -1 || snowLeftBorder == snowRightBorder) return 0;
		if (snowLeftBorder >= mashineStartPosition) {
			return GetMinSeconds(mashineStartPosition, snowRightBorder);
		}
		if (mashineStartPosition >= snowRightBorder) {
			return GetMinSeconds(snowLeftBorder, mashineStartPosition);
		}
		else {
			int time_1 = GetMinSeconds(mashineStartPosition, snowRightBorder) +
				2 * fabs(mashineStartPosition - snowLeftBorder);
			
			int time_2 = GetMinSeconds(snowLeftBorder, mashineStartPosition) +
				2 * fabs(snowRightBorder - mashineStartPosition);

			return myMin(time_1, time_2);
		}
	}
};

int main()
{
	ifstream fin("in.txt");
	int n, k;
	fin >> n >> k;
	vector<vector<int>> field(2, vector<int>(n, 0));

	int snowLeftBorder = -1;
	int SnowRightBorder = 0;
	for (int i = 0; i < n; i++) {
		fin >> field[0][i];
		fin >> field[1][i];
		if (field[0][i] == 1 || field[1][i] == 1) {
			if (snowLeftBorder == -1) {
				snowLeftBorder = i;
			}
			SnowRightBorder = i;
		}
	}
	Solver solver(field, snowLeftBorder, SnowRightBorder + 1, k, n);
	int time = solver.Solve();
	ofstream fout("out.txt");
	fout << time;
	return 0;
}