#include "TextPointNode.h"
#include <osgDB/ConvertUTF>
namespace chcEarth
{
	class TextPointNode::UpdateCallBack :public osg::NodeCallback
	{
	public:
		virtual void operator()(osg::Node* node, osg::NodeVisitor* visitor) override
		{
			TextPointNode* thisNode = dynamic_cast<TextPointNode*>(node);
			if (thisNode) {
				thisNode->update();
				//traverse the NodeVisitor
				thisNode->traverse(*visitor);
			}
		}
	};


	TextPointNode::TextPointNode(const TextPointAttribute& attribute)
	{
		this->_attribute = TextPointAttribute(attribute);
		//add CallBack will make map run slowly if put a lot of TextPointNode
		//addUpdateCallback(new TextPointNode::UpdateCallBack());
	}

	osg::ref_ptr<osgText::Text> TextPointNode::buildTextDrawable() {
		_osgText = new osgText::Text();
		setTextAttribute();
		return _osgText;
	}
	osg::ref_ptr<osgEarth::PointDrawable> TextPointNode::buildPointDrawable() {
		_centerPoint = new osgEarth::PointDrawable;
		setCenterPointAttribute(false);
		return _centerPoint;
	}
	osg::ref_ptr<osgEarth::PointDrawable> TextPointNode::buildPointBorderDrawable() {
		_borderPoint = new osgEarth::PointDrawable();
		setBorderPointAttribute(false);
		return _borderPoint;
	}

	const void TextPointNode::setTextAttribute()
	{
		if (!_osgText) {
			return;
		}
		_osgText->setText(osgDB::convertStringFromUTF8toCurrentCodePage(_attribute.getText().c_str(),
			_attribute.getText().length()), osgText::String::ENCODING_UTF8);
		//text->setAutoRotateToScreen(true);
		_osgText->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
		_osgText->setCharacterSize(_attribute.getTextSize());
		_osgText->setAlignment(osgText::Text::CENTER_CENTER);
		_osgText->setAxisAlignment(osgText::Text::SCREEN);
		_osgText->setColor(_attribute.getTextColor());
		_osgText->setFont(_attribute.getFontPath());
		//_osgText->setFontResolution(50, 50);

		osg::Vec3d worldPos;
		_attribute.getPosition().toWorld(worldPos);
		_osgText->setPosition(worldPos);
		_osgText->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		_osgText->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

		_osgText->setShaderTechnique(osgText::GREYSCALE);
		// Set the render factor. Increase the render factor of the model that you want to display first
		_osgText->getOrCreateStateSet()->setRenderBinDetails(10, "RenderBin", osg::StateSet::PROTECTED_RENDERBIN_DETAILS);
	}

	const void TextPointNode::setCenterPointAttribute(bool updatePosition)
	{
		if (!_centerPoint) {
			return;
		}
		osg::Vec3d pointPos;
		_attribute.getPosition().toWorld(pointPos);
		if (updatePosition) {
			_centerPoint->setVertex(0, pointPos);
		}
		else {
			_centerPoint->pushVertex(pointPos);
		}
		_centerPoint->setPointSize(_attribute.getPointSize() * (1.0 - _attribute.getBorderScale()));
		_centerPoint->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		_centerPoint->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		_centerPoint->getOrCreateStateSet()->setRenderBinDetails(5, "RenderBin", osg::StateSet::PROTECTED_RENDERBIN_DETAILS);
		_centerPoint->setPointSmooth(true);
		_centerPoint->setColor(_attribute.getFillColor());
		_centerPoint->finish();
	}

	const void TextPointNode::setBorderPointAttribute(bool updatePosition)
	{
		if (!_borderPoint) {
			return;
		}
		osg::Vec3d pointPos;
		_attribute.getPosition().toWorld(pointPos);
		if (updatePosition) {
			_borderPoint->setVertex(0, pointPos);
		}
		else {
			_borderPoint->pushVertex(pointPos);
		}
		_borderPoint->setPointSize(_attribute.getPointSize());
		_borderPoint->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		_borderPoint->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		_borderPoint->getOrCreateStateSet()->setRenderBinDetails(1, "RenderBin", osg::StateSet::PROTECTED_RENDERBIN_DETAILS);
		_borderPoint->setPointSmooth(true);
		_borderPoint->setColor(_attribute.getBorderColor());
		_borderPoint->finish();
	}

	const void TextPointNode::buildSingleText(osgText::Text& text)
	{
		_osgText = &text;
		setTextAttribute();
	}

	const void TextPointNode::buildText()
	{
		addChild(buildTextDrawable());
	}

	const void TextPointNode::buildPoint() {
		if (_attribute.drawBorderEnable()) {
			addChild(buildPointBorderDrawable());
		}
		addChild(buildPointDrawable());
	}

	const void TextPointNode::buildAll()
	{
		buildPoint();
		buildText();
	}

	const void TextPointNode::updatePosition(osgEarth::GeoPoint& point)
	{
		_attribute.updatePosition(point);
		osg::Vec3d pointPos;
		_attribute.getPosition().toWorld(pointPos);
		_osgText->setPosition(pointPos);
		_osgText->update();
		_centerPoint->setVertex(0, pointPos);
		_borderPoint->setVertex(0, pointPos);
	}

	const void TextPointNode::update()
	{
		if (_osgText) {
			setTextAttribute();
			_osgText->update();
		}

		if (_centerPoint) {
			setCenterPointAttribute(true);
		}
		if (_attribute.drawBorderEnable() && !_borderPoint) {
			addChild(buildPointBorderDrawable());
		}
		if (_borderPoint) {
			setBorderPointAttribute(true);
		}
	}

	const void TextPointNode::setVisibility(bool visible)
	{
		if (visible) {
			setAllChildrenOn();
		}
		else {
			setAllChildrenOff();
		}
	}

	const void TextPointNode::release()
	{
		try {
			if (_osgText) {
				removeChild(_osgText);
			}
			if (_centerPoint) {
				removeChild(_centerPoint);
			}

			if (_borderPoint) {
				removeChild(_borderPoint);
			}

		}
		catch (exception e) {

		}

	}

	TextPointAttribute& TextPointNode::getNodeAttribute()
	{
		return _attribute;
	}



	TextPointNode::~TextPointNode()
	{
	}
}