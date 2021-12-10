#include<GLFW/glfw3.h>
#include<iostream>
#include<algorithm>
#include<vector>
void processInput(GLFWwindow* window);
void drawPoint(GLint _x, GLint _y);
void DDA(GLint x1, GLint y1, GLint x2, GLint y2);
void midPointBresenham(GLint x1, GLint y1, GLint x2, GLint y2);
void optimizedBresenham(GLint x1, GLint y1, GLint x2, GLint y2);
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);
void cursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y);
const GLuint SCR_WIDTH = 1000;
const GLuint SCR_HEIGHT = 700;
bool isDrawing;
GLint sX, sY;
int main() {
	//初始化GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		return -1;
	}
	//宽 高 名称 
	//返回一个GLFWwindow对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DrawLine", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	isDrawing = false;
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {
		//检查输入的按键
		processInput(window);
		//清除颜色缓冲 RGB 灰度
		/*glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//释放资源
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
}
//放置一个点
void drawPoint(GLint _x,GLint _y) {
	/* Draw a point */
	//坐标为[-1,1] 做一下比例变换
	GLfloat x = (GLfloat)_x / (GLfloat)SCR_WIDTH * 2;
	GLfloat y = (GLfloat)_y / (GLfloat)SCR_HEIGHT * 2;
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x, y);
	glEnd();
}
void DDA(GLint x1, GLint y1, GLint x2, GLint y2) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (x1 == x2) {
		for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
			drawPoint(x1, y);
		}
		return;
	}
	GLint dx = x2 - x1;
	GLint dy = y2 - y1;
	GLfloat x = x1;
	GLfloat y = y1;
	GLint epsl = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	GLfloat xIncre = (GLfloat)dx / (GLfloat)epsl;
	GLfloat yIncre = (GLfloat)dy / (GLfloat)epsl;
	for (int i = 0; i <= epsl; i++) {
		drawPoint(GLint(x + 0.5), GLint(y + 0.5));
		x += xIncre;
		y += yIncre;
	}
}
//中点BH
void midPointBresenham(GLint x1, GLint y1, GLint x2, GLint y2) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//规格化输入的点
	auto regularPoints = [](GLint x1, GLint y1, GLint x2, GLint y2) {
		GLint x = x1;
		GLint y = y1;
		GLint dx = x2 - x1;
		GLint dy = y2 - y1;
		GLint d = dx - 2 * dy;
		GLint upIncre = 2 * (dx - dy);
		GLint downIncre = -2 * dy;
		std::vector<std::pair<int, int>>points;
		points.push_back(std::make_pair(x, y));
		while (x <= x2) {
			++x;
			if (d < 0) {
				++y;
				d += upIncre;
			} else {
				d += downIncre;
			}
			points.push_back(std::make_pair(x, y));	
		}
		return points;
	};
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (x1 == x2) {
		for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
			drawPoint(x1, y);
		}
		return;
	}
	if (y1 == y2) {
		for (int x = x1; x <= x2; x++) {
			drawPoint(x, y1);
		}
		return;
	}
	//点集
	std::vector<std::pair<int, int>>points;
	if (y2 > y1) {
		if (y2 - y1 <= x2 - x1) {
			//0<=k<=1
			points = regularPoints(x1, y1, x2, y2);
			for (const auto& p : points) {
				drawPoint(p.first, p.second);
			}
		} else {
			//k>1
			points = regularPoints(y1, x1, y2, x2);
			for (const auto& p : points) {
				drawPoint(p.second, p.first);
			}
		}
	} else {
		if (y1 - y2 <= x2 - x1) {
			//-1<=k<0
			points = regularPoints(-x2, y2, -x1, y1);
			for (const auto& p : points) {
				drawPoint(-p.first, p.second);
			}	
		} else {
			//k<-1
			points = regularPoints(y2, -x2, y1, -x1);
			for (const auto& p : points) {
				drawPoint(-p.second, p.first);
			}
		}
	}
}
void cursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y) {
	y = SCR_HEIGHT / 2 - y;
	x = x - SCR_WIDTH / 2;
	if (isDrawing) {
		optimizedBresenham(sX, sY, x, y);
	} else {
		sX = x;
		sY = y;
	}
}
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
	//鼠标左键点击按住开始绘图 释放停止
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_RELEASE) {
			isDrawing = false;
		} else if (action == GLFW_PRESS) {
			isDrawing = true;
		}
	}
}
//改进BH
void optimizedBresenham(GLint x1, GLint y1, GLint x2, GLint y2) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	/// <summary>
	/// lambda表达式 画0<=k<=1的直线
	/// </summary>
	/// <param name="x1">起点横坐标</param>
	/// <param name="y1">起点纵坐标</param>
	/// <param name="x2">终点横坐标</param>
	/// <param name="y2">终点纵坐标</param>
	auto regularPoints = [](GLint x1, GLint y1, GLint x2, GLint y2) {
		std::vector<std::pair<int, int>>points;
		GLint x = x1;
		GLint y = y1;
		points.push_back(std::make_pair(x, y));
		GLint dx = x2 - x1;
		GLint dy = y2 - y1;
		GLint e = -dx;
		while (x <= x2) {
			++x;
			e += 2 * dy;
			if (e > 0) {
				++y;
				e -= 2 * dx;
			}
			points.push_back(std::make_pair(x, y));
		}
		return points;
	};
	//保证x1<=x2
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (x1 == x2) {
		for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
			drawPoint(x1, y);
		}
		return;
	}
	if (y1 == y2) {
		for (int x = x1; x <= x2; x++) {
			drawPoint(x, y1);
		}
		return;
	}
	//点集
	std::vector<std::pair<int, int>>points;
	if (y2 > y1) {
		if (y2 - y1 <= x2 - x1) {
			//0<=k<=1
			points = regularPoints(x1, y1, x2, y2);
			for (const auto& p : points) {
				drawPoint(p.first, p.second);
			}
		} else {
			//k>1
			points = regularPoints(y1, x1, y2, x2);
			for (const auto& p : points) {
				drawPoint(p.second, p.first);
			}
		}
	} else {
		if (y1 - y2 <= x2 - x1) {
			//-1<=k<0
			points = regularPoints(-x2, y2, -x1, y1);
			for (const auto& p : points) {
				drawPoint(-p.first, p.second);
			}	
		} else {
			//k<-1
			points = regularPoints(y2, -x2, y1, -x1);
			for (const auto& p : points) {
				drawPoint(-p.second, p.first);
			}
		}
	}
}