/******************************************************************

	Inspired by Ogre::Log; www.ogre3D.org.

*******************************************************************/

#ifndef GCORE_LOG_H
#define GCORE_LOG_H
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "GC_Common.h"
#include <string>

namespace gcore
{

	class LogManager;
	class LogListener;


	/** TODO : rewrite this comment!
		The Log class act has a log file writer.
		Its instanced and used by using a LogManager.
		@par	
		When created a Log is binded to a file (the file name if the name of the log),
		and messages can be written at anytime into this file (messages are concatenated with a new line separation between them).
		@par
		In order to add a message into the binded file, the logMessage methods has to be called.
		When the logMessage method is called thought the logMessage of the LogManager that created this Log,
		The catchLogMessage method of every registered  LogListener of the LogManager is called.
		However, if the logMessage of a Log is called directly, the message is written directly into the file, and LogListener are not notified.
		@remark Managed by LogManager.
	*/
	class GCORE_API Log
	{
	public :

		/** Write a full message into the file binded to the Log.
			@param message The message to add into the file, each message is succeeded by a new line.
		**/
		void logMessage( const std::string& message );

		/** Write text in the current message without logging and adding a new line.
			@remark Use this function to add text to the message and call logText();
			to make the message be written in the log. It will not be written until 
			you call it.
			@param text Text to add.
			@see addText
			*/
		void addText( const std::string& text );

		/** Log the text that have been built with addText().
			@see addText
		*/
		void logText();


		/** The name of the log, which is also the name of the file the log writes into.
		**/
		const std::string& getName() const {return m_name;}

		void registerListener( LogListener* logListener );
		void unregisterListener( LogListener* logListener );

		class Streamer;
		
	private:

		/// Only LogManager should create Logs.
		friend class LogManager;

		/// Current message being written.
		std::stringstream m_message;

		/// The stream writing into the file.
		std::ofstream	m_fileStream;

		/// The name of the log, which is also the name of the file the log writes into.
		const std::string	m_name;

		/// LogManager that manage this Log.
		const LogManager& m_logManager;

		/// List of log listeners registered to listen this log
		std::vector< LogListener* >	m_registeredListeners;

		/** Create a log with the desired name.
			@param logManager Log manager that manage this Log.
			@param name The name of the Log, which is the name of the file in which the Log writes data.
			@param isNewFile True for erasing the log file if it already exists, else append the messages at the end of the existing file.
		**/
		Log( const LogManager& logManager,const std::string& name, bool isNewFile = true);

		/** The log destructor close the file in which data are written.
		**/
		~Log();
		
					
	};


	/** To allow streaming semantic on logs (used in << operator) .
	*/
	class LogStreamer
	{
	public:


		template< typename T >
		LogStreamer( Log& log, const T& text )
			: m_log( log )
		{
			std::stringstream stream;
			stream << text;
			m_log.addText( stream.str() );
		}

		template<>
		LogStreamer( Log& log, const std::string& text )
			: m_log( log )
		{
			m_log.addText( text );
		}


		~LogStreamer()
		{
			m_log.logText();
		}

		template< typename T >
		LogStreamer& operator<<( const T& text )
		{
			std::stringstream stream;
			stream << text;
			m_log.addText( stream.str() );
			return *this;
		}

		template<>
		LogStreamer& operator<<( const std::string& text )
		{
			m_log.addText( text );
			return *this;
		}
		
	private:

		Log& m_log;

	};

	template< typename T >
	inline LogStreamer operator<<( Log& log, const T& message )
	{
		return LogStreamer( log, message );
	}

}

#endif