namespace GanAHE{
#include "osgEarthDemo.h"
#include <Windows.h>
#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include <iostream>

    int testOsgCow() {
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
        viewer.setSceneData(osgDB::readNodeFile("../../source/data/tree.osg"));
        return viewer.run();
    }
}
