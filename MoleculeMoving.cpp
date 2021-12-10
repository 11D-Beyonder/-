#include<GL/glut.h>
void init() {
	//������ȵ���
	glEnable(GL_DEPTH_TEST);
	//����ɫΪ��ɫ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
void changeSize(GLint w,GLint h) {
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
	//��ԭ��ת�ĽǶ�
	static GLfloat fElect1 = 0.0f;
	//�����ɫ����Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ģ����ͼ�����ջ
	glMatrixMode(GL_MODELVIEW);
	//����ģ����ͼ����
	glLoadIdentity();
	//����z�Ḻ���ƶ� ���ڹ۲�ռ���
	glTranslatef(0.0f, 0.0f, -250.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	//����ԭ��
	glutSolidSphere(12.0f, 15, 15);
	glColor3f(0.0f, 0.0f, 0.0f);
	//ת�����������ջ
	glPushMatrix();
	//��y����ת
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	//ƽ��
	glTranslatef(90.0f, 0.0f, 0.0f);
	//��������
	glutSolidSphere(6.0f, 15, 15);
	//�ָ�ģ����ͼ����
	glPopMatrix();
	//���浱ǰģ����ͼ����
	glPushMatrix();
	//��z����ת45
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	//�ڶ�������
	glutSolidSphere(6.0f, 15, 15);
	//�ָ�ģ����ͼ����
	glPopMatrix();
	//���浱ǰģ����ͼ����
	glPushMatrix();
	//��z����ת-45
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	//��y����ת
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	//����������
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	fElect1 += 10.0f;
	if (fElect1 > 360.0f) {
		fElect1 = 10.0f;
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
	glutCreateWindow("����ģ��");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutTimerFunc(500, timeFunc, 1);
	init();
	glutMainLoop();
	return 0;
}