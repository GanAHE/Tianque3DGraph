// osgEarthDemo.cpp: 定义应用程序的入口点。
//
#include <Windows.h>
#include<osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers> 
#include<osgDB/ReadFile>
#include <osgEarth/Notify>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/MapNode>
#include <iostream>
#include <osgEarth/Metrics>
#include "OsgTextPointStyle.h"
#include "TextPointTest.h"
using namespace std;

int main(int argc, char** argv)
{
	cout << "====Start====" << endl;
	osgViewer::Viewer viewer;
    osg::ref_ptr<osgViewer::Viewer> viewer_ptr = &viewer;
    {
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->x = 40;
        traits->y = 40;
        traits->width = 1200;
        traits->height = 960;
        traits->windowDecoration = true;
        traits->doubleBuffer = true;
        traits->sharedContext = 0;


        osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

        osg::ref_ptr<osg::Camera> camera = new osg::Camera;
        camera->setGraphicsContext(gc.get());
        camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
        GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
        camera->setDrawBuffer(buffer);
        camera->setReadBuffer(buffer);

        // add this slave camera to the viewer, with a shift left of the projection matrix
        viewer_ptr->addSlave(camera.get());
    }

    // manipulator
    osg::ref_ptr<osgEarth::Util::EarthManipulator> mainManipulator = new osgEarth::Util::EarthManipulator;
    const osgEarth::Viewpoint* viewpoint = new osgEarth::Viewpoint("home", 114.424861, 30.472961, 100, 0, -90, 2E6);
    mainManipulator->setHomeViewpoint(*viewpoint, 0.1);
    mainManipulator->getSettings()->setMinMaxDistance(1e-7, 2e7);
    viewer.setCameraManipulator(mainManipulator);


    // disable the small-feature culling
    viewer.getCamera()->setSmallFeatureCullingPixelSize(-1.0f);

    // load an earth file, and support all or our example command-line options
    // and earth file <external> tags
    string path = "../../source/earth/mapbox_mystyle.earth";
    osg::Node* globe = osgDB::readNodeFile(path);
    osgEarth::MapNode* mapNode = osgEarth::MapNode::get(globe);
    //state
    viewer.addEventHandler(new osgViewer::StatsHandler());
    if (mapNode)
    {
        GanAHE::TextPointTest testTextPoint(&viewer);
        testTextPoint.testDrawSimpleTextPoint(mapNode);
        testTextPoint.testDrawClusterPoint(mapNode);
        viewer.setSceneData(mapNode);
        //viewer.setSceneData(initSky(viewer_ptr,mapNode).get());
        return osgEarth::Metrics::run(viewer);
    }
	return 0;
}