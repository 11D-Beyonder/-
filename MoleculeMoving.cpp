#include<GL/glut.h>
void init() {
	//启用深度调试
	glEnable(GL_DEPTH_TEST);
	//背景色为白色
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void changeSize(GLint w,GLint h) {
	if (h == 0) {
		h = 1;
	}
	//设置视口
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	//重置投影矩阵 单位矩阵推入堆栈
	glLoadIdentity();
	//计算宽高比
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	//指定透视投影的观察空间
	gluPerspective(45.0, fAspect, 1.0, 500.0);
	//对视图矩阵操作
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display() {
	//绕原子转的角度
	static GLfloat fElect1 = 0.0f;
	//清除颜色和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//模型视图矩阵堆栈
	glMatrixMode(GL_MODELVIEW);
	//重置模型视图矩阵
	glLoadIdentity();
	//沿着z轴负向移动 放在观察空间内
	glTranslatef(0.0f, 0.0f, -250.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	//绘制原子
	glutSolidSphere(12.0f, 15, 15);
	glColor3f(0.0f, 0.0f, 0.0f);
	//转换矩阵推入堆栈
	glPushMatrix();
	//绕y轴旋转
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	//平移
	glTranslatef(90.0f, 0.0f, 0.0f);
	//画出电子
	glutSolidSphere(6.0f, 15, 15);
	//恢复模型视图矩阵
	glPopMatrix();
	//保存当前模型视图矩阵
	glPushMatrix();
	//绕z轴旋转45
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	//第二个电子
	glutSolidSphere(6.0f, 15, 15);
	//恢复模型视图矩阵
	glPopMatrix();
	//保存当前模型视图矩阵
	glPushMatrix();
	//绕z轴旋转-45
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	//绕y轴旋转
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	//第三个电子
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	fElect1 += 10.0f;
	if (fElect1 > 360.0f) {
		fElect1 = 10.0f;
	}
	glutSwapBuffers();
}
void timeFunc(GLint value) {
	//100ms后调用定时器回调函数
	glutPostRedisplay();
	glutTimerFunc(100, timeFunc, 1);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("分子模型");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutTimerFunc(500, timeFunc, 1);
	init();
	glutMainLoop();
	return 0;
}