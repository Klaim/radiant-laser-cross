#ifndef GCORE_EXCEPTION_H
#define GCORE_EXCEPTION_H
#pragma once

#include <exception>
#include <string>

#if (GC_PLATFORM != GC_PLATFORM_WIN32) || (_MSC_VER < 1600) // < vc10
#include <boost/static_assert.hpp>
#define static_assert( expr ) BOOST_STATIC_ASSERT( expr )
#endif

#include "GC_CrossPlatform.h"

#include <sstream>

namespace gcore
{


	/** 
	*	GCore exception base class.
	*/
	class Exception : public std::exception
	{
	public:

		/// Description of the error in standard exception compatible mode. @see getMessage()
		const char* what() const
		{
			return m_message.c_str();
		}

		///Name of the file where the exception occurred
		const std::string& file() const {return m_file;}

		///Name of the function where the exception occurred 
		const std::string& function() const {return m_function;}

		///Description of the error/exception and informations.
		const std::string& message() const {return m_message;}

		///Number of the file in the file where the exception occurred
		long line() const {return m_line;}

		///Error identifier code - deprecated
		long code() const {return m_code;}
		
		/// Allow stream semantic for message addition
		template< class T >
		Exception& operator<<( T text )
		{
			std::stringstream stream;
			stream << m_message;
			stream << text;
			m_message = stream.str();
			return *this;
		}
		
		/** Exception constructor.
			@param code		Error code. 
			@param file		Source file name where the error occurred.
			@param function	Function or method name where the exception occurred.
			@param line		Line number in the file where the exception occurred. 
			@param msg		Description of the error and other informations.
		*/
		Exception( long code, const std::string& function ,  const std::string& file , long line, const std::string& message = std::string()  )	//Constructor
			: m_message(message)
			, m_function(function)
			, m_file(file)
			, m_line(line)
			, m_code(code)
		{

		}

		~Exception(){}

	private:

		std::string	m_file;
		unsigned long m_line;
		std::string	m_function;
		std::string	m_message;
		long m_code;	
	};




	/** 
		GCore assert exception class.
		Thrown on failed assertion.
		Error code : -1
	*/
	class AssertionException:public Exception
	{
	public:
		/** Assertion exception.
			@param file		Source file name where the error occurred.
			@param function	Function or method name where the exception occurred.
			@param line		Line number in the file where the exception occurred. 
		*/
		explicit AssertionException( const std::string& testExpression , const std::string& function ,  const std::string& file , long line, const std::string& msg = std::string() )
			: Exception( -1 , function , file , line, std::string("/!\\ Assertion failed! : \n Test Expression : ") + testExpression  + "\n Description :\n"  )
			, m_testExpression( testExpression )
		{  }

		/** Expression used to test the assertion.
		*/
		const std::string& getTestExpression() const { return m_testExpression; }

	private:

		/// Expression used to test the assertion.
		std::string		m_testExpression;

	};

#ifdef GC_DEBUG
	/// Hardware breakpoint (should be portable between 64bit and 32bit versions, certainly not with other compiler than vc)
	struct DebugBreak
	{
		bool operator()()
		{
			m_message;
			::__debugbreak(); // debug mode : look at the message value!
			return true;
		}

		/// Allow stream semantic for message addition
		template< class T >
		DebugBreak& operator<<( T text )
		{
			std::stringstream stream;
			stream << m_message;
			stream << text;
			m_message = stream.str();
			return *this;
		}

		std::string m_message;
		
	};
#endif

}




/// @copydoc DebugBreak
#ifdef GC_DEBUG
	#define GC_BREAKPOINT( message ) ((gcore::DebugBreak() << message)()) // create the debug break, stream the message in, call the final debug break (to get the message)
#else
	#define GC_BREAKPOINT( message )
#endif

/// Throw a general gcore::Exception. Use it as a critical error. Use like this : GC_EXCEPTION << "This is " << 1 << "message" ;
#define GC_EXCEPTION throw gcore::Exception( 0, __FUNCTION__ , __FILE__ , __LINE__ )

/// Useful to remind implementer to add missing code once used.
#ifdef GC_DEBUG
	#define GC_NOT_IMPLEMENTED_YET GC_BREAKPOINT( "Not implemented yet : DO IT NOW!!!" )
#else
	#define GC_NOT_IMPLEMENTED_YET throw gcore::Exception(  0, __FUNCTION__ , __FILE__ , __LINE__ ) << "Not implemented yet : DO IT NOW!!!"
#endif
/// Useful in template code that should not be instantiated, forcing user to define or use specific implementations.
#define GC_FORCE_IMPLEMENTATION static_assert( false )

/// GCore assert macro that throw a gcore::AssertException on failure in debug mode.Use like this : GC_ASSERT( a.isGood(), "Object" << a.name() << " is not good!" << 42 );
#ifdef GC_DEBUG
	#define GC_ASSERT( assert_test , assert_msg ) \
		if( !(assert_test) && GC_BREAKPOINT(assert_msg) ) \
			(throw gcore::AssertionException( #assert_test , __FUNCTION__ , __FILE__ , __LINE__ ) << assert_msg )
#else
	#define GC_ASSERT(test , msg)
#endif

/* GC_ASSERT_OR usage:
	GC_ASSERT_OR( a > b, "A > B!!" )
	{
		// here the code executed on assert in non-debug mode
	}
*/
#ifdef GC_DEBUG
	#define GC_ASSERT_OR( assert_test , assert_msg ) GC_ASSERT( assert_test, assert_msg ); if(false)
#else
	#define GC_ASSERT_OR( assert_test , assert_msg ) if( !(assert_test)  ) 
#endif

#ifdef GC_DEBUG
	#define GC_ASSERT_RETURN( assert_test, assert_msg ) GC_ASSERT( assert_test, assert_msg )
	#define GC_ASSERT_RETURN_VALUE( assert_test, assert_msg, return_value ) GC_ASSERT( assert_test, assert_msg )
#else
	#define GC_ASSERT_RETURN( assert_test, assert_msg ) if( !(assert_test)  ) return;
	#define GC_ASSERT_RETURN_VALUE( assert_test, assert_msg, return_value ) if( !(assert_test)  ) return return_value;
#endif

#ifdef GC_DEBUG
	#define GC_ASSERT_EXCEPT( assert_test , assert_msg ) GC_ASSERT( assert_test, assert_msg )
#else
	#define GC_ASSERT_EXCEPT( assert_test , assert_msg ) GC_EXCEPTION << assert_msg
#endif


#define GC_ASSERT_NOT_NULL( expr ) GC_ASSERT( (expr) , "Assertion failed! " #expr " is null!" );
#define GC_ASSERT_NULL( expr ) GC_ASSERT( !(expr) , "Assertion failed! " #expr " is not null!" );

#define GC_ASSERT_NOT_NULL_OR( expr ) GC_ASSERT_OR( (expr) , "Assertion failed! " #expr " is null!" )
#define GC_ASSERT_NULL_OR( expr ) GC_ASSERT_OR( !(expr) , "Assertion failed! " #expr " is not null!" )

#define GC_ASSERT_NOT_NULL_RETURN( expr ) GC_ASSERT_RETURN( (expr) , "Assertion failed! " #expr " is null!" )
#define GC_ASSERT_NULL_RETURN( expr ) GC_ASSERT_RETURN( !(expr) "Assertion failed! " #expr " is not null!" )

#define GC_ASSERT_NOT_NULL_RETURN_VALUE( expr, return_value ) GC_ASSERT_RETURN_VALUE( (expr) , "Assertion failed! " #expr " is null!", return_value )
#define GC_ASSERT_NULL_RETURN_VALUE( expr, return_value ) GC_ASSERT_RETURN_VALUE( !(expr) , "Assertion failed! " #expr " is not null!", return_value )


#endif