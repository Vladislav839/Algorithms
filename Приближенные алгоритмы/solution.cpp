#include <fstream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <functional>

class Good
{
public:
	long long before;
	long long after;
	long long proc;
	int number;

	Good(long long before, long long proc, long long after, int number)
	{
		this->before = before;
		this->proc = proc;
		this->after = after;
		this->number = number;
	}

	
};

bool operator < (Good c1, Good c2)
{
	return c1.before < c2.before;
}

class Machine
{
public:
	int number;
	long long time;

	Machine(int number, long long time)
	{
		this->number = number;
		this->time = time;
	}
};

bool operator < (Machine c1, Machine c2)
{
	return c1.time < c2.time;
}

bool operator > (Machine c1, Machine c2)
{
	return c1.time > c2.time;
}

long long myMax(long long a, long long b)
{
	return a > b ? a : b;
}

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	std::priority_queue<Machine, std::vector<Machine>, std::greater<Machine>> machines;
	std::vector<Good> goods;
	for (int i = 0; i < m; i++)
	{
		machines.push(Machine(i + 1, 0));
	}
	for (int i = 0; i < n; i++)
	{
		long long a, b, c;
		fin >> a >> b >> c;
		goods.push_back(Good(a, b, c, i + 1));
	}
	std::sort(goods.begin(), goods.end());
	std::vector<std::array<int, 2>> appoints;
	long long res = 0;
	for (int i = 0; i < n; i++)
	{
		Machine top = machines.top();
		machines.pop();
		long long c_time = top.time;
		if (c_time < goods[i].before) {
			c_time = goods[i].before;
		}
		c_time += goods[i].proc;
		appoints.push_back({ goods[i].number, top.number });
		machines.push(Machine(top.number, c_time));
		res = myMax(res, c_time + goods[i].after);
	}
	fout << res << '\n';
	for (int i = 0; i < appoints.size(); i++) {
		fout << appoints[i][0] << " " << appoints[i][1] << '\n';
	}
	return 0;
}