#ifndef RLC_GAMEENTITY_H
#define RLC_GAMEENTITY_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "sfml/System/Vector2.hpp"

#include "RLC_GameEntity.h"

namespace rlc
{
	typedef short PlanIdx;
	typedef sf::Vector2f Position;

	/** No documentation yet.
	*/
	class GameEntity
	{
	public:

		GameEntity() : m_plan_idx(0) {}

		virtual void render() = 0;
		virtual void update() = 0;

		PlanIdx plan_idx() const { return m_plan_idx; }

		Position position() const { return m_position; }
		void position( const Position& new_pos ) { m_position = new_pos; }
		
	private:

		PlanIdx m_plan_idx;
	
		Position m_position;

	};

	

	
}

#endif