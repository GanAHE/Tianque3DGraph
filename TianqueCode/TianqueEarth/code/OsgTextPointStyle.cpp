#include "OsgTextPointStyle.h"
using namespace osgEarth::Annotation;
namespace chcEarth
{
	OsgTextPointStyle::OsgTextPointStyle(osgEarth::MapNode* mapNode)
	{
		mMapNode = mapNode;
	}

	void OsgTextPointStyle::drawAll()
	{
		//drawText();
		//drawPoint();
		drawOsgTextSymbolPoint();
	}

	void OsgTextPointStyle::drawPoint()
	{
		Style circleStyle;
		circleStyle.getOrCreate<osgEarth::TextSymbol>()->alignment() = osgEarth::TextSymbol::ALIGN_CENTER_CENTER;
		circleStyle.getOrCreate<osgEarth::TextSymbol>()->fill()->color() = osgEarth::Color::Yellow;
		circleStyle.getOrCreate<osgEarth::TextSymbol>()->content()->set("CircleName", "Circle");
		circleStyle.getOrCreate<osgEarth::TextSymbol>()->declutter() = false;
		circleStyle.getOrCreate<osgEarth::TextSymbol>()->layout() = osgEarth::TextSymbol::LAYOUT_VERTICAL;
		circleStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::White);

		// circleStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		// circleStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_DRAPE;
		// circleStyle.getOrCreate<RenderSymbol>()
		//  A lat/long SRS for specifying points.
		const osgEarth::SpatialReference* geoSRS = mMapNode->getMapSRS()->getGeographicSRS();
		CircleNode* circle = new CircleNode();
		circle->set(
			GeoPoint(geoSRS, 114.256, 30.123, 100., osgEarth::AltitudeMode::ALTMODE_RELATIVE),
			Distance(300, Units::KILOMETERS),
			circleStyle,
			Angle(0.0, Units::DEGREES),
			Angle(360.0, Units::DEGREES),
			true);
		circle->setName("SD");
		osg::Group* annoGroup = new osg::Group();
		annoGroup->addChild(circle);
		mMapNode->addChild(annoGroup);
	}

	void OsgTextPointStyle::drawText()
	{
		// Style our labels:
		osgEarth::Style labelStyle;
		labelStyle.getOrCreate<osgEarth::TextSymbol>()->alignment() = osgEarth::TextSymbol::ALIGN_CENTER_CENTER;
		labelStyle.getOrCreate<osgEarth::TextSymbol>()->fill()->color() = osgEarth::Color(Color::Blue, 1.0);

		osgEarth::Annotation::LabelNode* label = new osgEarth::Annotation::LabelNode("7", labelStyle);
		// A lat/long SRS for specifying points.
		const osgEarth::SpatialReference* geoSRS = mMapNode->getMapSRS()->getGeographicSRS();
		label->setPosition(osgEarth::GeoPoint(geoSRS, 113.205, 30.2156, 100.0, osgEarth::AltitudeMode::ALTMODE_RELATIVE));
		std::cout << "Text center" << label->getBound().radius() << std::endl;

		mMapNode->addChild(label);
	}

	void OsgTextPointStyle::drawOsgTextSymbolPoint()
	{

	}

}