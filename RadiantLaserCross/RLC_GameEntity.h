#ifndef RLC_GAMEENTITY_H
#define RLC_GAMEENTITY_H
#pragma once


#include "RLC_Geometry.h"
#include "RLC_GameEntityGroup.h"

#include "sfml/Graphics/Shape.hpp"

#include <string>
#include <boost/shared_ptr.hpp>



namespace rlc
{
	

	/** No documentation yet.
	*/
	class GameEntity
		: public GameEntityGroup
	{
	public:

		GameEntity() : m_plan_idx(0), m_orientation(0.0f) {}

		void render() { do_render(); render_children(); }
		void update() { do_update(); update_children(); }

		PlanIdx plan_idx() const { return m_plan_idx; }

		Position position() const { return m_position; }
		void position( Position new_pos );

		Position center() const { return m_center; }
		void center( Position new_center ) { m_center = new_center; }
		
		Orientation orientation() const { return m_orientation; }
		void orientation( Orientation new_angle ) { m_orientation = new_angle; }

		Box core() const { return m_core; }
		void core( Box new_box ) { m_core = new_box; }

		sf::Shape core_shape();

		const std::string& name() { return m_name; }
		void name( const std::string& new_name ){ m_name = new_name; }
						
	private:

		std::string m_name;

		virtual void do_render() {};
		virtual void do_update() {};

		PlanIdx m_plan_idx;
	
		Box				m_core;
		Position		m_position;
		Position		m_center;
		Orientation		m_orientation;

		std::vector< GameEntity* > m_children;

	};

	bool in_screen( const GameEntity& entity );

	
}

#endif