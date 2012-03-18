#include "opengl.hxx"

void display()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSolidSphere (1.5, 500, 500);
  glutSwapBuffers();
}

void reshape (int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (30, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
}

void init()
{
  glClearColor (0.5, 0.0, 0.0, 1.0);
  glShadeModel (GL_SMOOTH);
  GLfloat mat_specular [] = {1.0, 1.0, 1.0, 0.0};
  GLfloat mat_diffuse [] = {0.8, 1.0, 1.0, 1.0};
  GLfloat mat_shine [] = {50.0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (400, 400);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Axes");
  init();
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutMainLoop();
}
