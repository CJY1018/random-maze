#include <iostream>
#include <vector>
#define MAX_DISTANCE 1000000
using namespace std;

class Graph {
public:
	//��ʼ��ͼ
	Graph(int** distance, int n) {
		this->distance = distance;
		this->N = n;
		path = new int* [n];
		//Ϊpath���󿪱ٿռ�
		for (int i = 0; i < n; i++) {
			path[i] = new int[n];
		}
		//Ϊpath���󸳳�ֵ
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

	//Floyed�㷨
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

	//������
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
	int N;	//������
	int** distance;	//�������
	int** path;	//·������
};

