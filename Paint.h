#pragma once
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include "RandomMaze.h"

constexpr auto WIDTH = 1000;
constexpr auto HEIGHT = 800;
constexpr auto MAGIN = 20;

class Paint {
public:
	Paint() {
		a = 0;
	}

	Paint(RandomMaze rm) {
		initPaint(rm);
	}

	bool initPaint(RandomMaze rm) {
		initgraph(WIDTH, HEIGHT);	// 创建绘图窗口，大小为 1000x800 像素
		setbkcolor(WHITE);
		cleardevice();
		setlinecolor(BLACK);
		//line(HEIGHT, 0, 800, HEIGHT);

		LOGFONT f;
		gettextstyle(&f);						// 获取当前字体设置
		f.lfHeight = 30;			// 设置字体高度为 30
		f.lfQuality = ANTIALIASED_QUALITY;
		setbkmode(TRANSPARENT);
		_tcscpy_s(f.lfFaceName, _T("Consolas"));
		settextstyle(&f);
		setfillcolor(RGB(52, 101, 181));
		//初始化按钮
		//Change按钮
		fillrectangle(820, 125, 960, 170);
		outtextxy(850, 130, _T("Change"));
		//Confirm按钮
		fillrectangle(820, 225, 960, 270);
		outtextxy(845, 230, _T("Confirm"));
		//Start按钮
		fillrectangle(820, 325, 960, 370);
		outtextxy(855, 330, _T("Start"));

		//求出方块的边长
		int a = (HEIGHT - (MAGIN * 2)) / max(rm.getM(), rm.getN());
		this->a = a;
		BeginBatchDraw();
		line(MAGIN, MAGIN, MAGIN + rm.getN() * a, MAGIN);
		line(MAGIN, MAGIN, MAGIN, MAGIN + rm.getM() * a);
		line(MAGIN + rm.getN() * a, MAGIN, MAGIN + rm.getN() * a, MAGIN + rm.getM() * a);
		line(MAGIN, MAGIN + rm.getM() * a, MAGIN + rm.getN() * a, MAGIN + rm.getM() * a);
		for (int i = rm.getCount(); i < rm.getEdgeNum(); i++) {
			int value;
			if (rm.getEdge()[i] % (2 * rm.getN() - 1) <= (rm.getN() - 2)) {	//竖边
				value = rm.getEdge()[i] / (2 * rm.getN() - 1) * rm.getN() + rm.getEdge()[i] % (2 * rm.getN() - 1) + 1;
				int i = (value - 1) / rm.getN();
				int j = (value - 1) % rm.getN();
				line(MAGIN + (j + 1) * a, MAGIN + i * a, MAGIN + (j + 1) * a, MAGIN + (i + 1) * a);
			}
			else {	//横边
				value = ((rm.getEdge()[i] + rm.getN()) / (2 * rm.getN() - 1) - 1) * rm.getN() + (rm.getEdge()[i] + rm.getN()) % (2 * rm.getN() - 1) + 1;
				int i = (value - 1) / rm.getN();
				int j = (value - 1) % rm.getN();
				line(MAGIN + j * a, MAGIN + (i + 1) * a, MAGIN + (j + 1) * a, MAGIN + (i + 1) * a);
			}
		}
		EndBatchDraw();
		return buttom();
	}

	//画Change和Confirm按钮
	bool buttom() {
		ExMessage m;		// 定义消息变量
		// 获取一条鼠标或按键消息
		while (true) {
			m = getmessage(EM_MOUSE | EM_KEY);
			switch (m.message){
			case WM_MOUSEMOVE:
				if (m.x >= 820 && m.x <= 960 && m.y >= 125 && m.y <= 170) {
					setfillcolor(RGB(69, 120, 202));
					fillrectangle(820, 125, 960, 170);
					outtextxy(850, 130, _T("Change"));
				}
				else if (m.x >= 820 && m.x <= 960 && m.y >= 225 && m.y <= 270) {
					setfillcolor(RGB(69, 120, 202));
					fillrectangle(820, 225, 960, 270);
					outtextxy(845, 230, _T("Confirm"));
				}
				else {
					setfillcolor(RGB(52, 101, 181));
					fillrectangle(820, 125, 960, 170);
					outtextxy(850, 130, _T("Change"));
					fillrectangle(820, 225, 960, 270);
					outtextxy(845, 230, _T("Confirm"));
				}
				break;
			case WM_LBUTTONDOWN:
				if (m.x >= 820 && m.x <= 960 && m.y >= 125 && m.y <= 170)
					return false;	//继续选择
				else if (m.x >= 820 && m.x <= 960 && m.y >= 225 && m.y <= 270)
					return true;	//退出选择
				break;
			}
		}
	}

	//画Start按钮
	void buttom2() {
		ExMessage m;		// 定义消息变量
		// 获取一条鼠标或按键消息
		bool isPress = false;
		while (!isPress) {
			m = getmessage(EM_MOUSE | EM_KEY);
			switch (m.message) {
			case WM_MOUSEMOVE:
				if (m.x >= 820 && m.x <= 960 && m.y >= 325 && m.y <= 370) {
					setfillcolor(RGB(69, 120, 202));
					fillrectangle(820, 325, 960, 370);
					outtextxy(855, 330, _T("Start"));
				}
				else {
					setfillcolor(RGB(52, 101, 181));
					fillrectangle(820, 325, 960, 370);
					outtextxy(855, 330, _T("Start"));
				}
				break;
			case WM_LBUTTONDOWN:
				if (m.x >= 820 && m.x <= 960 && m.y >= 325 && m.y <= 370)
					isPress = true;
				break;
			}
		}
	}

	//画最小路径
	void paintPath(RandomMaze rm, vector<int>* load) {
		buttom2();
		setlinecolor(WHITE);
		BeginBatchDraw();
		for (int t = load->size() - 1; t >= 0; t--) {
			int value = (*load)[t];
			int i = (value - 1) / rm.getN();
			int j = (value - 1) % rm.getN();
			//选择路径颜色
			switch (t % 5) {
			case 0:
				setfillcolor(RGB(43, 84, 151));
				break;
			case 1:
				setfillcolor(RGB(52, 101, 181));
				break;
			case 2:
				setfillcolor(RGB(69, 120, 202));
				break;
			case 3:
				setfillcolor(RGB(99, 142, 211));
				break;
			case 4:
				setfillcolor(RGB(130, 164, 219));
				break;
			}
			fillrectangle(MAGIN + j * a + 5, MAGIN + i * a + 5, MAGIN + (j + 1) * a - 5, MAGIN + (i + 1) * a - 5);
			FlushBatchDraw();
			Sleep(500);
		}
		EndBatchDraw();
	}


	~Paint() {
		system("pause");
		closegraph();
	}
private:
	int a;
};