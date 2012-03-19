#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

int main ()
{
  osgViewer::Viewer viewer;

  osg::Group* root = new osg::Group;
  osg::Geode* sphere = new osg::Geode;
  osg::Shape* shape = new osg::Sphere (osg::Vec3f(0.0, 0.0, 0.0), 1.0);
  osg::ShapeDrawable* sphereGeom = new osg::ShapeDrawable (shape);
  sphere->addDrawable (sphereGeom);
  root->addChild (sphere);

  viewer.setSceneData(root);
  viewer.run();
}
