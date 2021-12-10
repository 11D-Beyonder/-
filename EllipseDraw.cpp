#include<GLFW/glfw3.h>
#include<iostream>
#include<algorithm>
/// <summary>
/// ����ESC��Ϣ
/// </summary>
/// <param name="window">ָ���Ĵ���</param>
void processInput(GLFWwindow* window);
/// <summary>
/// ����һ����
/// </summary>
/// <param name="_x">������</param>
/// <param name="_y">������</param>
void drawPoint(GLint _x, GLint _y);
/// <summary>
/// ��Բ
/// </summary>
/// <param name="r">�뾶</param>
void drawCircle(GLint r);
/// <summary>
/// ����Բ
/// </summary>
/// <param name="_a">�볤��</param>
/// <param name="_b">�����</param>
void drawEllipse(GLint _a, GLint _b);
/// <summary>
/// ����ƶ���Ӧ ��ȡ����
/// </summary>
/// <param name="window">ָ������</param>
/// <param name="x">������</param>
/// <param name="y">������</param>
void cursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y);
/// <summary>
/// �������Ӧ
/// </summary>
/// <param name="window">ָ������</param>
/// <param name="button">����</param>
/// <param name="action">����</param>
/// <param name="mods">ģʽ</param>
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);
const GLuint SCR_WIDTH = 1000;
const GLuint SCR_HEIGHT = 700;
/// <summary>
/// ��ͼ��־
/// </summary>
bool isDrawing;
int main() {
	//��ʼ��GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		return -1;
	}
	//�� �� ���� 
	//����һ��GLFWwindow����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DrawLine", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	isDrawing = false;
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	//glViewport����ǰ�����������ƴ������½ǵ�λ�ã�
	//���ǻ���Ҫע���������
	while (!glfwWindowShouldClose(window)) {
		//�������İ���
		processInput(window);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//drawEllipse(500, 200);
		//�������� ˫�����ֹ����
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