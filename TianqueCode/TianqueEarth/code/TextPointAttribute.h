#pragma once
#ifndef TEXT_POINT_ATTRIBUTE_H
#define TEXT_POINT_ATTRIBUTE_H
#include <osg/ref_ptr>
#include <osgEarth/GeoData>
#include <osgEarthSymbology/Color>
namespace chcEarth {
	class TextPointAttribute
	{
	public:
		TextPointAttribute();
		TextPointAttribute(osgEarth::GeoPoint& point);
		TextPointAttribute(osgEarth::GeoPoint& point, const std::string& text);
		TextPointAttribute(const TextPointAttribute& attribute);
		~TextPointAttribute();
	public:
		void updatePosition(osgEarth::GeoPoint& point);
		void setFillColor(const osgEarth::Color color);
		void setPointSize(float size);
		void setText(const std::string text);
		void setTextColor(const osgEarth::Color textColor);
		void setFontPath(const std::string path);
		void setBorderScale(float scale);
		void setBorderColor(osgEarth::Color color);

	public:
		const osgEarth::GeoPoint& getPosition();
		const std::string& getText();
		const float getPointSize();
		const osgEarth::Color getTextColor();
		const float getTextSize();
		const std::string& getFontPath();
		const osgEarth::Color getFillColor();
		const float getBorderScale();
		const bool drawBorderEnable();
		const osgEarth::Color getBorderColor();

	protected:
		osgEarth::GeoPoint _geoPosition;
		float _pointSize = 20.0;
		osgEarth::Color _fillColor = osgEarth::Color(osgEarth::Color::Orange, 0.5);

		float _borderScale = 0.0;
		osgEarth::Color _borderColor = osgEarth::Color::White;

		std::string _text;
		std::string _fontPath;
		float _textSize = 20.0;
		osgEarth::Color _textColor = osgEarth::Color::White;
	protected:
		const void calcTextSize();
	};
}


#endif // !TEXT_POINT_ATTRIBUTE_H
