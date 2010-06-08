#ifndef RLC_GAMEENTITY_H
#define RLC_GAMEENTITY_H
#pragma once

#include <boost/shared_ptr.hpp>

#include "sfml/System/Vector2.hpp"
#include "sfml/Graphics/Rect.hpp"
#include "sfml/Graphics/Shape.hpp"


#include "RLC_GameEntity.h"

namespace rlc
{
	typedef short PlanIdx;
	typedef sf::Vector2f Position;
	typedef float Orientation;
	typedef sf::FloatRect Box;

	/** No documentation yet.
	*/
	class GameEntity
	{
	public:

		GameEntity() : m_plan_idx(0), m_orientation(0.0f) {}

		void render() { do_render(); }
		void update() { do_update(); }

		PlanIdx plan_idx() const { return m_plan_idx; }

		Position position() const { return m_position; }
		void position( Position new_pos ) { m_position = new_pos; }

		Position center() const { return m_center; }
		void center( Position new_center ) { m_center = new_center; }
		
		Orientation orientation() const { return m_orientation; }
		void orientation( Orientation new_angle ) { m_orientation = new_angle; }

		Box box() const { return m_box; }
		void box( Box new_box ) { m_box = new_box; }


		sf::Shape shape();
		
	private:


		virtual void do_render() {};
		virtual void do_update() {};

		PlanIdx m_plan_idx;
	
		Box				m_box;
		Position		m_position;
		Position		m_center;
		Orientation		m_orientation;

	};

	

	
}

#endif