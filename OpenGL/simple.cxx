#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void display ()
{
  glClearColor (0.5f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt (0.0, 1.0, 1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glScalef (1.0, 2.0, 1.0);

  glColor3f (0.0, 1.0, 1.0);
  glutWireCube(1.0);
  glFlush();
}

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (300, 250);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("HELLO");
  init();
  glutDisplayFunc (display);
  glutMainLoop();
  return 0;
}
