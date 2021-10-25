#pragma comment(linker, "/STACK:67108864")
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <stack>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <unordered_set>

const int LIMIT = 10000;

std::array<std::vector<int>, 100> graph;
std::array<std::array<bool, 100>, 100> visitedEdges;
std::vector<bool> visited;
int n, m;

std::deque<int> current;

int cycleNumber = 0;


std::set<std::deque<int>> allPaths;

int stop;
int startVert;

void printAllCycles(int start)
{
	printf("%d\n", cycleNumber);
	if (cycleNumber > LIMIT) {
		cycleNumber = LIMIT;
	}
	int end = 0;
	for (auto it = allPaths.begin(); it != allPaths.end(); it++)
	{
		if (end >= cycleNumber) break;
		std::deque<int> currentCycle = *it;
		for (int j = 0; j < currentCycle.size() - 1; j++)
		{
			printf("%d ", currentCycle[j] + 1);
		}
		printf("%d\n", currentCycle.back() + 1);
		end++;
	}
}


bool allEven()
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		count += graph[i].size();
		if (count % 2 == 1) return false;
	}
	return true;
}


void DFS(int u) {
	visited[u] = true;

	for (auto i = graph[u].begin(); i != graph[u].end(); ++i)
		if (!visited[*i])
			DFS(*i);
}

bool isConnected()
{
	int i;
	for (i = 0; i < n; i++)
		if (graph[i].size() > 0)
			break;

	if (i == n)
		return true;

	DFS(i);

	for (i = 0; i < n; i++)
		if (visited[i] == false && graph[i].size() > 0)
			return false;

	return true;
}

void InsertAllModifications(std::deque<int>& cycle)
{
	allPaths.insert(cycle);
	for (auto it = cycle.begin() + 1; it != cycle.end() - 1; it++) {
		if (*it == startVert) {
			std::deque<int> left_to_right;
			std::copy(it, cycle.end(), std::back_inserter(left_to_right));
			std::copy(cycle.begin() + 1, it + 1, std::back_inserter(left_to_right));
			allPaths.insert(std::move(left_to_right));
			std::deque<int> right_to_left;
			std::copy(it, cycle.end(), std::front_inserter(right_to_left));
			std::copy(cycle.begin() + 1, it + 1, std::front_inserter(right_to_left));
			allPaths.insert(std::move(right_to_left));
		}
	}
	std::deque<int> reversed;
	std::copy(cycle.begin(), cycle.end(), std::front_inserter(reversed));
	allPaths.insert(std::move(reversed));
}

void FindAllEulearCycles(int v)
{
	if (current.size() == m)
	{
		current.push_front(startVert);
		if (allPaths.find(current) == allPaths.end()) {
			InsertAllModifications(current);
			cycleNumber++;
		}
		current.pop_front();
		return;
	}
	for (auto it = graph[v].begin(); it != graph[v].end(); it++) {
		if (!visitedEdges[v][*it]) {
			visitedEdges[v][*it] = !visitedEdges[v][*it];
			visitedEdges[*it][v] = !visitedEdges[*it][v];
			current.push_back(*it);
			FindAllEulearCycles(*it);
			current.pop_back();
			visitedEdges[v][*it] = !visitedEdges[v][*it];
			visitedEdges[*it][v] = !visitedEdges[*it][v];
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	if (n == 1 && m == 0) {
		printf("%s", "1\n1");
		exit(0);
	}
	visited.resize(n, false);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}
	if (!allEven() || !isConnected())
	{
		printf("%s", "0");
		return 0;
	}
	startVert = -1;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i].size() > 0) {
			startVert = i;
			break;
		}
	}
	if (startVert == -1) {
		printf("%s", "0");
		return 0;
	}
	FindAllEulearCycles(startVert);
	printAllCycles(startVert);
	return 0;
}