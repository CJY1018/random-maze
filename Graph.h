#include <iostream>
#include <vector>
#define MAX_DISTANCE 1000000
using namespace std;

class Graph {
public:
	//初始化图
	Graph(int** distance, int n) {
		this->distance = distance;
		this->N = n;
		path = new int* [n];
		//为path矩阵开辟空间
		for (int i = 0; i < n; i++) {
			path[i] = new int[n];
		}
		//为path矩阵赋初值
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if(distance[i][j] == 1)
					path[i][j] = i;
				else {
					distance[i][j] = MAX_DISTANCE;
					path[i][j] = -1;
				}	
			}
		}
	}

	//Floyed算法
	void Floyed() {
		for (int m = 1; m <= N; m++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					if (i != j && distance[i - 1][m - 1] + distance[m - 1][j - 1] < distance[i - 1][j - 1]) {
						distance[i - 1][j - 1] = distance[i - 1][m - 1] + distance[m - 1][j - 1];
						path[i - 1][j - 1] = path[m - 1][j - 1];
					}
				}
			}
		}
	}

	//输出结果
	vector<int>* minPath(int i, int j) {
		vector<int>* load=new vector<int>;
		load->push_back(j);
		int sum = 1;
		int x = path[i - 1][j - 1];
		if (x == -1)
			return load;
		while (x != i - 1) {
			load->push_back(x + 1);
			sum++;
			x = path[i - 1][x];
		}
		load->push_back(i);
		return load;
	}

private:
	int N;	//结点个数
	int** distance;	//距离矩阵
	int** path;	//路径矩阵
};

