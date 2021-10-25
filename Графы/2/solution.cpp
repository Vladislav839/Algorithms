#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <chrono>
#include <list>
using namespace std::chrono;

int N;
//std::set<std::string> user_words;
std::vector<std::vector<int>> graph;
std::vector<bool> used_letters(26, false);
std::vector<char> vertex_to_letter;
std::map<char, int> letter_to_vertex;
std::stack<int> st;
std::stack<int> cycle;
std::vector<std::vector<std::list<std::string>>> letters_to_word;

//std::ofstream fout("output.txt");

//void printMap()
//{
//	for (auto& e : letters_to_word) {
//		std::cout << "{" << e.first << "\n";
//		for (std::string str : e.second) {
//			std::cout << str << " ";
//		}
//	}
//	std::cout << '\n';
//}

void printMatrix() {
	std::cout << "Matrix\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

//void printVertexes() {
//	std::cout << "Vertexes\n";
//	std::for_each(vertexes.cbegin(), vertexes.cend(), [](char x) {
//		std::cout << x << ' ';
//		});
//	std::cout << '\n';
//}

void print_letter_to_vertex() {
	std::cout << "letter_to_vertex\n";
	for (auto it = letter_to_vertex.begin(); it != letter_to_vertex.end(); ++it) {
		std::cout << it->first << ", " << it->second << '\n';
	}
	std::cout << '\n';
}

void print_vertex_to_letter() {
	std::cout << "vertex_to_letter\n";
	for (int i = 0; i < vertex_to_letter.size(); i++) {
		std::cout << i << " " << vertex_to_letter[i] << '\n';
	}
}

//bool consists(char letter) {
//	auto search = vertexes.find(letter);
//	return search != vertexes.end();
//}

void DFS(int u, std::vector<bool>& visited) {
	visited[u] = true;

	for (int v = 0; v < N; v++) {
		if (graph[u][v]) {
			if (!visited[v])
				DFS(v, visited);
		}
	}
}

bool isConnected() {
	std::vector<bool> visited(N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			visited[j] = false;

		DFS(i, visited);

		for (int k = 0; k < N; k++) {
			if (!visited[k])
				return false;
		}
	}
	return true;
}

bool isEuler() {
	if (!isConnected()) return false;

	std::vector<long long> in(N, 0);
	std::vector<long long> out(N, 0);

	for (int i = 0; i < N; i++) {
		long long sum = 0ll;
		for (int j = 0; j < N; j++) {
			if (graph[i][j] != 0) {
				in[j] += graph[i][j];
				sum += graph[i][j];
			}
		}
		out[i] = sum;
	}

	if (in == out)    
		return true;
	return false;
}

void findEulerCycle() {
	if (!isEuler()) {
		std::cout << "No";
		exit(0);
	}
	std::cout << "Yes\n";
	//std::vector<int> search_start_index(N);
	st.push(0);
	while (!st.empty())
	{
		bool found = false;
		int current = st.top();
		for (int i = 0; i < N; i++) {
			if (graph[current][i] != 0) {
				--graph[current][i];
				st.push(i);
				found = true;
				break;
			}
		}
		if (!found) {
			int tmp = st.top();
			st.pop();
			cycle.push(tmp);
		}
	}
}

void addWord(std::string word) {
	std::string first_last;
	if (!used_letters[int(word[0]) - 'a']) {
		used_letters[int(word[0]) - 'a'] = true;
		vertex_to_letter.push_back(word[0]);
		letter_to_vertex[word[0]] = vertex_to_letter.size() - 1;
	}
	if (!used_letters[int(word[word.size() - 1]) - 'a']) {
		used_letters[int(word[word.size() - 1]) - 'a'] = true;
		vertex_to_letter.push_back(word[word.size() - 1]);
		letter_to_vertex[word[word.size() - 1]] = vertex_to_letter.size() - 1;
	}
	first_last.push_back(word[0]);
	first_last.push_back(word[word.size() - 1]);
	letters_to_word[int(word[0]) - 'a'][int(word[word.size() - 1]) - 'a'].push_back(word);
}

void readGraph()
{
	//std::ifstream fin("input.txt");
	int n;
	std::cin >> n;
	if (n == 1) {
		std::string str;
		std::cin >> str;
		std::cout << "Yes\n" << str;
		exit(0);
	}
	std::string word;
	graph.resize(26, std::vector<int>(26));
	for (int i = 0; i < n; i++) {
		std::cin >> word;
		addWord(word);
		graph[letter_to_vertex[word[0]]][letter_to_vertex[word[word.size() - 1]]]++;
	}

}

int main()
{
	std::ios::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	letters_to_word.resize(26, std::vector<std::list<std::string>>(26));
	readGraph();
	N = 0;
	for (int i = 0; i < 26; i++) {
		if (used_letters[i] == true) {
			N++;
		}
	}
	findEulerCycle();
	while (cycle.size() != 1)
	{
		char first = vertex_to_letter[cycle.top()];
		cycle.pop();
		char last = vertex_to_letter[cycle.top()];
		if (!letters_to_word[int(first) - 'a'][int(last) - 'a'].empty()) {
			std::cout << letters_to_word[int(first) - 'a'][int(last) - 'a'].back() << '\n';
			letters_to_word[int(first) - 'a'][int(last) - 'a'].pop_back();
		}
	}
	return 0;
}