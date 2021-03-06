#ifndef GC_CROSSPLATFORM_H
#define GC_CROSSPLATFORM_H
#pragma once

/*
	Cross-platform definitions.
*/

// Target platforms :
#define GC_PLATFORM_WIN32	1		///< Win32 Architecture (Windows98, WindowsXP, Vista)
#define GC_PLATFORM_MACOSX	2		///< Apple OS (OSX)
#define	GC_PLATFORM_LINUX	3		///< Linux based OS (various, Ubuntu and Fedora as first target?)

// Find wich platform it is.
#if defined( WIN32 ) || defined( _WIN32 )	

	/// We are on Win32 operating system (windows98, windowsXP, Vista).
	#define GC_PLATFORM		GC_PLATFORM_WIN32

#elif defined( __APPLE_CC__)

	/// We are on an APPLE operating system (MacOSX)
	#define GC_PLATFORM		GC_PLATFORM_MACOSX

#else 
	
	/// We are on a LINUX based operating system.
	#define GC_PLATFORM		GC_PLATFORM_LINUX

#endif

// Target os architectures
#define GC_OS_ARCHITECTURE_32		///< 32bit Architecture Operating System
#define GC_OS_ARCHITECTURE_64		///< 64bit Architecture Operating System

// Find wich architecture it is
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
	
	/// We are on a 64bit Architecture Operating System 
	#define GC_OS_ARCHITECTURE	GC_OS_ARCHITECTURE_64	

#else
	
	/// We are on a 32bit Architecture Operating System
	#define GC_OS_ARCHITECTURE	GC_OS_ARCHITECTURE_32

#endif


#if GC_PLATFORM == GC_PLATFORM_WIN32 //windows specific
	
	///Specific Win32 DLL Import macro :
	#define GC_DllImport   __declspec( dllimport )
	///Specific Win32 DLL Export macro :
	#define GC_DllExport   __declspec( dllexport )

#else

	//Non-Windows specifics.

	///Specific Win32 DLL Import macro :
	#define DllImport 
	///Specific Win32 DLL Export macro :
	#define DllExport 

#endif




/************************************/
// C++0x features emulation
/*#if __cplusplus <= 199711L // <= C++03
	
	typedef wchar_t				char16_t;	///< UTF-16 encoded character.
	typedef unsigned int		char32_t;	///< UTF-32 encoded character.
	
	//nullptr definition: (see C++0x)
	// from http://stackoverflow.com/questions/2419800/can-nullptr-be-emulated-in-gcc
	const                        // this is a const object...
	class {
	public:
		template<class T>          // convertible to any type
		operator T*() const      // of null non-member
		{ return 0; }            // pointer...
		template<class C, class T> // or any type of null
		operator T C::*() const  // member pointer...
		{ return 0; }
	private:
		void operator&() const;    // whose address can't be taken
	} nullptr = {};              // and whose name is nullptr

#endif*/

#endif