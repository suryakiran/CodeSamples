#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/Material>
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

  osg::StateSet* state = sphere->getOrCreateStateSet();
  osg::Light* light = new osg::Light (0);
  light->setDiffuse(osg::Vec4(1.0, 0.8, 0.8, 1.0));
  light->setSpecular(osg::Vec4(0.0, 0.0, 1.0, 1.0));
  state->setAttributeAndModes (light);

  osg::Material* mat = new osg::Material();
  mat->setDiffuse (osg::Material::BACK, osg::Vec4(1.0, 1.0, 0.0, 1.0));
  mat->setSpecular (osg::Material::FRONT, osg::Vec4(0.0, 0.0, 1.0, 1.0));
  mat->setShininess (osg::Material::FRONT, 125.0);
  state->setAttributeAndModes (mat);

  viewer.setSceneData(root);
  viewer.run();
}
