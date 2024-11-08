#include "pch.hpp"

#include "../hooks.hpp"
#include "core/ui/ui.hpp"
#include "systems/render/render.hpp"

namespace hack::core {
    std::int32_t present( IDXGISwapChain *const swap_chain, const std::uint32_t sync_interval,
                                          const std::uint32_t flags ) noexcept {
        if ( !systems::g_render )
            return g_orig_present( swap_chain, sync_interval, flags );

        // Prepare some imgui data
        {
            systems::g_render->prepare( swap_chain );
            systems::g_render->new_frame( );
        }

        // Render draw data
        {
            core::g_ui->render( );

            ImGui::Render( );
            ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
        }

        // End of present
        const auto result { g_orig_present( swap_chain, sync_interval, flags ) };
        if ( systems::g_render )
            systems::g_render->reset( );

        return result;
    }

    std::int32_t resize_buffers( IDXGISwapChain *const swap_chain, const std::uint32_t buffer_count,
                                                 const std::uint32_t width, const std::uint32_t height, const std::int32_t new_format,
                                                 const std::uint32_t swap_chain_flags ) noexcept {
        systems::g_render->resize_buffers( );
        return g_orig_resize_buffers( swap_chain, buffer_count, width, height, new_format, swap_chain_flags );
    }
} // namespace hack::core