#pragma comment(linker, "/STACK:67108864")

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> usedRoads;
std::vector<std::pair<int, int>> crossRoads;
std::vector<int> preds;
int S, T, N, M;
int iter = 0;

std::ofstream fout("output.txt");

std::deque<int> path;

bool isDeadlock(int v, int pred, std::pair<int, int> p1, std::pair<int, int> p3)
{
	for (int u = 0; u < graph.size(); u++)
	{
		if (graph[v][u] == 1 && u != pred && p1.first != p3.first) return false;
	}
	return true;
}

//void printMatrix()
//{
//	for (int i = 0; i < graph.size(); i++)
//	{
//		for (int j = 0; j < graph.size(); j++)
//		{
//			std::cout << graph[i][j] << " ";
//		}
//		std::cout << '\n';
//	}
//}

bool isCross(int v)
{
	int n = 0;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[v][i] == 1) n++;
	}
	return n > 0;
}


bool Left(int a, int  b, int c)
{
	auto p1 = crossRoads[a];
	auto p2 = crossRoads[b];
	auto p3 = crossRoads[c];
	long long det = 0ll;
	det += (long long)p1.first * p2.second;
	det += (long long)p1.second * p3.first;
	det += (long long)p2.first * p3.second;
	det -= (long long)p2.second * p3.first;
	det -= (long long)p1.second * p2.first;
	det -= (long long)p1.first * p3.second;;
	return det > 0ll;
}

bool Back(int a, int  b, int c)
{
	auto p1 = crossRoads[a];
	auto p2 = crossRoads[b];
	auto p3 = crossRoads[c];
	if (p1.first == p2.first && p2.first == p3.first)
	{
		if (p1.second <= p3.second && p3.second <= p2.second) return true;
		if (p2.second <= p1.second && p1.second <= p3.second) return true;
		if (p2.second <= p3.second && p3.second <= p1.second) return true;
		if (p3.second <= p1.second && p1.second <= p2.second) return true;
	}
	return false;
}


void DFS(int v, int pred) {
	iter++;
	if (v == T)
	{
		fout << "Yes\n";
		while (!path.empty())
		{
			fout << path.front() << " ";
			path.pop_front();
		}
		exit(0);
	}
	if (iter >= 2 * M)
	{
		fout << "No";
		exit(0);
	}
	if (pred != -1)
	{
		graph[pred][v] = 0;
	}
	preds[v] = pred;
	for (int u = 0; u < graph.size(); u++)
	{
		if (graph[v][u] == 1)
		{
			bool left = false;
			bool back = false;
			if (pred != -1)
			{
				left = Left(pred, v, u);
				back = Back(pred, v, u);
			}
			if (!left && u != pred && !back)
			{
				path.push_back(u);
				DFS(u, v);
			}
		}
	}
	if (pred != -1)
	{
		if (!path.empty()) path.pop_back();
		DFS(pred, preds[pred]);
	}
	else
	{
		fout << "No";
		exit(0);
	}
}

int main()
{
	std::ifstream fin("input.txt");
	fin >> N >> M;
	if (M == 0)
	{
		fout << "No";
		return 0;
	}
	graph.resize(N + 1, std::vector<int>(N + 1));
	//usedRoads.resize(N, std::vector<int>(N));
	crossRoads.resize(N + 1);
	preds.resize(N + 1);
	for (int i = 1; i < M + 1; i++)
	{
		int x1, x2, y1, y2, from, to;
		fin >> x1 >> y1 >> x2 >> y2 >> from >> to;
		crossRoads[from] = std::make_pair(x1, y1);
		crossRoads[to] = std::make_pair(x2, y2);
		graph[from][to] = 1;
		graph[to][from] = 1;
	}
	fin >> S >> T;
	auto p1 = std::make_pair(crossRoads[S].first, crossRoads[S].second - 1);
	crossRoads[0] = p1;
	graph[0][S] = 1;
	DFS(0, -1);
}