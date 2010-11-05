#include "RLC_PlayerShip.h"

#include <cmath>
#include <boost/make_shared.hpp>

#include "sfml/Graphics/Shape.hpp"
#include "sfml/Graphics/Rect.hpp"
#include "sfml/Graphics/Color.hpp"
#include "sfml/Graphics/RenderWindow.hpp"

#include "RLC_Game.h"
#include "RLC_GameConfig.h"
#include "RLC_BulletType.h"
#include "RLC_GunType.h"

namespace rlc
{
	namespace config
	{
		const float SHIP_WIDTH = 32.0f;
		const float SHIP_HEIGHT = 32.0f;
		
		const float GUN_DISTANCE = 26.0f;
		const float GUN_WIDTH = 20.0f;
		const float GUN_HEIGHT = 16.0f;

		const float GUN_ANGLE_INTERVAL = 360.0f / float(MAX_PLAYER_GUNS);
		const float GUN_FIRE_BORDER_ANGLE = (GUN_ANGLE_INTERVAL / 2.0f);

		const float GUN_ROTATION_SPEED = 5.0f;

		const float FULL_SHIP_WIDTH = SHIP_WIDTH + SHIP_HEIGHT;

		const float SQUARE_ANGLE = 90.0f;
		const float UP_ANGLE = SQUARE_ANGLE * 4.0f;
		const float LEFT_ANGLE = SQUARE_ANGLE * 3.0f;
		const float DOWN_ANGLE = SQUARE_ANGLE * 2.0f;
		const float RIGHT_ANGLE = SQUARE_ANGLE;

	}

	using namespace config;

	namespace test
	{
		class BulletType : public rlc::BulletType
		{
		public:

			BulletType( sf::Color b_color ) : m_bullet_color( b_color ) {}

			sf::Shape bullet_shape() const 
			{
				return sf::Shape::Circle( 0.0f, 0.0f, 4.0f, m_bullet_color );
			}

			float bullet_speed() const { return 20.0f; }
			sf::Color bullet_color() const { return m_bullet_color; }

			void bullet_behavior( Bullet& bullet ) const {  }

		private:

			sf::Color m_bullet_color;

		};

		class GunType : public rlc::GunType
		{
		public:

			GunType( BulletTypePtr bt ) : m_bullet_type( bt ) { GC_ASSERT_NOT_NULL(m_bullet_type);  }

			BulletTypePtr bullet_type() const { return m_bullet_type;}
			float fire_rate() const { return 5.0f; }

		private:

			BulletTypePtr m_bullet_type;

		};
	}
	

	PlayerShip::PlayerShip()
		: m_guns_orientation( 0.0f )
		, m_guns_setup( GunsSetup_East )

	{
		core( Box(-4,-4,4,4) );
		
		BulletTypePtr test_bullet_type_0 = boost::make_shared<test::BulletType>( gun_color(0) );
		BulletTypePtr test_bullet_type_1 = boost::make_shared<test::BulletType>( gun_color(1) );
		BulletTypePtr test_bullet_type_2 = boost::make_shared<test::BulletType>( gun_color(2) );
		BulletTypePtr test_bullet_type_3 = boost::make_shared<test::BulletType>( gun_color(3) );

		GunTypePtr test_gun_type_0 = boost::make_shared<test::GunType>( test_bullet_type_0 );
		GunTypePtr test_gun_type_1 = boost::make_shared<test::GunType>( test_bullet_type_1 );
		GunTypePtr test_gun_type_2 = boost::make_shared<test::GunType>( test_bullet_type_2 );
		GunTypePtr test_gun_type_3 = boost::make_shared<test::GunType>( test_bullet_type_3 );

		set_gun( boost::make_shared<Gun>( test_gun_type_0 ), 0 );
		set_gun( boost::make_shared<Gun>( test_gun_type_1 ), 1 );
		set_gun( boost::make_shared<Gun>( test_gun_type_2 ), 2 );
		set_gun( boost::make_shared<Gun>( test_gun_type_3 ), 3 );

		get_gun(0)->name( "Gun_A" );
		get_gun(1)->name( "Gun_B" );
		get_gun(2)->name( "Gun_C" );
		get_gun(3)->name( "Gun_D" );


		get_gun(0)->cannon( Position( GUN_DISTANCE + GUN_WIDTH, 0.0f ) );
		get_gun(1)->cannon( Position( GUN_DISTANCE + GUN_WIDTH, 0.0f ) );
		get_gun(2)->cannon( Position( GUN_DISTANCE + GUN_WIDTH, 0.0f ) );
		get_gun(3)->cannon( Position( GUN_DISTANCE + GUN_WIDTH, 0.0f ) );

		get_gun(0)->direction( Vector2( 1.0f, 0.0f ) );
		get_gun(1)->direction( Vector2( 0.0f, -1.0f ) );
		get_gun(2)->direction( Vector2( -1.0f, 0.0f ) );
		get_gun(3)->direction( Vector2( 0.0f, 1.0f ) );

		using namespace config;

		position( Position( SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f ) ) ;
		rotate_guns( 1 );
	}

	void PlayerShip::do_update()
	{
		update_move();
		update_guns();
	}

	
	inline bool in_circle_angle( const float& val, const float& target_angle, const float& tolerance )
	{
		if( val < 0.0f ) return false;

		const float min_angle = target_angle - tolerance;
		const float max_angle = target_angle + tolerance;
		return (( val >= min_angle )
			&& ( val <= max_angle )
			)
			|| ( target_angle >= UP_ANGLE && val <= tolerance )
			;
	}
	
	void PlayerShip::update_move()
	{
		using namespace sf;
		const Input& input = Game::instance().display().GetInput();

		Position move;
		Position position = this->position();
		
		static const float MOVE_JOYSTICK_TOLERANCE = 33.0f;
		static const float FIRE_JOYSTICK_TOLERANCE = 66.0f;
		static const float POV_ANGLE_TOLERANCE = 55.0f;

		
		const float pov_angle = input.GetJoystickAxis( 0, sf::Joy::AxisPOV );


		if( input.IsKeyDown( Key::Left ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_MOVE_LEFT ) ) 
		||	input.GetJoystickAxis( 0, sf::Joy::AxisX ) < -MOVE_JOYSTICK_TOLERANCE 
		||	in_circle_angle( pov_angle, LEFT_ANGLE, POV_ANGLE_TOLERANCE )
		)
		{
			if( position.x > FULL_SHIP_WIDTH/2 )
				move.x -= 1;
		}

		if( input.IsKeyDown( Key::Right ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_MOVE_RIGHT ) ) 
		||	input.GetJoystickAxis( 0, sf::Joy::AxisX ) > MOVE_JOYSTICK_TOLERANCE 
		||	in_circle_angle( pov_angle, RIGHT_ANGLE, POV_ANGLE_TOLERANCE )
		)
		{
			if( position.x < ( SCREEN_WIDTH - (FULL_SHIP_WIDTH/2) ) ) 
				move.x += 1;
		}

		if( input.IsKeyDown( Key::Up ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_MOVE_UP ) ) 
		||	input.GetJoystickAxis( 0, sf::Joy::AxisY ) < -MOVE_JOYSTICK_TOLERANCE 
		||	in_circle_angle( pov_angle, UP_ANGLE, POV_ANGLE_TOLERANCE ) 
		)
		{
			if( position.y > FULL_SHIP_WIDTH/2 )
				move.y -= 1;
		}

		if( input.IsKeyDown( Key::Down ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_MOVE_DOWN ) ) 
		||	input.GetJoystickAxis( 0, sf::Joy::AxisY ) > MOVE_JOYSTICK_TOLERANCE 
		||	in_circle_angle( pov_angle, DOWN_ANGLE, POV_ANGLE_TOLERANCE )
		)
		{
			if( position.y < ( SCREEN_HEIGHT - (FULL_SHIP_WIDTH/2) ) )
				move.y += 1;
		}

		
		move *= PLAYER_SHIP_SPEED;
		position += move;
		this->position( position );

		if( !is_rotating_guns() )
		{
			if( input.IsKeyDown( Key::Numpad7 ) 
			||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_ROTATE_LEFT ) )
			||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_ROTATE_LEFT ) 
			||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_ROTATE_AXIS ) ) > MOVE_JOYSTICK_TOLERANCE
			)
			{
				rotate_guns( 1 );
			}

			if( input.IsKeyDown( Key::Numpad9 )
			||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_ROTATE_RIGHT ) )
			||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_ROTATE_RIGHT ) 
			||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_ROTATE_AXIS ) ) < -MOVE_JOYSTICK_TOLERANCE 
			)
			{
				rotate_guns( -1 );
			}

		}

		// FIRE
		if( input.IsKeyDown( Key::Numpad6 ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_FIRE_RIGHT ) )
		||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_FIRE_RIGHT )
		||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_FIRE_AXIS_X ) ) > FIRE_JOYSTICK_TOLERANCE
		)
		{
			fire( GunsSetup_East );
		}
		
		if( input.IsKeyDown( Key::Numpad8 ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_FIRE_UP ) )
		||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_FIRE_UP ) 
		||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_FIRE_AXIS_Y ) ) < -FIRE_JOYSTICK_TOLERANCE
		)
		{
			fire( GunsSetup_North );
		}
		
		if( input.IsKeyDown( Key::Numpad4 )
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_FIRE_LEFT ) )
		||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_FIRE_LEFT ) 
		||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_FIRE_AXIS_X ) ) < -FIRE_JOYSTICK_TOLERANCE
		)
		{
			fire( GunsSetup_West );
		}
		
		if( input.IsKeyDown( Key::Numpad5 ) 
		||	input.IsKeyDown( Key::Code( KEYBOARD_PLAYERSHIP_FIRE_DOWN ) )
		||	input.IsJoystickButtonDown( 0, JOYSTICK_PLAYERSHIP_FIRE_DOWN ) 
		||	input.GetJoystickAxis( 0, Joy::Axis( JOYSTICK_PLAYERSHIP_FIRE_AXIS_Y ) ) > FIRE_JOYSTICK_TOLERANCE 
		)
		{
			fire( GunsSetup_South );
		}
		
	}

	void PlayerShip::update_guns()
	{
		if( is_rotating_guns() )
		{
			const float target_orientation = slot_direction( m_guns_setup );
			const float angle_difference = target_orientation - m_guns_orientation; // FUCK
			const float result_angle = std::abs( angle_difference );

			if( result_angle > GUN_ROTATION_SPEED )
			{
				const float rotation = GUN_ROTATION_SPEED * ( ( angle_difference > 0.0f ? 1 : -1 ) * (result_angle < 180.0f ? 1 : -1) );
				m_guns_orientation += rotation;
				if( m_guns_orientation > 360.0f )
				{
					m_guns_orientation -= 360.0f;
				}
				else if( m_guns_orientation < 0.0f )
				{
					m_guns_orientation += 360.0f;
				}
			}
			else
			{
				m_guns_orientation = target_orientation;
			}

			for( unsigned int i = 0; i < guns_count(); ++i )
			{
				unsigned int gid = i;
				if( has_gun( gid ) )
				{
					GunSlot gun = get_gun( gid );
					Orientation gun_dir = gun_direction( gid );
					gun->direction( gun_dir );
					gun->orientation( gun_dir );
				
				}
			}

		}

	}

	
	void PlayerShip::do_render()
	{
		render_guns();
		render_ship();
	}

	void PlayerShip::render_ship()
	{
		Position pos = position();

		const float ship_center_x = SHIP_WIDTH/2;
		const float ship_center_y = SHIP_HEIGHT/2;

		sf::Vector2f top_left( -ship_center_x, -ship_center_y );
		sf::Vector2f bottom_right( ship_center_x, ship_center_y );

		top_left += pos;
		bottom_right += pos;

		sf::Shape ship_shape = sf::Shape::Rectangle( top_left, bottom_right , sf::Color( 0, 180, 30 ) );

		Game::instance().display().Draw( ship_shape );
		Game::instance().display().Draw( core_shape() );
	}

	void PlayerShip::render_guns()
	{
		for( unsigned int i = 0; i < guns_count(); ++i )
		{
			if( has_gun( i ) )
				render_gun( i );
		}
	}

	void PlayerShip::render_gun( unsigned int gun_idx )
	{
		GunSlot gun = get_gun( gun_idx );
		
		const float HALF_HEIGHT = GUN_HEIGHT / 2;

		sf::Shape gun_shape = sf::Shape::Rectangle( GUN_DISTANCE, -HALF_HEIGHT, GUN_DISTANCE + GUN_WIDTH, HALF_HEIGHT , gun_color( gun_idx ) );
		sf::Shape cannon_shape = sf::Shape::Circle( gun->cannon(), 3.0f, sf::Color::White );

		Orientation gun_dir = gun_direction( gun_idx );
		gun_shape.Rotate( gun_dir );

		gun_shape.Move( position() );
		cannon_shape.Move( position() );
				
		Game::instance().display().Draw( gun_shape );
		Game::instance().display().Draw( cannon_shape );
	}

	sf::Color PlayerShip::gun_color( unsigned int gun_idx ) const
	{
		static const sf::Uint8 ALPHA = 255;
		static const std::array< sf::Color, MAX_PLAYER_GUNS > colors = 
		{ sf::Color( 255, 252, 0, ALPHA )
		, sf::Color( 255, 174, 0, ALPHA )
		, sf::Color( 255, 12, 0, ALPHA  )
		, sf::Color( 174, 0, 255, ALPHA )
		};

		return colors[ gun_idx ];
	}

	rlc::Orientation PlayerShip::gun_direction( unsigned int gun_idx ) const
	{
		float result = m_guns_orientation + slot_direction( gun_idx );
		while( result >= 360.0f )
			result -= 360.0f;
		return result;
	}


	rlc::Orientation PlayerShip::slot_direction( unsigned int gun_idx ) const
	{
		return GUN_ANGLE_INTERVAL * gun_idx;
	}

	void PlayerShip::rotate_guns( int setups )
	{
		int new_setup = m_guns_setup + setups;
		m_guns_setup = GunsSetup( new_setup % MAX_PLAYER_GUNS );
		
	}

	bool PlayerShip::is_rotating_guns() const
	{
		const float target_orientation = slot_direction( m_guns_setup );
		return m_guns_orientation > target_orientation
			|| m_guns_orientation < target_orientation
			;
	}

	int PlayerShip::gun_id( unsigned int slot )
	{
		return ( slot - int(m_guns_setup) ) % MAX_PLAYER_GUNS;
	}

	void PlayerShip::fire( GunsSetup dir )
	{
		if( is_rotating_guns() )
		{
			const Orientation target_dir = slot_direction( dir );
			Orientation min_orientation = target_dir - GUN_FIRE_BORDER_ANGLE;
			Orientation max_orientation = target_dir + GUN_FIRE_BORDER_ANGLE;

			for( unsigned int gun_idx = 0; gun_idx < guns_count(); ++gun_idx )
			{
				GunSlot gun = get_gun( gun_idx );
				const Orientation gun_dir = gun->orientation();

				if( gun_dir <= max_orientation && gun_dir >= min_orientation )
				{
					gun->fire();
				}

			}

		}
		else
		{
			fire_gun( gun_id( dir ) );
		}
		
	}


}