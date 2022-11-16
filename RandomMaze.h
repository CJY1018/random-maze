#pragma once
#include <iostream>
#include "Graph.h"
#include <queue>
#include <stack>
using namespace std;

class RandomMaze {
public:
	RandomMaze(int m, int n) {
		this->m = m;
		this->n = n;
		this->edgeNum = m * n * 2 - m - n;
		this->count = 0;
		edge = new int[edgeNum];
		maze = new int* [m];
		map = new int* [m * n];
		for (int i = 0; i < edgeNum; i++) {
			edge[i] = i;
		}
		shuffle(edge, edgeNum);
		for (int i = 0; i < m; i++) {
			maze[i] = new int[n];
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				maze[i][j] = i * n + j + 1;
			}
		}

		for (int i = 0; i < m * n; i++) {
			map[i] = new int[m * n];
		}
		for (int i = 0; i < m * n; i++) {
			for (int j = 0; j < m * n; j++) {
				map[i][j] = 0;
			}
		}
	}

	//找到所在元素的根结点
	int find(int i, int j) {
		int value = i * n + j + 1;
		return value == maze[i][j] ? value : (maze[i][j] = find((maze[i][j] - 1) / n, (maze[i][j] - 1) % n));
	}

	//合并两方块
	void merge(int i1, int j1, int i2, int j2) {
		int value1 = find(i1, j1);
		maze[(value1 - 1) / n][(value1 - 1) % n] = find(i2, j2);
		map[i1 * n + j1][i2 * n + j2] = map[i2 * n + j2][i1 * n + j1] = 1;
	}

	//洗牌算法
	void shuffle(int* a, int len) {
		srand((int)time(0));
		for (int i = 0; i < len - 1; i++) {
			int r = (rand() % (len - i)) + i;
			swap(a[i], a[r]);
		}
	}

	//消除边
	void erase() {
		for (int i = 0; i < edgeNum; i++) {
			int value1,value2;
			if (edge[i] % (2 * n - 1) <= (n-2)) {	//竖边
				value1 = edge[i] / (2 * n - 1) * n + edge[i] % (2 * n - 1) + 1;
				value2 = value1+1;
				merge((value1 - 1) / n, (value1 - 1) % n, (value2 - 1) / n, (value2 - 1) % n);
			}
			else {	//横边
				value1 = ((edge[i] + n) / (2 * n - 1) - 1) * n + (edge[i] + n) % (2 * n - 1) + 1;
				value2 = value1+n;
				merge((value1 - 1) / n, (value1 - 1) % n, (value2 - 1) / n, (value2 - 1) % n);
			}
			count++;
			if (find(0, 0) == find(m - 1, n - 1))
				break;
		}
	}

	//求最小路径
	vector<int>* minPath() {
		Graph g(map,m*n);
		g.Floyed();
		return g.minPath(1, m * n);
	}


	int getM() {
		return m;
	}
	int getN() {
		return n;
	}
	int getEdgeNum() {
		return edgeNum;
	}
	int getCount() {
		return count;
	}
	int** getMaze() {
		return maze;
	}
	int* getEdge() {
		return edge;
	}

private:
	int m;
	int n;
	int* edge;
	int edgeNum;
	int count;
	int** maze;
	int** map;
};