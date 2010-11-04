#ifndef RLC_GAMESTATE_H
#define RLC_GAMESTATE_H
#pragma once

#include <string>
#include <boost/shared_ptr.hpp>

namespace rlc
{
	/** Interface for game states.
	*/
	class GameState
	{
	public:

		GameState( const std::string& state_name ) : m_name( state_name ){}

		virtual void begin() = 0; 
		virtual void update() = 0;
		virtual void render() = 0; // TODO : rendering should be orthogonal...move that elsewhere!
		virtual void end() = 0;
		
		const std::string& name() const { return m_name; }

	private:

		const std::string m_name;
	
	};

	typedef boost::shared_ptr< GameState > GameStatePtr;

}

#endif