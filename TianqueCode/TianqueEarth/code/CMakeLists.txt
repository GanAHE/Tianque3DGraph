# CMakeList.txt: osgEarthDemo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


SET(HEAD_FILES 
    "OsgTextPointStyle.h"
    "TextPointNode.h"
     "ClusterTextPointNode.h"
      
     "UpdateQueue.h"
     "TextPointAttribute.h" 
     "TextPointTest.h"  "logger.h")

SET(SOURCES_FILE
    "Main.cpp"
    "OsgTextPointStyle.cpp"
    "TextPointNode.cpp"
     "ClusterTextPointNode.cpp"
       
     "UpdateQueue.cpp" 
     "TextPointAttribute.cpp" 
     "TextPointTest.cpp" )

# 将源代码添加到此项目的可执行文件。
add_executable (osgEarthDemo ${SOURCES_FILE} ${HEAD_FILES})

#库头文件
include_directories(
   ${PROJECT_SOURCE_DIR}/libs/osgEarth_x64/include
   ${PROJECT_SOURCE_DIR}/libs/thirdParty_x64/include
)

SET(OSGEARTHPATH ${PROJECT_SOURCE_DIR}/libs/osgEarth_x64/lib)
SET(OSGEarth 
    optimized ${OSGEARTHPATH}/osgDB.lib
	  optimized ${OSGEARTHPATH}/osgViewer.lib
    optimized ${OSGEARTHPATH}/OpenThreads.lib
    optimized ${OSGEARTHPATH}/osg.lib
    optimized ${OSGEARTHPATH}/osgManipulator.lib
    optimized ${OSGEARTHPATH}/osgUtil.lib
    optimized ${OSGEARTHPATH}/osgGA.lib
    optimized ${OSGEARTHPATH}/osgAnimation.lib
    optimized ${OSGEARTHPATH}/osgSim.lib
    optimized ${OSGEARTHPATH}/osgFX.lib
    optimized ${OSGEARTHPATH}/osgText.lib
    optimized ${OSGEARTHPATH}/osgShadow.lib
    optimized ${OSGEARTHPATH}/osgParticle.lib
    optimized ${OSGEARTHPATH}/osgPresentation.lib
    optimized ${OSGEARTHPATH}/osgTerrain.lib
    optimized ${OSGEARTHPATH}/osgUI.lib
    optimized ${OSGEARTHPATH}/osgVolume.lib
    optimized ${OSGEARTHPATH}/osgWidget.lib 

    optimized ${OSGEARTHPATH}/osgEarth.lib
    optimized ${OSGEARTHPATH}/osgEarthrd.lib
    optimized ${OSGEARTHPATH}/osgEarthAnnotation.lib
    optimized ${OSGEARTHPATH}/osgEarthUtil.lib
    optimized ${OSGEARTHPATH}/osgEarthSplat.lib
    optimized ${OSGEARTHPATH}/osgEarthFeatures.lib
    optimized ${OSGEARTHPATH}/osgEarthSymbology.lib 
)

SET(THIRDPARTYPATH ${PROJECT_SOURCE_DIR}/libs/thirdParty_x64/lib)
SET(THIRD_PARTY
    optimized ${THIRDPARTYPATH}/gdal.lib 
    optimized ${THIRDPARTYPATH}/gdal_i.lib
    optimized ${THIRDPARTYPATH}/geos.lib 
    optimized ${THIRDPARTYPATH}/geos_i.lib 
    optimized ${THIRDPARTYPATH}/geotiff_i.lib 
    optimized ${THIRDPARTYPATH}/giflib_5.1.4_x64.lib 
    optimized ${THIRDPARTYPATH}/iconv.lib 
    optimized ${THIRDPARTYPATH}/jpeg.lib 
    optimized ${THIRDPARTYPATH}/jpeg-static.lib 
    optimized ${THIRDPARTYPATH}/leveldb.lib
    optimized ${THIRDPARTYPATH}/libcurl.lib 
    optimized ${THIRDPARTYPATH}/libeay32.lib 
    optimized ${THIRDPARTYPATH}/libpng16.lib 
    optimized ${THIRDPARTYPATH}/libtiff_i.lib 
    optimized ${THIRDPARTYPATH}/NCSEcw.lib 
    optimized ${THIRDPARTYPATH}/sqlite3.lib 
    optimized ${THIRDPARTYPATH}/zlibwapi.lib 
    optimized ${THIRDPARTYPATH}/proj_i.lib 
    #NCSEcwS库会导致CircleNode类使用出现冲突
    #optimized ${THIRDPARTYPATH}/NCSEcwS.lib 
    #optimized ${THIRDPARTYPATH}/NCSEcwS_MT.lib 
    optimized ${THIRDPARTYPATH}/ssleay32.lib
    optimized ${THIRDPARTYPATH}/xerces-c_2.lib
    optimized ${THIRDPARTYPATH}/turbojpeg-static.lib
    optimized ${THIRDPARTYPATH}/ssleay32.lib

   )
target_link_libraries(osgEarthDemo ${OSGEarth} ${THIRD_PARTY})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET osgEarthDemo PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/execute/x64_Release")
#bin
#设置变量
set(SDK_DLL_DIR 
    "${PROJECT_SOURCE_DIR}/libs/thirdParty_x64/bin/"
    "${PROJECT_SOURCE_DIR}/libs/osgEarth_x64/bin/"
    )
# 设置输出目录,后续应支持Release/Debug分离
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/lib/")  
 
# 拷贝文件到exe所在的目录
# 1 拷贝文件夹里的文件
file(COPY ${SDK_DLL_DIR}/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})
# 2 拷贝bin文件
file(COPY ${SDK_DLL_DIR} DESTINATION ${EXECUTABLE_OUTPUT_PATH})