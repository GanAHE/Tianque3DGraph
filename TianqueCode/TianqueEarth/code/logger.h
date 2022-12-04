/*********************************************************************
* Copyright (c) 2018, CHC Technology Co., Ltd., All rights reserved
* filename: logger.h
* created:  2018-12-06  16:58
* author:   Jeffrey
* version:  1.0
* purpose:  
*********************************************************************/
#pragma once
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <time.h>

namespace utils {

enum LogLevel
{
    LL_Verbose,
    LL_Debug,
    LL_Info,
    LL_Error
};

LogLevel getLogLevel();
void setLogLevel(LogLevel level);

#ifdef _WINDOWS
extern void __DbgOutA(LogLevel level, const char* fmt, ...);
#else
#endif

}//utils

#ifdef _WINDOWS
#  define _DBGOUTA( lvl, x, ... )  utils::__DbgOutA( lvl, x ## "\n" , ##__VA_ARGS__ )
#else
#  define _DBGOUTA( lvl, x, ... )
#endif


/*
 * android/log.h:__android_log_print函数签名：int __android_log_print(int prio, const char *tag,  const char *fmt, ...)
 *Send a formatted string to the log, used like printf(fmt,...)
 */
#ifdef OS_ANDROID
#  include <android/log.h>
#  define __LOG(lvl,tag,...) __android_log_print(lvl, tag, ##__VA_ARGS__)

#  ifdef _DEBUG
#    define LOGD(TAG, FMT, ...) __LOG(ANDROID_LOG_DEBUG, TAG, "(%11.3lf): " #FMT, clock()*1.0/CLOCKS_PER_SEC, ##__VA_ARGS__)
#    define LOGHERE(s) LOGD("Debug","(%11.3lf):%s In %d line:%s", clock()*1.0/CLOCKS_PER_SEC, __FILE__,__LINE__, s);
#  else
#    define LOGD(TAG,...)
#    define LOGHERE(s)
#  endif//DEBUG

//如下LOGV，LOGI，LOGE，测试生效，比如LOGI("cpc__", "%s", mFilePath.c_str());，LOGI("cpc__", "count %d", 10);
#  define LOGV(TAG, FMT, ...) __LOG(ANDROID_LOG_VERBOSE, TAG, "(%11.3lf): " #FMT, clock() * 1.0 / CLOCKS_PER_SEC, ##__VA_ARGS__)
#  define LOGI(TAG, FMT, ...) __LOG(ANDROID_LOG_INFO, TAG, "(%11.3lf): " #FMT, clock() * 1.0 / CLOCKS_PER_SEC, ##__VA_ARGS__)
#  define LOGE(TAG, FMT, ...) __LOG(ANDROID_LOG_ERROR, TAG, "(%11.3lf): " #FMT, clock() * 1.0 / CLOCKS_PER_SEC, ##__VA_ARGS__)

#elif defined(_WINDOWS)

#  ifdef _DEBUG
#    define LOGD(TAG, FMT, ...) _DBGOUTA( utils::LogLevel::LL_Debug, "%s(%d) : %s : (%11.3lf)(DEBUG)"##TAG##" : "##FMT, __FILE__,__LINE__,__FUNCTION__, clock()*1.0/CLOCKS_PER_SEC, ##__VA_ARGS__ )
#    define LOGHERE(s)          _DBGOUTA( utils::LogLevel::LL_Debug, "%s(%d) : %s : (%11.3lf)", __FILE__,__LINE__,__FUNCTION__, clock()*1.0/CLOCKS_PER_SEC, s )
#  else //_DEBUG
#    define LOGD(TAG,...)
#    define LOGHERE(s)
#  endif//_DEBUG

#  define LOGE(TAG, FMT, ...) _DBGOUTA( utils::LogLevel::LL_Error,"%s(%d) : %s : (%11.3lf)(ERROR)"##TAG##" : "##FMT, __FILE__,__LINE__,__FUNCTION__, clock()*1.0/CLOCKS_PER_SEC, ##__VA_ARGS__ )
#  define LOGI(TAG, FMT, ...) _DBGOUTA( utils::LogLevel::LL_Info,"%s(%d) : %s : (%11.3lf)(VERBOSE)"##TAG##" : "##FMT, __FILE__,__LINE__,__FUNCTION__, clock()*1.0/CLOCKS_PER_SEC, ##__VA_ARGS__ )
#  define LOGV(TAG, FMT, ...) _DBGOUTA( utils::LogLevel::LL_Verbose,"%s(%d) : %s : (%11.3lf)(VERBOSE)"##TAG##" : "##FMT, __FILE__,__LINE__,__FUNCTION__, clock()*1.0/CLOCKS_PER_SEC, ##__VA_ARGS__ )

#else// _WINDOWS
#  define LOGD(TAG,...)
#  define LOGHERE(s)
#  define LOGE(TAG,...)
#  define LOGI(TAG,...)
#  define LOGV(TAG,...)
#endif

#endif//__LOGGER_H__

