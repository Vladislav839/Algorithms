#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stack>

void Print(std::vector<std::vector<std::pair<int, int>>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << "(" << matrix[i][j].first << ", " << matrix[i][j].second << ")\t";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void ProcessDpCell(std::vector<int>& blocks, std::vector<int>& winners,
	std::vector<std::vector<std::pair<int, int>>>& dp, int i, int j)
{
	if (i == j)
	{
		for (int p = 0; p < i; p++)
		{
			if (blocks[p] + winners[p] >= blocks[p + 1] + winners[p + 1])
			{
				dp[i][j].first = -1;
				dp[i][j].second = p - 1;
				return;
			}
		}
		dp[i][j].first = i;
		dp[i][j].second = i - 1;
		return;
	}
	dp[i][j] = dp[i][j - 1];
	int k = j - 1;
	if (dp[i - 1][k].first != -1)
	{
		if (winners[i - 1] + blocks[dp[i - 1][k].first] < winners[i] + blocks[j])
		{
			if (dp[i][j - 1].first == -1)
			{
				dp[i][j].first = j;
				dp[i][j].second = dp[i - 1][k].first;
				return;
			}
			if (winners[i] + blocks[dp[i][j - 1].first] > winners[i] + blocks[j])
			{
				dp[i][j].first = j;
				dp[i][j].second = dp[i - 1][k].first;
			}
		}
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int m, n;
	scanf("%d %d", &m, &n);
	std::vector<std::vector<std::pair<int, int>>> dp(m, std::vector<std::pair<int, int>>(n, std::make_pair(0, -1)));
	std::vector<int> winners(m);
	for (int i = 0; i < m; i++)
	{
		int d;
		scanf("%d", &d);
		winners[i] = d;
	}
	std::vector<int> blocks(n);
	for (int i = 0; i < n; i++)
	{
		int d;
		scanf("%d", &d);
		blocks[i] = d;
	}
	dp[0][0] = std::make_pair(0, -1);
	for (int v = 1; v < n - m + 1; v++)
	{
		if (winners[0] + blocks[v] < winners[0] + blocks[dp[0][v - 1].first])
		{
			dp[0][v].first = v;
		}
		else
		{
			dp[0][v] = dp[0][v - 1];
		}
	}

	//Print(dp);

	for (int i = 1; i < dp.size(); i++)
	{
		for (int j = i; j < dp[i].size() - dp.size() + i + 1; j++)
		{
			ProcessDpCell(blocks, winners, dp, i, j);
			//Print(dp);
		}
	}

	//Print(dp);
	if (dp.back().back().first == -1)
	{
		printf("%d ", -1);
		return 0;
	}
	std::stack<int> st;
	std::pair<int, int> current = dp.back().back();
	for (int i = dp.size() - 1; i >= 1; i--)
	{
		st.push(current.first);
		current = std::make_pair(current.second, dp[i - 1][current.second].second);
	}
	printf("%d ", dp[0][current.first].first + 1);
	while (!st.empty())
	{
		printf("%d ", st.top() + 1);
		st.pop();
	}
	return 0;
}