#include "GC_ConsoleCmd_Help.h"

#include "GC_Console.h"

namespace gcore
{

	const std::string ConsoleCmd_Help::HELP_COMMAND_NAME = "help";
	const std::string ConsoleCmd_Help::DEFAULT_HELP_TEXT = "Print the help text of all the registered commands or the command as second parametter.";


	ConsoleCmd_Help::ConsoleCmd_Help( const std::string& helpText )
		: ConsoleCommand( HELP_COMMAND_NAME )
		, m_helpText( helpText )
	{
	}

	bool ConsoleCmd_Help::execute( Console & console , const std::vector< std::string >& parameterList )
	{
		std::stringstream helpText;

		if( parameterList.empty() )
		{
			// print all the command's help texts

			for( Console::CommandIndex::iterator it = console.m_commandIndex.begin(); it != console.m_commandIndex.end(); ++it )
			{
				const ConsoleCommandPtr command = it->second;
				GC_ASSERT_NOT_NULL( command );

				printCommandHelp( helpText, console.commandCallPrefix(), command );
			}

		}
		else
		{
			// take the first parameter as the command name we want to print the help text of
			const ConsoleCommandPtr command = console.command( parameterList[0] );

			if( command )
			{
				// command found!
				printCommandHelp( helpText, console.commandCallPrefix(), command );
			}
			else
			{
				// command not found!
				helpText << "Command not found : " <<  parameterList[0];
			}
		}

		console.printText( helpText.str() );

		return false;
	}


	void ConsoleCmd_Help::printCommandHelp( std::stringstream& output, const std::string& commandPrefix, const ConsoleCommandPtr& command )
	{
		output << commandPrefix << command->name() << "\t : \t" << command->help() << "\n\n";
	}
}