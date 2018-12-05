// Template1.cpp : Defines the entry point for the console application.
//
#include <cmath>
#include <GL/glut.h>

constexpr GLdouble sceneHeight = 1000;
constexpr GLdouble sceneWidth = 1000;
constexpr GLdouble triangleSideWidth = sceneWidth / 12;
constexpr GLdouble squareDiagonal = triangleSideWidth * 3 * 2;
const GLdouble triangleHeight = std::sqrt(
	std::pow(triangleSideWidth, 2) - std::pow(triangleSideWidth / 2, 2));

constexpr double maxExpansionDistance = triangleSideWidth;
constexpr double minExpansionDistance = triangleSideWidth / 2;
static double expansionDistanceDelta = 1;
static double expansionDistance = minExpansionDistance;

constexpr double rotationAngleDelta = 10;
static double rotationAngle = 0;

void init();
void draw_scene();
void draw_quater();
void draw_triangle_tower(unsigned triangle_count);
void set_random_color();
void rotate_around_center_of_mass();
void redraw(int);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(640, 480);//initial window size
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spinning Triangles");//create widnow, hello title bar
	init();
	glutDisplayFunc(draw_scene);//
	glutTimerFunc(100, redraw, 1);
	glutMainLoop();//enter main loop and process events
	return 0;
}
//Chaninging the dierctions of rotation of rings and triangles should be possible
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
									 /* initialize viewing values */
	glViewport(0, 0, 500, 500);//window origin and size
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();//=1
	gluOrtho2D(0.0, sceneWidth, 0.0, sceneHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//=1
}

void draw_scene(void) {
	// The new scene
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(squareDiagonal / 2, squareDiagonal / 2, 0.0f);
	for(unsigned side = 0; side < 4; ++side) {
		glPushMatrix();
		glTranslatef(triangleSideWidth * 3, triangleSideWidth * 3, 0.0f);
		glRotatef(90 * side, 0.0f, 0.0f, 1.0f);
		draw_quater();
		glPopMatrix();
	}
	glPopMatrix();
	// The end of scene
	glFlush();//start processing buffered OpenGL routines
}
void draw_quater()
{
	glPushMatrix();
	for (unsigned i = 3; i > 0; --i) {
		glTranslatef(expansionDistance, 0.0f, 0.0f); //expanding
		draw_triangle_tower(i);
		glTranslatef(triangleSideWidth, 0.0f, 0.0f);
	}
	glPopMatrix();
}

void draw_triangle_tower(unsigned int triangle_cout)
{
	glPushMatrix();
	for(unsigned i = 0; i < triangle_cout; ++i) {
		glTranslatef(0.0f, expansionDistance,  0.0f); // expanding
		glPushMatrix();
		set_random_color();
		glTranslatef(0.0f, triangleSideWidth * i, 0.0f);
		rotate_around_center_of_mass();
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, triangleSideWidth);
		glVertex2f(triangleSideWidth, 0.0f);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

void set_random_color()
{
	glColor4f(
		std::rand() % 10 * 0.1f,
		std::rand() % 10 * 0.1f,
		std::rand() % 10 * 0.1f,
		1.0f);
}

void rotate_around_center_of_mass()
{
	glTranslatef(triangleSideWidth / 3, triangleSideWidth / 3, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-triangleSideWidth / 3, -triangleSideWidth / 3, 0.0f);
}

void redraw(int)
{
	if ((expansionDistance += expansionDistanceDelta) > maxExpansionDistance ||
	expansionDistance < minExpansionDistance)
		expansionDistanceDelta = -expansionDistanceDelta;

	if ((rotationAngle += rotationAngleDelta) >= 360)
		rotationAngle -= 360;
	else if (rotationAngle <= 0)
		rotationAngle += 360;

	draw_scene();
	glutTimerFunc(100, redraw, 1);
}
