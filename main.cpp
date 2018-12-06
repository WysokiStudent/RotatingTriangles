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

constexpr double triangleRotationAngleDelta = 10;
static double triangleRotationAngle = 0;

constexpr double ringRotationAngleDelta[] = {1, -1, 5};
static double ringRotationAngle[] = {0, 0, 0};

void init();
void draw_scene();
void drawRings();
void drawTriangle();
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
	glTranslatef(sceneWidth / 2, sceneHeight / 2, 0.0f);
	drawRings();
	glPopMatrix();
	// The end of scene
	glFlush();//start processing buffered OpenGL routines
}

void drawRings()
{
	glPushMatrix();
	for (unsigned ring = 0; ring < 3; ++ring) {
		glPushMatrix();
		glRotatef(ringRotationAngle[ring], 0.0f, 0.0f, 1.0f);
		for (unsigned side = 0; side < 4; ++side) {
			glRotatef(90, 0.0f, 0.0f, 1.0f);
			for (unsigned triangle = 0; triangle <= ring; ++triangle) {
				glPushMatrix();
				glTranslatef(triangleSideWidth * triangle, triangleSideWidth * (ring - triangle), 0.0f);
			glTranslatef(expansionDistance * (triangle + 1), expansionDistance * (ring + 1 - triangle), 0.0f);
				drawTriangle();
				glPopMatrix();
			}
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawTriangle()
{
		glPushMatrix();
		set_random_color();
		rotate_around_center_of_mass();
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, triangleSideWidth);
		glVertex2f(triangleSideWidth, 0.0f);
		glEnd();
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
	glRotatef(triangleRotationAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-triangleSideWidth / 3, -triangleSideWidth / 3, 0.0f);
}

void redraw(int)
{
	if ((expansionDistance += expansionDistanceDelta) > maxExpansionDistance ||
	expansionDistance < minExpansionDistance)
		expansionDistanceDelta = -expansionDistanceDelta;

	if ((triangleRotationAngle += triangleRotationAngleDelta) >= 360)
		triangleRotationAngle -= 360;
	else if (triangleRotationAngle <= 0)
		triangleRotationAngle += 360;

	for (unsigned ring = 0; ring < 3; ++ring) {
		if ((ringRotationAngle[ring] += ringRotationAngleDelta[ring]) >= 360)
		ringRotationAngle[ring] -= 360;
		else if (ringRotationAngle[ring] <= 0)
		ringRotationAngle[ring] += 360;
	}

	draw_scene();
	glutTimerFunc(100, redraw, 1);
}
