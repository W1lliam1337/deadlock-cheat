#pragma once
#include "handle_entity.hpp"

namespace hack::valve::inline entities {
    _INLINE auto i_handle_entity_t::game_get_ent_class_info( void *, class_info_t **ret ) const noexcept {
        return hack::utils::get_virtual< void >( 36, this, &ret );
    }

    _INLINE interfaces::class_info_t *i_handle_entity_t::get_class_info( ) const noexcept {
        interfaces::class_info_t *ret { };
        hack::utils::get_virtual< void >( 38, this, &ret );
        return ret;
    }

    bool i_handle_entity_t::is_class( const std::size_t name_hash ) const noexcept {
        const auto class_info { get_class_info( ) };
        return class_info ? _HASH( class_info->m_name ) == name_hash : false;
    }
} // namespace hack::valve::inline entities