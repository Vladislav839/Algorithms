#include <fstream>
#include <iostream>
#include <vector>
#include <set>

int myMax(int a, int b) {
	return a > b ? a : b;
}

bool allVisited(std::vector<bool>& visited) {
	for (int i = 0; i < visited.size(); i++) {
		if (visited[i] == false) {
			return false;
		}
	}
	return true;
}

void DFS(int v, std::vector<std::vector<int>>& matrix, std::vector<bool>& visited, std::vector<bool>& visited_current) {
	visited[v] = true;
	visited_current[v] = true;
	for (int u = 0; u < visited_current.size(); u++) {
		if (matrix[v][u] && !visited_current[u]) {
			DFS(u, matrix, visited, visited_current);
		}
	}
}

void Invert(std::vector<std::vector<int>>& matrix, 
	 std::vector<std::vector<int>>& transpose_matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			transpose_matrix[i][j] = matrix[j][i];
		}
	}
}

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n;
	fin >> n;
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
	std::vector<std::vector<int>> transpose_matrix(matrix.size(), std::vector<int>(matrix.size(), 0));
	std::vector<bool> visited(n);
	std::vector<bool> visited_current(n);
	for (int i = 0; i < n; i++) {
		int value;
		while (true) {
			fin >> value;
			if (value == 0) break;
			matrix[i][value - 1] = 1;
		}
	}
	std::set<int> s1;
	for (int i = 0; i < n; i++) {
		s1.insert(i);
	}
	int v1 = 0;
	while (true)
	{
		for (int i = 0; i < n; i++) visited_current[i] = false;
		DFS(v1, matrix, visited, visited_current);
		for (int i = 0; i < n; i++) {
			if (visited_current[i]) {
				auto it = s1.find(i);
				if (it != s1.end()) {
					s1.erase(it);
				}
			}
		}
		s1.insert(v1);
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				v1 = i;
				break;
			}
		}
		if (allVisited(visited)) break;
	}
	Invert(matrix, transpose_matrix);
	std::set<int> s2;
	int v2 = 0;
	std::vector<bool> visited2(n);
	for (int i = 0; i < n; i++) {
		s2.insert(i);
	}
	while (true)
	{
		for (int i = 0; i < n; i++) visited_current[i] = false;
		DFS(v2, transpose_matrix, visited2, visited_current);
		for (int i = 0; i < n; i++) {
			if (visited_current[i]) {
				auto it = s2.find(i);
				if (it != s2.end()) {
					s2.erase(it);
				}
			}
		}
		s2.insert(v2);
		for (int i = 0; i < n; i++) {
			if (!visited2[i]) {
				v2 = i;
				break;
			}
		}
		if (allVisited(visited2)) break;
	}
	if (s1.size() == 1 && s2.size() == 1) {
		auto it1 = s1.begin();
		auto it2 = s2.begin();
		if (*it1 == 0 && *it2 == 0) {
			fout << 1 << '\n' << 0;
			return 0;
		}
	}
	fout << s1.size() << '\n' << myMax(s1.size(), s2.size());
	return 0;
}