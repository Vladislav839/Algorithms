#pragma comment(linker, "/STACK:167772160")

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Tree
{
public:
    vector<long long> numbers;
    int n;
    vector<long long> tree;

    Tree(int n)
    {
        this->n = n;
        tree.resize(4 * n, 0ll);
    }

    void Add(int index, long long value) {
        Add(1, 0, n, index, value);
    }

    void Add(int v, int start, int end, int index, long long value) {
        if (end - start == 1) {
            tree[v] += value;
            return;
        }

        int mid = (end + start) / 2;
        if (index < mid) {
            Add(2 * v, start, mid, index, value);
        }
        else {
            Add(2 * v + 1, mid, end, index, value);
        }
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    long long sum(int start, int end) {
        return sum(1, 0, n, start, end);
    }

    long long sum(int v, int tree_start, int tree_end, int start, int end) {
        if (start == tree_start && end == tree_end) {
            return tree[v];
        }

        int mid = (tree_end + tree_start) / 2;
        if (end <= mid) {
            return sum(2 * v, tree_start, mid, start, end);
        }
        if (mid <= start) {
            return sum(2 * v + 1, mid, tree_end, start, end);
        }

        return sum(2 * v, tree_start, mid, start, mid) +
            sum(2 * v + 1, mid, tree_end, mid, end);
    }
};

pair<vector<long long>, vector<long long>> countGreater(vector<long long>& nums) {
    vector<long long> resultLeft;
    vector<long long> resultRight;
    if (nums.empty()) {
        return make_pair(resultLeft, resultRight);
    }
    int n = (int)nums.size();
    vector<pair<long long, long long> > data1(n);
    for (int i = 0; i < n; ++i) {
        data1[i] = pair<long long, long long>(nums[i], i);
    }
    sort(data1.begin(), data1.end(), greater<pair<long long, long long> >());
    resultLeft.resize(n);
    Tree segmentTree(n);
    for (int i = 0; i < n; ++i) {
        resultLeft[data1[i].second] = segmentTree.sum(0, data1[i].second);
        segmentTree.Add(data1[i].second, 1);
    }
    vector<pair<long long, long long> > data2(n);
    for (int i = 0; i < n; ++i) {
        data2[i] = pair<long long, long long>(nums[i], i);
    }
    sort(data2.begin(), data2.end());
    resultRight.resize(n);
    Tree segmentTree_2(n);
    for (int i = 0; i < n; ++i) {
        resultRight[data2[i].second] = segmentTree_2.sum(data2[i].second, n);
        segmentTree_2.Add(data2[i].second, 1);
    }
    return make_pair(resultLeft, resultRight);
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;
    vector<long long> numbers;
    for (int i = 0; i < n; i++)
    {
        int k;
        fin >> k;
        numbers.push_back(k);
    }
    pair<vector<long long>, vector<long long>> res = countGreater(numbers);
    long long result = 0ll;
    for (int i = 0; i < res.first.size(); i++)
    {
        result += res.first[i] * res.second[i];
    }
    fout << result;
    return 0;
}