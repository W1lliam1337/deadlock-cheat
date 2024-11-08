#pragma once
#include "entity_utils.hpp"

namespace hack::valve {
    _INLINE c_entity_list::c_entity_list( ) {
        m_entities.reserve( k_ent_entry_mask );
        m_player_pawns.reserve( k_max_entity_lists );
        m_player_controllers.reserve( k_max_entity_lists );

        m_entity_system->get_listeners( ).add_to_head( &m_entity_listener );

        for ( int idx { }; idx <= m_entity_system->get_highest_entity_index( ); ++idx ) {
            const auto entity_instance { m_entity_system->get_entity( idx ) };
            if ( !entity_instance )
                continue;

            add_entity( entity_instance );
        }

        sort( );
    };

    _INLINE c_entity_list::~c_entity_list( ) noexcept {
        m_entity_system->get_listeners( ).find_and_remove( &m_entity_listener );
    }

    _INLINE std::span< entity_t *const > c_entity_list::get_entities( ) const noexcept {
        return m_entities;
    }

    _INLINE std::span< player_pawn_t *const > c_entity_list::get_player_pawns( ) const noexcept {
        return m_player_pawns;
    }

    _INLINE std::span< player_controller_t *const > c_entity_list::get_player_controllers( ) const noexcept {
        return m_player_controllers;
    }

    _INLINE player_controller_t *c_entity_list::get_local_controller( ) noexcept {
        return g_get_player_controller_by_id( -1 );
    }
} // namespace hack::valve