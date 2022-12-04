#pragma once
#ifndef CLUSTER_TEXT_POINT_NODE_H
#define CLUSTER_TEXT_POINT_NODE_H

#include <osg/Switch>
#include <osgEarth/GeoData>
#include <osgEarth/PointDrawable>
#include "TextPointNode.h"
#include "UpdateQueue.h"

namespace chcEarth {
	class ClusterTextPointNode : public osg::Switch
	{
		class UpdateCallBack;
		friend class UpdateCallBack;

	public:
		ClusterTextPointNode(const TextPointAttribute& attritube);
		const void setLODMinDist(float minDist);
		const void setLODMaxDist(float maxDist);
		/*initial the data*/
		const void initPushPoint(osgEarth::GeoPoint& position);
		const void build();
		/*runtime add point slowly*/
		const void addPoint(osgEarth::GeoPoint& position);
		const void clear();
		const void setVisibility(bool visible);
		~ClusterTextPointNode();

	public:
		const float getLODMinDist();
		const float getLODMaxDist();
	private:
		std::mutex _Lock;
		TextPointAttribute _attritbute;
		float _LODMinDist = 1E-2;
		float _LODMaxDist = 3E6;
		osg::ref_ptr<osg::LOD> _LOD;
		osg::ref_ptr<osgEarth::PointDrawable> _centerPointNode;
		osg::ref_ptr<osgEarth::PointDrawable> _borderPointNode;
		UpdateQueue* _updateHandler;

	private:
		void init();
		void initPointStyle(osg::ref_ptr<osgEarth::PointDrawable> point, const osgEarth::Color color, float size, int renderDepth);
		void update();

	};
}
#endif // !CLUSTER_TEXT_POINT_NODE_H

