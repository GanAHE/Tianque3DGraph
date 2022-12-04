#ifndef TEXTPOINTTEXT_H
#define TEXTPOINTTEXT_H
#include <osgEarth/GeoData>
#include<osgViewer/Viewer>
#include "TextPointNode.h"
#include "ClusterTextPointNode.h"
namespace GanAHE {
    class TextPointTest
    {
        class KeyboardHandler;
        friend class KeyboardHandler;
    public:
        TextPointTest(osgViewer::Viewer* viewer);
        void testDrawSimpleTextPoint(osgEarth::MapNode* mapNode);
        void testDrawClusterPoint(osgEarth::MapNode* mapNode);
        ~TextPointTest() {};

    private:
        osg::ref_ptr<chcEarth::ClusterTextPointNode> _clusterNode;
    };


}
#endif // !TEXTPOINTTEXT_H
