#ifndef TEXT_POINT_NODE_H
#define TEXT_POINT_NODE_H

#include <osg/Switch>
#include <osg/Drawable>
#include <osgText/Text>
#include <osgEarthSymbology/Color>
#include <osgEarth/PointDrawable>
#include <osgEarthAnnotation/Draggers>
#include "TextPointAttribute.h"
using namespace std;
namespace chcEarth
{
	class TextPointNode :public osg::Switch
	{
		class UpdateCallBack;
		friend class UpdateCallBack;
		//The Android platform needs to turn off Culling, otherwise the drawing may not display 
		// at first until it zooms in near the point. 
		//wangdinggan on 2022/11/18
		//setCullingActive(false);
	public:
		TextPointNode(const TextPointAttribute& attribute);
		~TextPointNode();

	public:
		const void updatePosition(osgEarth::GeoPoint& point);
		const void update();
		const void setVisibility(bool visible);
		const void buildText();
		const void buildPoint();
		const void buildAll();
		const void buildSingleText(osgText::Text& text);
		const void release();
		TextPointAttribute& getNodeAttribute();

	private:
		osg::ref_ptr<osgText::Text> buildTextDrawable();
		osg::ref_ptr<osgEarth::PointDrawable> buildPointDrawable();
		osg::ref_ptr<osgEarth::PointDrawable> buildPointBorderDrawable();
		const void setTextAttribute();
		const void setCenterPointAttribute(bool updatePosition);
		const void setBorderPointAttribute(bool updatePosition);

	private:
		TextPointAttribute _attribute;
		osg::ref_ptr<osgText::Text> _osgText;
		osg::ref_ptr<osgEarth::PointDrawable> _centerPoint;
		osg::ref_ptr<osgEarth::PointDrawable> _borderPoint;

	};
}

#endif // TEXT_POINT_NODE_H