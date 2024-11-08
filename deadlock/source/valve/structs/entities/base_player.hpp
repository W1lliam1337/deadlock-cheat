#pragma once
#include "base_entity.hpp"

namespace hack::valve {
    inline namespace interfaces {
        struct user_cmd_pb_t;
    }

    inline namespace entities {
        class c_econ_item_view : public i_handle_entity_t {
          public:
            NET_VAR( "C_EconItemView", m_iItemDefinitionIndex, std::uint16_t )
            NET_VAR( "C_EconItemView", m_iItemID, std::uint64_t );
            NET_VAR( "C_EconItemView", m_iItemIDLow, std::int32_t );
            NET_VAR( "C_EconItemView", m_iItemIDHigh, std::int32_t );
            NET_VAR( "C_EconItemView", m_iAccountID, std::int32_t );
            NET_VAR( "C_EconItemView", m_iEntityQuality, std::int32_t );
            NET_VAR( "C_EconItemView", m_bInitialized, bool );
        };

        struct attribute_container_t {
            NET_VAR( "C_AttributeContainer", m_Item, c_econ_item_view )
        };

        struct econ_entity_t : entity_t {
            NET_VAR( "C_EconEntity", m_AttributeManager, attribute_container_t );
            NET_VAR( "C_EconEntity", m_OriginalOwnerXuidLow, std::uint32_t );
            NET_VAR( "C_EconEntity", m_OriginalOwnerXuidHigh, std::uint32_t );
            NET_VAR( "C_EconEntity", m_nFallbackPaintKit, std::int32_t );
            NET_VAR( "C_EconEntity", m_nFallbackSeed, std::int32_t );
            NET_VAR( "C_EconEntity", m_flFallbackWear, float );
            NET_VAR( "C_BasePlayerWeapon", m_iClip1, std::int32_t )
        };

        struct weapon_services_t {
            NET_VAR( "CPlayer_WeaponServices", m_hMyWeapons, econ_entity_t * )
            NET_VAR( "CPlayer_WeaponServices", m_hActiveWeapon, c_handle )
        };

        struct player_pawn_t : entity_t {
            player_pawn_t( )                       = delete;
            player_pawn_t( player_pawn_t && )      = delete;
            player_pawn_t( const player_pawn_t & ) = delete;

            NET_VAR( "C_BasePlayerPawn", m_hController, c_handle )
            NET_VAR( "C_BasePlayerPawn", m_pWeaponServices, weapon_services_t * )
        };

        struct player_controller_t : entity_t {
            player_controller_t( )                             = delete;
            player_controller_t( player_controller_t && )      = delete;
            player_controller_t( const player_controller_t & ) = delete;

            [[nodiscard]] user_cmd_pb_t *get_cmd( ) const noexcept;

            NET_VAR( "CBasePlayerController", m_hPawn, c_handle )
            NET_VAR( "CCSPlayerController", m_hPlayerPawn, c_handle );
            NET_VAR( "CCSPlayerController", m_iszPlayerName, char * );
        };

        inline const auto g_get_player_controller_by_id
            = systems::get_pattern< fastcall_t< player_controller_t *, int > >( "client.dll", "33 C0 83 F9 FF" );
    } // namespace entities
} // namespace hack::valve

#include "base_player.inl"