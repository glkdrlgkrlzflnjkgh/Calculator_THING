// Config.h
#pragma once // Gaurd to idiot-proof this header file.
/* 
Enable debug mode if _DEBUG is defined,
typically in debug builds in visual studio  2022
(and many other IDEs/compilers!) 
*/
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__
#ifdef _DEBUG // are we in a debug build?
#define DEBUG  // if so, define DEBUG for our code
#define VERSION "1.0.5-Debug" // Debug version string
#else
#define VERSION "1.0.5-Release" // Release version string
#endif 