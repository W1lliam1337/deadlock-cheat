#pragma once
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "utils/math/data_types/vector.hpp"
#include "vendor.hpp"

namespace hack::systems {
    /// @brief A struct for rendering ImGui in a DirectX 11 environment.
    struct render_t {
        /// @brief Initialize render.
        _INLINE render_t( ) noexcept;

        /// @brief Destructor.
        _INLINE ~render_t( ) noexcept;

        /**
         * @brief Prepares ImGui rendering.
         *
         * @param swap_chain Pointer to the IDXGISwapChain interface. This interface is used to manipulate an image
         * buffer (a swap chain).
         */
        void prepare( IDXGISwapChain *swap_chain ) noexcept;

        /// @brief Resets the rendering environment.
        void reset( ) noexcept;

        /// @brief Resizes rendering buffers.
        void resize_buffers( ) noexcept;

        /// @brief Starts a new frame for rendering.
        void new_frame( ) const noexcept;

      private:
        struct {
            ImFont *m_esp { };
        } m_fonts { };

        ImGuiIO                *m_imgui_io { };            /**< Pointer to the ImGuiIO structure. */
        ID3D11Device           *m_d3d11device { };         /**< Pointer to the Direct3D 11 device. */
        ID3D11DeviceContext    *m_d3d11device_context { }; /**< Pointer to the Direct3D 11 device context. */
        ID3D11RenderTargetView *m_render_target_view { }, *m_backup_render_target_view { }; /**< Render target views. */
        bool                    m_initialized { };
    };

    inline auto g_render { std::unique_ptr< render_t > {} };
} // namespace hack::systems

#include "render.inl"