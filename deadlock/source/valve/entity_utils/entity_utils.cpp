#include "pch.hpp"

#include "entity_utils.hpp"

namespace hack::valve {
    void c_entity_list::add_entity( entity_t *entity ) noexcept {
        if ( !entity || std::ranges::find( m_entities, entity ) != m_entities.end( ) )
            return;

        m_entities.emplace_back( entity );

        if ( const auto base_entity { entity }; base_entity->is_player_pawn( ) )
            m_player_pawns.emplace_back( static_cast< player_pawn_t * >( base_entity ) );
        else if ( base_entity->is_player_controller( ) )
            m_player_controllers.emplace_back( static_cast< player_controller_t * >( base_entity ) );
    }

    void c_entity_list::remove_entity( entity_t *entity ) noexcept {
        if ( !entity )
            return;

        const auto founded_entity { std::ranges::find( m_entities, entity ) };
        if ( founded_entity == m_entities.end( ) )
            return;

        m_entities.erase( founded_entity );

        if ( const auto base_entity { entity }; base_entity->is_player_pawn( ) ) {
            if ( const auto player_pawn { std::ranges::find( m_player_pawns, entity ) }; player_pawn != m_player_pawns.end( ) )
                m_player_pawns.erase( player_pawn );
        } else if ( base_entity->is_player_controller( ) ) {
            if ( const auto player_controller { std::ranges::find( m_player_controllers, entity ) };
                 player_controller != m_player_controllers.end( ) )
                m_player_controllers.erase( player_controller );
        }
    }

    void c_entity_list::sort( ) noexcept {
        auto entity_sort = []( const entity_t *first, const entity_t *second ) {
            return first->m_pEntity( )->m_handle.get_index( ) < second->m_pEntity( )->m_handle.get_index( );
        };

        std::ranges::sort( m_entities, entity_sort );
        std::ranges::sort( m_player_pawns, entity_sort );
        std::ranges::sort( m_player_controllers, entity_sort );
    }

    void c_entity_list::c_entity_listener::on_entity_created( entity_t *ent ) noexcept {
        g_entity_list->add_entity( ent );
        g_entity_list->sort( );
    }

    void c_entity_list::c_entity_listener::on_entity_deleted( entity_t *ent ) noexcept {
        g_entity_list->remove_entity( ent );
        g_entity_list->sort( );
    }
} // namespace hack::valve