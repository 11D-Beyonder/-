#include<GLFW/glfw3.h>
#include<iostream>
#include<algorithm>
/// <summary>
/// 接受ESC消息
/// </summary>
/// <param name="window">指定的窗口</param>
void processInput(GLFWwindow* window);
/// <summary>
/// 放置一个点
/// </summary>
/// <param name="_x">横坐标</param>
/// <param name="_y">纵坐标</param>
void drawPoint(GLint _x, GLint _y);
/// <summary>
/// 画圆
/// </summary>
/// <param name="r">半径</param>
void drawCircle(GLint r);
/// <summary>
/// 画椭圆
/// </summary>
/// <param name="_a">半长轴</param>
/// <param name="_b">半短轴</param>
void drawEllipse(GLint _a, GLint _b);
/// <summary>
/// 鼠标移动响应 获取坐标
/// </summary>
/// <param name="window">指定窗口</param>
/// <param name="x">横坐标</param>
/// <param name="y">纵坐标</param>
void cursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y);
/// <summary>
/// 鼠标点击响应
/// </summary>
/// <param name="window">指定窗口</param>
/// <param name="button">按键</param>
/// <param name="action">动作</param>
/// <param name="mods">模式</param>
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);
const GLuint SCR_WIDTH = 1000;
const GLuint SCR_HEIGHT = 700;
/// <summary>
/// 绘图标志
/// </summary>
bool isDrawing;
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
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	//glViewport函数前两个参数控制窗口左下角的位置；
	//我们还需要注册这个函数
	while (!glfwWindowShouldClose(window)) {
		//检查输入的按键
		processInput(window);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//drawEllipse(500, 200);
		//交换缓冲 双缓冲防止屏闪
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void drawPoint(GLint _x, GLint _y) {
	/* Draw a point */
	GLfloat x = (GLfloat)_x / (GLfloat)SCR_WIDTH * 2;
	GLfloat y = (GLfloat)_y / (GLfloat)SCR_HEIGHT * 2;
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x, y);
	glEnd();
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void drawCircle(GLint r) {
	GLint x = 0;
	GLint y = r;
	GLint d = 1 - r;
	while (x <= y) {
		drawPoint(x, y);
		drawPoint(y, x);
		drawPoint(-y, x);
		drawPoint(-x, y);
		drawPoint(-x, -y);
		drawPoint(-y, -x);
		drawPoint(y, -x);
		drawPoint(x, -y);
		if (d < 0) {
			d += 2 * x + 3;
		} else {
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
}
void drawEllipse(GLint _a, GLint _b) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat x = 0;
	GLfloat y = _b;
	GLfloat a = _a, b = _b;
	GLfloat d = b * b + a * a * (-b + 0.25);
	drawPoint(x, y);
	drawPoint(-x, -y);
	drawPoint(-x, y);
	drawPoint(x, -y);
	while (b * b * (x + 1.0) < a * a * (y - 0.5)) {
		if (d <= 0) {
			d += b * b * (2 * x + 3);
			++x;
		} else {
			d += b * b * (2 * x + 3) + a * a * (2 - 2 * y);
			++x;
			--y;
		}
		drawPoint(x, y);
		drawPoint(-x, -y);
		drawPoint(-x, y);
		drawPoint(x, -y);
	}
	d = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1.0) * (y - 1.0) - a * a * b * b;
	while (y > 0) {
		if (d <= 0) {
			d += b * b * (2 * x + 2) + a * a * (3 - 2 * y);
			++x;
			--y;
		} else {
			d += a * a * (3 - 2 * y);
			--y;
		}
		drawPoint(x, y);
		drawPoint(-x, -y);
		drawPoint(-x, y);
		drawPoint(x, -y);
	}
}
void cursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y) {
	x -= SCR_WIDTH / 2;
	y = SCR_HEIGHT / 2 - y;
	if (isDrawing) {
		drawEllipse(abs(GLint(x)), abs(GLint(y)));
	}
}
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			isDrawing = true;
		} else if (action == GLFW_RELEASE) {
			isDrawing = false;
		}
	}
}