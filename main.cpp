// Template1.cpp : Defines the entry point for the console application.
//
#include <cmath>
#include <GL/glut.h>

constexpr GLdouble sceneHeight = 1000;
constexpr GLdouble sceneWidth = 1000;
constexpr GLdouble triangleSideWidth = sceneWidth / 5;
const GLdouble triangleHeight = std::sqrt(
	std::pow(triangleSideWidth, 2) - std::pow(triangleSideWidth / 2, 2));

//Chaninging the dierctions of rotation of rings and triangles should be possible

void drawInnerRing()
{

}

void MyDisplay(void) {
	// The new scene
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
//	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);// OpenGL�a state
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	glVertex2f(100.0f, 50.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green
	glVertex2f(450.0f, 400.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue
	glVertex2f(450.0f, 50.0f);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue
	glVertex2f(450.0f, 400.0f);
	glVertex2f(800.0f, 50.0f);
	glVertex2f(800.0f, 400.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(800.0f, 50.0f);
	glVertex2f(450.0f, 50.0f);
	glVertex2f(450.0f, 400.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(100.0f, 50.0f);
	glVertex2f(100.0f, 400.0f);
	glVertex2f(450.0f, 400.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(100.0f, 400.0f);
	glVertex2f(100.0f, 750.0f);
	glVertex2f(450.0f, 400.0f);

	//glPushMatrix();
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2f(100.0f, 750.0f);
	glVertex2f(450.0f, 750.0f);
	glVertex2f(450.0f, 400.0f);
	//glPopMatrix();

	glVertex2f(450.0f, 750.0f);
	glVertex2f(800.0f, 750.0f);
	glVertex2f(800.0f, 400.0f);

	glVertex2f(800.0f, 400.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(450.0f, 400.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(450.0f, 750.0f);

	glEnd();

	// The end of scene
	glFlush();//start processing buffered OpenGL routines
}
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
									 /* initialize viewing values */
	glViewport(0, 0, 500, 500);//window origin and size
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();//=1
	gluOrtho2D(0.0, sceneWidth, 0.0, sceneHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//=1
}

int main(int argc, char** argv) { //<- for normal API
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(640, 480);//initial window size
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spinning Triangles");//create widnow, hello title bar
	MyInit();
	glutDisplayFunc(MyDisplay);//
	glutMainLoop();//enter main loop and process events
	return 0;
}
