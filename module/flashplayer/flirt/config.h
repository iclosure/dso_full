
// These are determined in Makefiles now:

//#define DD_PLATFORM_MAC_OS_X
//#define DD_PLATFORM_CYGWIN
//#define DD_PLATFORM_LINUX
//#define DD_PLATFORM_SYMBIAN

//#define DD_BIG_ENDIAN
//#define DD_LITTLE_ENDIAN

// render top-down, so we can ignore geometry that's obscured
#define DD_RENDER_TOPDOWN

// choose the correct sample order for your platform
#define DD_COLOR_SAMPLE_RGBA
//#define DD_COLOR_SAMPLE_ARGB

// comment out if these are missing on your system
#define HAVE_ZLIB
#define HAVE_JPEGLIB
#define HAVE_MAD

// enable debugging/logging features
//#define DD_DEBUG
//#define DD_LOG

// include functions to allow poking at the runtime
#define DD_INCLUDE_DEBUGGER


#if defined(WIN32)
// Visual Studio C 6++ ->
#pragma warning( disable : 4244 )  // Disable warning messages in simulation
#pragma warning( disable : 4761 )  // Disable warning "integral size mismatch in argument; conversion supplied"
#pragma warning( disable : 4305)   // truncation from 'const double ' to 'float '
#pragma warning( disable : 4049)   // compiler limit : terminating line number emission
// Visual Studio 2008 ->
#pragma warning( disable : 4996)   // 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#endif 