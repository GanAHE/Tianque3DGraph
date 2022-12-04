#include "TextPointAttribute.h"
#include <iostream>
namespace chcEarth {
	TextPointAttribute::TextPointAttribute()
	{
	}
	TextPointAttribute::TextPointAttribute(osgEarth::GeoPoint& point)
		:_geoPosition(osgEarth::GeoPoint(point))
	{
		_fontPath = "font/simfang.ttf";
	}

	TextPointAttribute::TextPointAttribute(osgEarth::GeoPoint& point, const std::string& text)
		:_geoPosition(osgEarth::GeoPoint(point))
	{
		_text = text;
	}

	TextPointAttribute::TextPointAttribute(const TextPointAttribute& attribute)
	{
		this->_geoPosition = osgEarth::GeoPoint(attribute._geoPosition);
		this->_pointSize = attribute._pointSize;
		this->_fillColor = osgEarth::Color(attribute._fillColor);
		this->_borderScale = attribute._borderScale;
		this->_borderColor = osgEarth::Color(attribute._borderColor);
		this->_text = attribute._text;
		this->_textSize = attribute._textSize;
		this->_textColor = attribute._textColor;
		this->_fontPath = attribute._fontPath;
	}

	TextPointAttribute::~TextPointAttribute()
	{
	}

	void TextPointAttribute::updatePosition(osgEarth::GeoPoint& point)
	{
		_geoPosition = osgEarth::GeoPoint(point);
	}

	void TextPointAttribute::setFillColor(const osgEarth::Color color)
	{
		_fillColor = color;
	}

	void TextPointAttribute::setPointSize(float size)
	{
		_pointSize = size;
		//calc the text size
		calcTextSize();
	}

	void TextPointAttribute::setText(const std::string text)
	{
		_text = text;
		//calc the text size
		calcTextSize();
	}

	void TextPointAttribute::setTextColor(const osgEarth::Color textColor)
	{
		_textColor = textColor;
	}

	void TextPointAttribute::setFontPath(const std::string path)
	{
		_fontPath = path;
	}

	void TextPointAttribute::setBorderScale(float scale)
	{
		if (scale < 0) {
			_borderScale = 0;
		}
		else if (scale > 1) {
			_borderScale = 1;
		}
		else {
			_borderScale = scale;
		}
	}

	void TextPointAttribute::setBorderColor(osgEarth::Color color)
	{
		_borderColor = color;
	}


	const osgEarth::GeoPoint& TextPointAttribute::getPosition()
	{
		return _geoPosition;
	}
	const std::string& TextPointAttribute::getText()
	{
		return _text;
	}
	const float TextPointAttribute::getPointSize()
	{
		return _pointSize;
	}
	const osgEarth::Color TextPointAttribute::getTextColor()
	{
		return _textColor;
	}
	const float TextPointAttribute::getTextSize() {
		return _textSize;
	}
	const std::string& TextPointAttribute::getFontPath()
	{
		return _fontPath;
	}
	const osgEarth::Color TextPointAttribute::getFillColor()
	{
		return _fillColor;
	}
	const float TextPointAttribute::getBorderScale()
	{
		return _borderScale;
	}
	const bool TextPointAttribute::drawBorderEnable()
	{
		return _borderScale > 0;
	}
	const osgEarth::Color TextPointAttribute::getBorderColor()
	{
		return _borderColor;
	}

	const void TextPointAttribute::calcTextSize() {
		if (_text.empty()) {
			return;
		}
		int length = _text.length();
		//calculate text size by scale
		if (length <= 2) {
			_textSize = _pointSize * 0.75;
		}
		else if (length == 3) {
			_textSize = _pointSize * 0.58;
		}
		else if (length == 4)
		{
			_textSize = _pointSize * 0.42;
		}
		else {
			_textSize = _pointSize * 0.2;
		}
	}
}