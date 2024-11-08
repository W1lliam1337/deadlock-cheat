#include "pch.hpp"

#include "../hooks.hpp"
#include "valve/entity_utils/entity_utils.hpp"
#include "valve/interfaces/citadel_input/citadel_input.hpp"

namespace hack::core {
    void get_matrices( void *render_game_system, void *view_params, void *world_to_view, void *view_to_projection,
                       void *world_to_projection, void *world_to_screen ) noexcept {
        g_orig_get_matrices( render_game_system, view_params, world_to_view, view_to_projection, world_to_projection, world_to_screen );
    }

    void create_move( valve::citadel_input_t *citadel_input, const int slot, const bool is_active ) {
        g_orig_create_move( citadel_input, slot, is_active );

        const auto local_controller { valve::g_entity_list->get_local_controller( ) };
        if ( !local_controller )
            return g_orig_create_move( citadel_input, slot, is_active );

        const auto cmd { local_controller->get_cmd( ) };
        if ( !cmd || !cmd->m_base_user_cmd || !cmd->m_camera_angle )
            return g_orig_create_move( citadel_input, slot, is_active );

        const auto base_cmd { cmd->m_base_user_cmd };
        if ( !base_cmd->m_angle )
            return g_orig_create_move( citadel_input, slot, is_active );

        // todo: legitbot :)
    }
} // namespace hack::core