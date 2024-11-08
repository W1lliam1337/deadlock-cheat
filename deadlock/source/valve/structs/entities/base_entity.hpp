#pragma once
#include "handle_entity.hpp"
#include "utils/math/data_types/vector.hpp"
#include "valve/net_vars/net_vars.hpp"

namespace hack::valve::inline data_types {
    struct collision_property_t;
    struct game_scene_node_t;
} // namespace hack::valve::inline data_types

namespace hack::valve::inline entities {
    struct entity_identity_t;

    struct entity_t : i_handle_entity_t {
        entity_t( )                  = delete;
        entity_t( entity_t && )      = delete;
        entity_t( const entity_t & ) = delete;

        NET_VAR( "C_BaseEntity", m_iHealth, int );
        NET_VAR( "C_BaseEntity", m_iMaxHealth, int );
        NET_VAR( "C_BaseEntity", m_pCollision, collision_property_t * );
        NET_VAR( "C_BaseEntity", m_iTeamNum, std::uint8_t )

        [[nodiscard]] _INLINE bool is_player_pawn( ) const noexcept, is_player_controller( ) const noexcept,
            is_modifier_invis( ) const noexcept;
        [[nodiscard]] bool is_enemy( ) noexcept;
    };

    struct base_model_entity_t : entity_t {
        base_model_entity_t( )                             = delete;
        base_model_entity_t( base_model_entity_t && )      = delete;
        base_model_entity_t( const base_model_entity_t & ) = delete;
    };

    struct entity_instance_t {
        entity_instance_t( )                           = delete;
        entity_instance_t( entity_instance_t && )      = delete;
        entity_instance_t( const entity_instance_t & ) = delete;

        NET_VAR( "CEntityInstance", m_entity, entity_identity_t * );
    };

} // namespace hack::valve::inline entities

#include "base_entity.inl"