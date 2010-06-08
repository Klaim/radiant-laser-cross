#ifndef RLC_GAMESTATE_H
#define RLC_GAMESTATE_H
#pragma once

#include <string>
#include <boost/shared_ptr.hpp>

namespace rlc
{
	/** No documentation yet.
	*/
	class GameState
	{
	public:

		GameState( const std::string& state_name ) : m_name( state_name ){}

		virtual void begin() = 0; 
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void end() = 0;
		
		const std::string& name() const { return m_name; }

	private:

		const std::string m_name;
	
	};

	typedef boost::shared_ptr< GameState > GameStatePtr;

}

#endif