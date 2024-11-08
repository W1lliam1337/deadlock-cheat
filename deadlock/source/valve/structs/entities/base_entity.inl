#pragma once
#include "base_entity.hpp"

namespace hack::valve::inline entities {
    _INLINE bool entity_t::is_player_pawn( ) const noexcept {
        return is_class( _HASH( "C_CitadelPlayerPawn" ) );
    }

    _INLINE bool entity_t::is_player_controller( ) const noexcept {
        return is_class( _HASH( "CCitadelPlayerController" ) );
    }

    _INLINE bool entity_t::is_modifier_invis( ) const noexcept {
        return is_class( _HASH( "CCitadel_Modifier_Invis" ) );
    }
} // namespace hack::cs2::inline entities
