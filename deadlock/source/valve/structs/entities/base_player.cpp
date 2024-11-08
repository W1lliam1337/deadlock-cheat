#include "pch.hpp"

#include "base_player.hpp"
#include "valve/entity_utils/entity_utils.hpp"
#include "valve/interfaces/citadel_input/citadel_input.hpp"
#include "valve/interfaces/entity_system/entity_system.hpp"

namespace hack::valve::inline entities {
    inline const auto g_get_index
        = systems::get_pattern< fastcall_t< void, void *, void * > >( "client.dll", "40 53 48 83 EC 20 4C 8B 41 10 48 8B DA" );

    user_cmd_pb_t *player_controller_t::get_cmd( ) const noexcept {
        const auto local_controller { g_entity_list->get_local_controller( ) };
        if ( !local_controller || local_controller != this )
            return { };

        int index { };
        g_get_index( local_controller, &index );

        std::intptr_t corrected_index;
        if ( index != -1 ) {
            if ( static_cast< std::uint32_t >( index - 1 ) > k_max_entity_lists - 1 )
                return { };

            corrected_index = static_cast< std::uint32_t >( index - 1 );
        } else {
            corrected_index = 0xFFFFFFFF;
        }

        const auto base_cmd_ptr { *utils::base_address_t { g_cmd_base }.offset( corrected_index * 0x8 ).as< base_user_cmd_t ** >( ) };
        return g_get_user_cmd( local_controller, *utils::base_address_t { base_cmd_ptr }.offset( 21136 ).as< std::uint32_t * >( ) );
    }
} // namespace hack::valve::inline entities