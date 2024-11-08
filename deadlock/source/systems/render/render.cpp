#include "pch.hpp"

#include "core/ui/ui.hpp"
#include "render.hpp"
#include "systems/input/input.hpp"
#include "systems/logger/logger.hpp"

namespace hack::systems {
    void render_t::prepare( IDXGISwapChain *const swap_chain ) noexcept {
        // Obtains the Direct3D device associated with the swap chain
        if ( FAILED( swap_chain->GetDevice( IID_PPV_ARGS( &m_d3d11device ) ) ) )
            return;

        // Obtains the immediate context of the Direct3D device
        m_d3d11device->GetImmediateContext( &m_d3d11device_context );

#pragma clang diagnostic ignored "-Wlanguage-extension-token"
        // Declares a pointer to a Direct3D texture that will hold the back buffer
        ID3D11Texture2D *back_buffer { };
        if ( FAILED( swap_chain->GetBuffer( 0, IID_PPV_ARGS( &back_buffer ) ) ) )
            return;
#pragma clang diagnostic warning "-Wlanguage-extension-token"

        DXGI_SWAP_CHAIN_DESC back_buffer_desc { };
        if ( FAILED( swap_chain->GetDesc( &back_buffer_desc ) ) )
            return;

        // Retrieves the handle to the game window
        const auto game_window { back_buffer_desc.OutputWindow };

        // Sets up the description for creating a render target view
        D3D11_RENDER_TARGET_VIEW_DESC d3d11_render_target_view_desc { };
        d3d11_render_target_view_desc.Format        = DXGI_FORMAT_R8G8B8A8_UNORM;
        d3d11_render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

        // Creates a render target view for the back buffer
        if ( FAILED( m_d3d11device->CreateRenderTargetView( back_buffer, &d3d11_render_target_view_desc, &m_render_target_view ) ) )
            return;

        // Backs up the current render target view
        m_d3d11device_context->OMGetRenderTargets( 1, &m_backup_render_target_view, nullptr );
        // Sets the newly created render target view as the active render target
        m_d3d11device_context->OMSetRenderTargets( 1, &m_render_target_view, nullptr );

        if ( !m_initialized ) {
            // Initializes ImGui only once
            if ( !ImGui::GetCurrentContext( ) )
                ImGui::CreateContext( );

            ImGui_ImplWin32_Init( game_window );
            ImGui_ImplDX11_Init( m_d3d11device, m_d3d11device_context );

            core::g_ui = std::make_unique< core::ui_t >( );
            g_input    = std::make_unique< c_input >( game_window );

            g_input->register_callback( VK_INSERT, [] {
                core::g_ui->opened( ) = !core::g_ui->opened( );
            } );

            _INFO_LOG( "Initialized ImGui" );
            m_initialized = true;
        }
    }

    void render_t::new_frame( ) const noexcept {
        if ( !m_initialized )
            return;

        ImGui_ImplDX11_NewFrame( );
        ImGui_ImplWin32_NewFrame( );
        ImGui::NewFrame( );
    }

    void render_t::reset( ) noexcept {
        if ( !m_render_target_view )
            return;

        // Resets the render target view to the backed up render target view
        m_d3d11device_context->OMSetRenderTargets( 1, &m_backup_render_target_view, nullptr );

        // Clear the backed up render target view
        if ( m_backup_render_target_view ) {
            m_backup_render_target_view->Release( );
            m_backup_render_target_view = nullptr;
        }

        // Cleat the current render target view
        if ( m_render_target_view ) {
            m_render_target_view->Release( );
            m_render_target_view = nullptr;
        }
    }

    void render_t::resize_buffers( ) noexcept {
        if ( m_backup_render_target_view ) {
            m_backup_render_target_view->Release( );
            m_backup_render_target_view = nullptr;
        }

        if ( m_render_target_view ) {
            m_render_target_view->Release( );
            m_render_target_view = nullptr;
        }

        if ( m_d3d11device_context ) {
            m_d3d11device_context->Release( );
            m_d3d11device_context = nullptr;
        }

        if ( m_d3d11device ) {
            m_d3d11device->Release( );
            m_d3d11device = nullptr;
        }

        ImGui_ImplDX11_Shutdown( );
        ImGui::DestroyContext( );
    }
} // namespace hack::systems