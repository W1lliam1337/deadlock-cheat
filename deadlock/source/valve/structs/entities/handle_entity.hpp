#pragma once
#include "../data_types/handle/handle.hpp"
#include "valve/net_vars/net_vars.hpp"

namespace hack::valve::inline entities {
    static inline constexpr std::uint32_t k_num_serial_shift_bits { 0xfu };
    struct entity_identity_t;

    struct i_handle_entity_t {
        i_handle_entity_t( )                           = delete;
        i_handle_entity_t( i_handle_entity_t && )      = delete;
        i_handle_entity_t( const i_handle_entity_t & ) = delete;

        NET_VAR( "CEntityInstance", m_pEntity, entity_identity_t * )

        [[nodiscard]] _INLINE auto game_get_ent_class_info( void *, class_info_t **ret ) const noexcept;

        [[nodiscard]] _INLINE interfaces::class_info_t *get_class_info( ) const noexcept;

        [[nodiscard]] _INLINE bool is_class( const std::size_t name_hash ) const noexcept;
    };
} // namespace hack::valve::inline entities

#include "handle_entity.inl"