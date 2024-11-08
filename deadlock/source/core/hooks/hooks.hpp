#pragma once
#include "systems/hooker/hooker.hpp"
#include "systems/module_parser/module_parser.hpp"
#include "utils/memory/base_address/base_address.hpp"

#define _HOOK( hooker, func )                           \
    using fn_##func                = decltype( &func ); \
    inline fn_##func g_orig_##func = hack::systems::hook_impl< fn_##func >( _HASH( #hooker ), hooker, reinterpret_cast< void * >( func ) );

namespace hack {
    namespace valve::inline interfaces {
        struct citadel_input_t;
    }

    namespace core {
        inline const auto g_get_matrices = hack::systems::get_pattern< void * >( "client.dll", "40 53 48 81 EC 10 01 00 00 49" );

        // xref: "cl: %d: %s\n", "cl: %d ===========================\n"
        inline const auto g_create_move = hack::systems::get_pattern< void * >( "client.dll", "85 D2 0F 85 21" );

        inline const auto g_present = hack::systems::get_pattern< void * >(
            "gameoverlayrenderer64.dll", "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 41 8B E8" );
        inline const auto g_resize_buffers = hack::systems::get_pattern< void * >(
            "gameoverlayrenderer64.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 44" );

        extern void _FASTCALL get_matrices( void *render_game_system, void *view_params, void *world_to_view, void *view_to_projection,
                                            void *world_to_projection, void *world_to_screen ) noexcept;
        extern void _FASTCALL create_move( valve::citadel_input_t *citadel_input, int slot, bool is_active );
        extern std::int32_t _FASTCALL present( IDXGISwapChain *const swap_chain, const std::uint32_t sync_interval,
                                               const std::uint32_t flags ) noexcept;
        extern std::int32_t _FASTCALL resize_buffers( IDXGISwapChain *const swap_chain, const std::uint32_t buffer_count,
                                                      const std::uint32_t width, const std::uint32_t height, const std::int32_t new_format,
                                                      const std::uint32_t swap_chain_flags ) noexcept;

        _HOOK( g_get_matrices, get_matrices )
        _HOOK( g_create_move, create_move )
        _HOOK( g_present, present )
        _HOOK( g_resize_buffers, resize_buffers )
    } // namespace core
} // namespace hack

#undef _HOOK