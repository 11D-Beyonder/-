#include<iostream>
#include"AET.h"
#include"CLine.h"
#include<vector>
const GLint WIDTH = 1000;
const GLint HEIGHT = 700;
const GLdouble eps = 1e-7;
std::vector<CPoint>points;
std::vector<CLine>lines;
GLuint preparingState;
/// <summary>
/// �������Ӧ
/// </summary>
/// <param name="window">ָ������</param>
/// <param name="button">����</param>
/// <param name="action">����</param>
/// <param name="mode">ģʽ</param>
void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mode);
/// <summary>
/// ������Ӧ
/// </summary>
/// <param name="window">ָ������</param>
/// <param name="key">��</param>
/// <param name="scancode"></param>
/// <param name="action">����</param>
/// <param name="mode"></param>
void keyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
/// <summary>
/// ����һ����
/// </summary>
void putPixels();
/// <summary>
/// ��ʼ���߼�
/// </summary>
void initLines();
int main() {
	//------------------------------------------------------------------------------------------
	//��ʼ��GLFW���ڲ������Ӧ
	if (glfwInit() != GLFW_TRUE) {
		std::cerr << "Failed to init GLFW" << std::endl;
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Polygon Filling", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwMakeContextCurrent(window);
	//------------------------------------------------------------------------------------------
	//ET��
	ET* edgeTable = nullptr;
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//״̬Ϊ0 ���õ�
		if (preparingState == 0) {
			putPixels();
		} else if (preparingState == 1) {
			//״̬Ϊ1 ��ʼ���߼�
			initLines();

			GLdouble yMin = 0x3f3f3f3f;
			GLdouble yMax = -0x3f3f3f3f;
			for (int i = 0; i<lines.size(); i++) {
				yMin = std::min(lines[i].getYMin(), yMin);
				yMax = std::max(lines[i].getYMax(), yMax);
			}
			//����ET
			edgeTable = new ET(yMin, yMax);
			for (BucketNode* bucket = edgeTable->getHead(); bucket != nullptr; bucket = bucket->getNext()) {
				for (int i = 0; i < lines.size(); i++) {
					if (fabs(lines[i].getYMin() - bucket->getY()) < eps) {
						bucket->addEdge(new EdgeNode(lines[i].getStartPoint().getX(), lines[i].getYMax(), lines[i].getShiftFactor()));
					}
				}
			}

			++preparingState;
		} else if(preparingState<=2000){
			//<=2000����ʾ������߿�
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			for (int i = 0; i < points.size() - 1; i++) {
				glVertex2f(points[i].getX() / 500.0f, points[i].getY() / 350.f);
				glVertex2f(points[i + 1].getX() / 500.0f, points[i + 1].getY() / 350.f);
			}
			glVertex2f(points.front().getX() / 500.0f, points.front().getY() / 350.f);
			glVertex2f(points.back().getX() / 500.0f, points.back().getY() / 350.f);
			glEnd();
			++preparingState;
		} else {
			//����AET�� ��Ч�߱��㷨���
			AET activeEdgeTable(edgeTable->getHead());
			while (!activeEdgeTable.isEmpty()) {
				activeEdgeTable.moveOneStep(edgeTable);
			}
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void putPixels() {
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (const CPoint& p : points) {
		glVertex2f(p.getX() / 500.0, p.getY() / 350.0);
	}
	glEnd();
}

void initLines() {
	//��������
	std::sort(points.begin(), points.end());
	glLineWidth(2.0f);
	glBegin(GL_LINE);
	glColor3f(1.0f, 0.0, 0.0);
	//����
	for (int i = 0; i < points.size()-1; i++) {
		//ˮƽ�߲���
		if (fabs(points[i].getY() - points[i + 1].getY()) < eps) {
			continue;
		}
		lines.push_back(CLine(points[i], points[i + 1]));
	}
	if (fabs(points.front().getY() - points.back().getY()) >= eps) {
		lines.push_back(CLine(points.front(), points.back()));

	}
	
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines.size(); j++) {
			if (lines[i].getEndPoint() == lines[j].getStartPoint()) {
				lines[i].shortenYMax();
			}
		}
	}

}

void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mode) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		GLdouble x, y;
		glfwGetCursorPos(window, &x, &y);
		x -= 500;
		y = 350 - y;
		std::cout << x << ' ' << y << std::endl;
		points.push_back(CPoint(x, y));
		putPixels();
	}
}

void keyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) {
	if (action != GLFW_RELEASE) {
		return;
	}
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_ENTER:
		++preparingState;
		break;
	default:
		break;
	}
}