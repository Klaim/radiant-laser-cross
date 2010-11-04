#ifndef RLC_PLAYER_H
#define RLC_PLAYER_H
#pragma once

#include "RLC_PlayerShip.h"

namespace rlc
{
	typedef unsigned long PlayerScore;
	typedef unsigned short PlayerLife;

	/** Player's state informations.
	*/
	class Player
	{
	public:



		PlayerScore score() const { return m_score; }
		PlayerLife life() const { return m_life; }
		
		PlayerShip& ship() { return m_ship; }
		
	private:

		PlayerShip m_ship;

		PlayerScore m_score;
		PlayerLife m_life;
	
	};
	
}

#endif