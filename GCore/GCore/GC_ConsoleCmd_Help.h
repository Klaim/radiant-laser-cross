#ifndef GC_CONSOLECMD_HELP_H
#define GC_CONSOLECMD_HELP_H
#pragma once

#include <sstream>

#include "GC_Common.h"

#include "GC_ConsoleCommand.h"

namespace gcore
{
	/** Print help texts from all registered commands of a console.
	*/
	class GCORE_API ConsoleCmd_Help
		: public ConsoleCommand
	{
	public:

		static const std::string HELP_COMMAND_NAME;
		static const std::string DEFAULT_HELP_TEXT;

		ConsoleCmd_Help( const std::string& helpText = DEFAULT_HELP_TEXT );
		~ConsoleCmd_Help(){}

		
	protected:
		
	private:

		bool execute( Console & console , const std::vector< std::string >& parameterList);

		std::string help() const { return m_helpText; }

		void printCommandHelp( std::stringstream& output, const std::string& commandPrefix, const ConsoleCommandPtr& command );

		const std::string m_helpText;

	};
	

}

#endif