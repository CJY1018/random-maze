#include "RandomMaze.h"
#include "Paint.h"
using namespace std;

int main() {
	RandomMaze* rm;
	Paint* p;
	//初始化每轮的界面
	while (true) {
		//选择按钮
		while (true) {
			rm = new RandomMaze(20, 20);
			rm->erase();
			p = new Paint();
			if (p->initPaint(*rm))
				break;
		}
		p->paintPath(*rm, rm->minPath());
		delete p;
	}
	return 0;
}