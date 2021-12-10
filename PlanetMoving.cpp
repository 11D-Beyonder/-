#include<GL/glut.h>
#include<cmath>
#define PI 3.1415926535
void init() {
	//������ȵ���
	glEnable(GL_DEPTH_TEST);
	//����ɫΪ��ɫ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void changeSize(GLint w, GLint h) {
	if (h == 0) {
		h = 1;
	}
	//�����ӿ�
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	//����ͶӰ���� ��λ���������ջ
	glLoadIdentity();
	//�����߱�
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	//ָ��͸��ͶӰ�Ĺ۲�ռ�
	gluPerspective(45.0, fAspect, 1.0, 500.0);
	//����ͼ�������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display() {
	//����õĶ�����ִ��
	//��̫��ת�ĽǶ�
	static GLfloat fElect1 = 0.0f;
	//�Ƶ���ת�ĽǶ�
	static GLfloat fElect2 = 0.0f;
	//�����ɫ����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ģ����ͼ�����ջ
	glMatrixMode(GL_MODELVIEW);
	//����ģ����ͼ����
	glLoadIdentity();
	//����z�Ḻ���ƶ� ���ڹ۲�ռ���
	glTranslatef(0.0f, 0.0f, -250.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	//����̫��
	glutSolidSphere(32.0f, 15, 15);
	glColor3f(0.0f, 1.0f, 1.0f);
	//ת�����������ջ
	glPushMatrix();
	//��y����ת
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	//ƽ��
	glTranslatef(80.0f, 0.0f, 0.0f);
	//��������
	glutSolidSphere(6.0f, 15, 15);
	//�ָ�ģ����ͼ����
	glPopMatrix();
	//���浱ǰģ����ͼ����
	glColor3f(0.933f, 0.901f, 0.5215f);
	glPushMatrix();
	glTranslatef(80 * cos(fElect1 * PI / 180.0), 0, -80 * sin(fElect1 * PI / 180.0));
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(-80 * cos(fElect1 * PI / 180.0), 0, 80 * sin(fElect1 * PI / 180.0));
	glutSolidSphere(3.0f, 15, 15);
	glPopMatrix();
	//ת�ٲ���10��
	fElect1 += 1.0f;
	if (fElect1 > 360.0f) {
		fElect1 = 1.0f;
	}
	fElect2 += 10.0f;
	if (fElect2 > 360.f) {
		fElect2 = 10.0f;
	}
	glutSwapBuffers();
}
void timeFunc(GLint value) {
	//100ms����ö�ʱ���ص�����
	glutPostRedisplay();
	glutTimerFunc(100, timeFunc, 1);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("�յ���ģ��");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutTimerFunc(500, timeFunc, 1);
	init();
	glutMainLoop();
	return 0;
}