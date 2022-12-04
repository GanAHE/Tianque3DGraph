#include "ClusterTextPointNode.h"
#include <osgDB/ConvertUTF>
namespace chcEarth {
	class ClusterTextPointNode::UpdateCallBack :public osg::NodeCallback
	{
	public:
		virtual void operator()(osg::Node* node, osg::NodeVisitor* visitor) override
		{
			ClusterTextPointNode* thisNode = dynamic_cast<ClusterTextPointNode*>(node);
			if (thisNode) {
				thisNode->update();
				//traverse the NodeVisitor
				thisNode->traverse(*visitor);
			}
		}
	};

	ClusterTextPointNode::ClusterTextPointNode(const TextPointAttribute& attritube)
		:_attritbute(TextPointAttribute(attritube))
	{
		_LOD = new osg::LOD();
		_centerPointNode = new osgEarth::PointDrawable();
		_centerPointNode->setCullingActive(false);
		_updateHandler = new UpdateQueue();
		init();
		addUpdateCallback(new ClusterTextPointNode::UpdateCallBack());
	}

	const void ClusterTextPointNode::setLODMinDist(float minDist)
	{
		_LODMinDist = minDist;
	}

	const void ClusterTextPointNode::setLODMaxDist(float maxDist)
	{
		_LODMaxDist = maxDist;
	}

	const void ClusterTextPointNode::initPushPoint(osgEarth::GeoPoint& position)
	{
		osg::Vec3d scenePosition;
		position.toWorld(scenePosition);
		if (_attritbute.drawBorderEnable() && _borderPointNode) {
			_borderPointNode->pushVertex(scenePosition);
			_borderPointNode->finish();
		}
		_centerPointNode->pushVertex(scenePosition);
		_centerPointNode->finish();
	}

	const void ClusterTextPointNode::build()
	{
		_LOD->addChild(_centerPointNode, _LODMinDist, _LODMaxDist);
		if (_attritbute.drawBorderEnable() && _borderPointNode) {
			_LOD->addChild(_borderPointNode, _LODMinDist, _LODMaxDist);
		}
		addChild(_LOD, true);
	}

	const void ClusterTextPointNode::addPoint(osgEarth::GeoPoint& position)
	{
		std::lock_guard<std::mutex> locker(_Lock);
		osg::Vec3d scenePosition;
		position.toWorld(scenePosition);
		bool drawEnable = _attritbute.drawBorderEnable() && _borderPointNode;
		_updateHandler->push(0, false, [this, drawEnable, scenePosition]()
			{
				if (drawEnable) {
					_borderPointNode->pushVertex(scenePosition);
					_borderPointNode->finish();
				}
				_centerPointNode->pushVertex(scenePosition);
				_centerPointNode->finish();
			});
	}

	const void ClusterTextPointNode::clear()
	{
		std::lock_guard<std::mutex> _locker(_Lock);
		bool drawEnable = _attritbute.drawBorderEnable() && _borderPointNode;
		_updateHandler->push(0, false, [this,drawEnable]() 
			{
			if (drawEnable)
			{
				_borderPointNode->clear();
				_borderPointNode->finish();
			}
			_centerPointNode->clear();
			_centerPointNode->finish();
			});
	}

	const void ClusterTextPointNode::setVisibility(bool visible)
	{
		if (visible) {
			setAllChildrenOn();
		}
		else {
			setAllChildrenOff();
		}
	}

	ClusterTextPointNode::~ClusterTextPointNode()
	{
	}
	const float ClusterTextPointNode::getLODMinDist()
	{
		return _LODMinDist;
	}
	const float ClusterTextPointNode::getLODMaxDist()
	{
		return _LODMaxDist;
	}
	void ClusterTextPointNode::init()
	{
		if (_attritbute.drawBorderEnable()) {
			_borderPointNode = new osgEarth::PointDrawable();
			_borderPointNode->setCullingActive(false);
			initPointStyle(_borderPointNode, _attritbute.getBorderColor(), _attritbute.getPointSize(), 1);
		}
		initPointStyle(_centerPointNode, _attritbute.getFillColor(),
			_attritbute.getPointSize() * (1.0 - _attritbute.getBorderScale()),
			5);
	}

	void ClusterTextPointNode::initPointStyle(osg::ref_ptr<osgEarth::PointDrawable> point,
		const osgEarth::Color color,
		float size,
		int renderDepth)
	{
		osg::Vec3d pointPos;
		_attritbute.getPosition().toWorld(pointPos);
		point->pushVertex(pointPos);
		point->setPointSize(size);
		point->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		point->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		point->getOrCreateStateSet()->setRenderBinDetails(renderDepth, "RenderBin", osg::StateSet::PROTECTED_RENDERBIN_DETAILS);

		point->setPointSmooth(true);
		point->setColor(color);
		point->finish();
	}

	void ClusterTextPointNode::update()
	{
		_updateHandler->execute();
	}
}