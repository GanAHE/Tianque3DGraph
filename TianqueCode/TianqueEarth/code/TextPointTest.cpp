
#include "TextPointTest.h"
#include "ClusterTextPointNode.h"

#include<osgGA/GUIEventHandler>

namespace GanAHE {

	class TextPointTest::KeyboardHandler :public osgGA::GUIEventHandler//人机交互事件处理器
	{

	public:
		//重构父类GUIEventHandler.handle，事件处理函数，自定义交互操作，
		//参数1:当前传入此处理器的事件，只可以被获取，不能被修改
		//参数2：反馈动作，动作适配器，可以获取也可以修改的参数，大部分时候这个传入值表示当前所用的视图对象View，可以用它来获取
		//        或控制视景器的状态变化。如：osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		//参数3：对象指针obj，保存该处理器的对象，可能是当前事件回调所在的Node节点指针，也可能是Drawable指针
		//参数4：传递该事件的访问器（EventVisitor），nv通常为当前时间访问器指针。
		virtual bool handle(const osgGA::GUIEventAdapter& ea,
			osgGA::GUIActionAdapter& aa,
			osg::Object* obj, osg::NodeVisitor* nv)
		{
			osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			if (!viewer)return false;

			switch (ea.getEventType())//判断事件，做出响应
			{
			case osgGA::GUIEventAdapter::KEYDOWN://ea.getEventType()获取到的如果是键盘事件
				if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)//空格，控制鼠标到屏幕中间
				{
					int width = ea.getWindowWidth();
					int heigth = ea.getWindowHeight();
					viewer->requestWarpPointer(width * 0.5, heigth * 0.5);
				}
				else
				{
					std::cout << "================= KeyBoard Click: " << ea.getKey() << std::endl;
					osg::Switch* root = dynamic_cast<osg::Switch*>(viewer->getSceneData());
					if (!root) return false;
					//按下1为第一个不着火的飞机，2，着火飞机，3，牛
					if (ea.getKey() == '51')
					{

					}
					else if (ea.getKey() == '52')
					{
						
					}
					else if (ea.getKey() == '3')
					{

					}
					return true;
				}
				break;
			default:break;
			}
			return false;
		}

	};

	TextPointTest::TextPointTest(osgViewer::Viewer* viewer)
	{
		viewer->addEventHandler(new TextPointTest::KeyboardHandler());
	}

	void TextPointTest::testDrawSimpleTextPoint(osgEarth::MapNode* mapNode) {
		//Point1
		{
			chcEarth::TextPointAttribute attribute(*(new osgEarth::GeoPoint(mapNode->getMapSRS(), 114.014, 30.256, 100)),"66");
			attribute.setPointSize(45);
			attribute.setBorderScale(0.2);
			std::string path = "font/Arial.ttf";
			attribute.setFontPath(path);
			chcEarth::TextPointNode* drawable = new chcEarth::TextPointNode(attribute);
			drawable->buildAll();
			mapNode->addChild(drawable);
		}
		
		//Point2
		{
			chcEarth::TextPointAttribute attribute2(*(new osgEarth::GeoPoint(mapNode->getMapSRS(), 114.114, 30.256, 100)));
			attribute2.setFillColor(osgEarth::Color::Green);
			attribute2.setText("102");
			chcEarth::TextPointNode* drawable2 = new chcEarth::TextPointNode(attribute2);
			drawable2->buildPoint();
			mapNode->addChild(drawable2);
		}

		//Point3
		{
			chcEarth::TextPointAttribute attribute3(*(new osgEarth::GeoPoint(mapNode->getMapSRS(), 114.214, 30.256, 100)));
			chcEarth::TextPointNode* drawable3 = new chcEarth::TextPointNode(attribute3);
			drawable3->getNodeAttribute().setFillColor(osgEarth::Color::Orange);
			drawable3->getNodeAttribute().setText("10s");
			drawable3->getNodeAttribute().setPointSize(35);
			drawable3->getNodeAttribute().setTextColor(osgEarth::Color::Orange);
			drawable3->buildText();
			mapNode->addChild(drawable3);
		}
		//more points
		{
			double lon = 114.314;
			double lat = 30.256;

			for (int i = 0; i < 2000; i++) {
				chcEarth::TextPointAttribute attributeMore(*(new osgEarth::GeoPoint(mapNode->getMapSRS(), lon+0.01*i, lat, 100)));
				chcEarth::TextPointNode* drawableMore = new chcEarth::TextPointNode(attributeMore);
				drawableMore->getNodeAttribute().setFillColor(osgEarth::Color::Orange);
				drawableMore->getNodeAttribute().setText(std::to_string(i));
				drawableMore->getNodeAttribute().setPointSize(35);
				drawableMore->getNodeAttribute().setBorderScale(0.2);
				drawableMore->getNodeAttribute().setTextColor(osgEarth::Color::White);
				drawableMore->buildAll();
				mapNode->addChild(drawableMore);
			}
		}
	}
	void TextPointTest::testDrawClusterPoint(osgEarth::MapNode* mapNode) {
		double lon = 114.114;
		double lat = 30.156;
		double step = 0.0;
		//Point group1
		{
			osgEarth::GeoPoint* pTemp = new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
				lon, lat, 100);
			chcEarth::TextPointAttribute textAttritube(*pTemp);
			textAttritube.setPointSize(25);
			textAttritube.setBorderScale(0.2);
			chcEarth::ClusterTextPointNode* clusterNode = new chcEarth::ClusterTextPointNode(textAttritube);
			for (int i = 0; i < 10000; i++) {
				step += 0.01;
				double innerLon = lon + step;
				double innerLat = lat;
				if (innerLon > 180) {
					innerLon -= 180;
					innerLat = lat - 1;
				}
				if (innerLon > 360) {
					innerLon -= 360;
					innerLat = lat - 2;
				}
				clusterNode->initPushPoint(*(new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
					innerLon, innerLat, 100)));
			}
			clusterNode->setLODMaxDist(3e7);
			clusterNode->build();
			mapNode->addChild(clusterNode);
		}
		//Point group2
		{
			osgEarth::GeoPoint* pTemp2 = new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
				lon, lat - 0.1, 100);
			chcEarth::TextPointAttribute textAttritube2(*pTemp2);
			textAttritube2.setPointSize(25);
			textAttritube2.setFillColor(osgEarth::Color::Red);
			chcEarth::ClusterTextPointNode* clusterNode2 = new chcEarth::ClusterTextPointNode(textAttritube2);
			step = 0.0;
			for (int i = 0; i < 10000; i++) {
				step += 0.01;
				clusterNode2->initPushPoint(*(new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
					lon + step, lat - 0.1, 100)));
			}
			clusterNode2->setLODMaxDist(5e6);
			clusterNode2->build();
			mapNode->addChild(clusterNode2);
		}
		
		//Point group3
		{
			osgEarth::GeoPoint* pTemp3 = new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
				lon, lat - 0.2, 100);
			chcEarth::TextPointAttribute textAttritube3(*pTemp3);
			textAttritube3.setPointSize(25);
			textAttritube3.setBorderScale(0.5);
			textAttritube3.setFillColor(osgEarth::Color::Green);
			_clusterNode = new chcEarth::ClusterTextPointNode(textAttritube3);
			step = 0.0;
			for (int i = 0; i < 5000; i++) {
				step += 0.01;
				_clusterNode->initPushPoint(*(new osgEarth::GeoPoint(mapNode->getMapSRS()->getGeographicSRS(),
					lon + step, lat - 0.2, 100)));
			}
			_clusterNode->build();
			mapNode->addChild(_clusterNode);
			//开启定时器用于刷新


		}
		
	}
}