#include "opengl.hxx"

GLuint torusDisplayList;

void display ()
{
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f (1.0, 1.0, 0.0);
  glCallList (torusDisplayList);
  glutSwapBuffers();
}

void reshape (int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (30, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
}

void keyboard (unsigned char key, int posx, int posy)
{
  switch (key) {
    case 'x':
    case 'X':
      glMatrixMode (GL_MODELVIEW);
      glRotatef (10.0, 1.0, 0.0, 0.0);
      glutPostRedisplay();
      break;
    case 'y':
    case 'Y':
      glMatrixMode (GL_MODELVIEW);
      glRotatef (10.0, 0.0, 1.0, 0.0);
      glutPostRedisplay();
      break;
    case 'z':
    case 'Z':
      glMatrixMode (GL_MODELVIEW);
      glRotatef (10.0, 0.0, 0.0, 1.0);
      glutPostRedisplay();
      break;
    case 'i':
    case 'I':
      glMatrixMode (GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt (0, 0, 10, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
    default:
      break;
  }
}

void torus (int numc, int numt)
{
  double twopi = 2 * M_PI;

  for (int i = 0; i < numc; ++i) {
    glBegin (GL_QUAD_STRIP);
    for (int j = 0; j < numt; ++j) {
      for (int k = 1; k >= 0; k--) {
        double s = (i + k) % numc + 0.5;
        double t = j % numt;

        double x = (1 + 0.1*cos (s * twopi / numc)) * cos (t * twopi / numt);
        double y = (1 + 0.1*cos (s * twopi / numc)) * sin (t * twopi / numt);
        double z = 0.1 * sin (s * twopi / numc);
        glVertex3d (x, y, z);
      }
    }
    glEnd();
  }
}

void init()
{
  torusDisplayList = glGenLists(1);
  glNewList(torusDisplayList, GL_COMPILE);
  torus (8, 25);
  glEndList();
  glShadeModel (GL_SMOOTH);
  glClearColor (0.0, 0.5, 0.0, 1.0);
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitWindowSize (300, 300);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow ("Torus");
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc (keyboard);
  init();
  glutMainLoop();
  return 0;
}
