#pragma once
#ifndef OSGTEXT_POINTSTYLE_H
#define OSGTEXT_POINTSTYLE_H

#include <osgDB/FileUtils>
#include <osgText/Text>
#include <osgDB/ConvertUTF>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/FeatureNode>

namespace chcEarth
{
    /// @brief OsgEarth绘制
    class OsgTextPointStyle
    {

    private:
        osgEarth::MapNode *mMapNode;

    private:
        void drawOutsizeCircle(osgEarth::GeoPoint& position, double radius);

    public:
        OsgTextPointStyle(){};
        OsgTextPointStyle(osgEarth::MapNode *mapNode);

        void drawAll();
        void drawText();
        void drawPoint();
        void drawOsgTextSymbolPoint();
        ~OsgTextPointStyle(){};
    };
}

#endif // OSGTEXT_POINTSTYLE_H END