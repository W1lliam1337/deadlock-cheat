#pragma once
#include "entity_system.hpp"

namespace hack::valve::inline interfaces {
    _INLINE valve::entity_identity_t *game_entity_system_t::get_identity( const int idx ) const noexcept {
        if ( idx <= -1 || idx >= ( k_max_total_entities - 1 ) )
            return nullptr;

        const auto chunk_to_use { get_identity_chunks( )[ ( idx / k_max_entities_in_list ) ] }; // equal to ( index >> 9 )

        if ( !chunk_to_use )
            return nullptr;

        const auto identity { &chunk_to_use->m_identities[ idx % k_max_entities_in_list ] }; // equal to ( index & 1FF )
        if ( !identity )
            return nullptr;

        return identity;
    }

    _INLINE entity_identity_t *game_entity_system_t::get_entity( const c_handle ent ) const noexcept {
        return get_identity( ent.get_index( ) );
    }

    template < typename type_t >
    std::add_pointer_t< type_t > game_entity_system_t::get_entity( const int idx ) noexcept {
        if ( const auto identity { get_identity( idx ) }; identity && identity->m_handle.get_index( ) == idx ) {
            return std::to_address( identity->m_entity );
        }
        return nullptr;
    }
} // namespace hack::valve::inline interfaces