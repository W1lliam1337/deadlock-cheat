#include "pch.hpp"

#include "core/hooks/hooks.hpp"
#include "core/ui/ui.hpp"
#include "systems/input/input.hpp"
#include "systems/logger/logger.hpp"
#include "systems/render/render.hpp"
#include "valve/entity_utils/entity_utils.hpp"
#include "valve/net_vars/net_vars.hpp"

namespace hack::bootstrap {
    void on_dll_detach( void *handle ) noexcept;

    void on_dll_attach( [[maybe_unused]] void *handle ) noexcept {
        systems::g_logger    = std::make_unique< systems::logger_t >( "C:\\deadlock\\cheat.log" );
        systems::g_render    = std::make_unique< systems::render_t >( );
        valve::g_net_vars    = std::make_unique< valve::net_vars_t >( );
        valve::g_entity_list = std::make_unique< valve::c_entity_list >( );

        systems::g_input->register_callback( VK_END, [ handle ] {
            systems::g_input->remove_callback( VK_END );
            std::jthread( on_dll_detach, handle ).detach( );
        } );
    }

    void on_dll_detach( void *handle ) noexcept {
        _INFO_LOG( "Unloading..." );

        systems::g_hook_manager.reset( );
        core::g_ui.reset( );
        systems::g_render.reset( );
        systems::g_input.reset( );
        valve::g_net_vars.reset( );
        valve::g_entity_list.reset( );

        systems::g_logger.reset( );

        FreeLibrary( static_cast< HMODULE >( handle ) );
    }
} // namespace hack::bootstrap

bool _STDCALL DllMain( void *handle, const std::uint8_t reason, [[maybe_unused]] void *const reserved ) {
    if ( reason == DLL_PROCESS_ATTACH ) {
        std::jthread( hack::bootstrap::on_dll_attach, handle ).detach( );
        return true;
    }
    return false;
}