#include "pch.hpp"

#include "core/ui/ui.hpp"
#include "input.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam );

namespace hack::systems {
    std::intptr_t c_input::wnd_proc( const HWND window, const std::uint32_t msg, const std::uintptr_t u_param,
                                     const std::intptr_t i_param ) noexcept {
        const auto wnd_proc { g_input->m_wnd_proc };
        const auto lock_wnd_proc { std::unique_lock( g_input->m_wnd_proc_mutex, std::try_to_lock_t( ) ) };

        auto key_id { key_id_t {} };
        auto key_pressed { false };

        switch ( msg ) {
            case WM_KEYDOWN :
            case WM_SYSKEYDOWN : {
                key_id      = static_cast< key_id_t >( u_param );
                key_pressed = true;

                break;
            }
            case WM_KEYUP :
            case WM_SYSKEYUP : {
                key_id      = static_cast< key_id_t >( u_param );
                key_pressed = false;

                break;
            }
            case WM_LBUTTONDOWN :
            case WM_LBUTTONDBLCLK : {
                key_id      = VK_LBUTTON;
                key_pressed = true;

                break;
            }
            case WM_LBUTTONUP : {
                key_id      = VK_LBUTTON;
                key_pressed = false;

                break;
            }
            case WM_RBUTTONDOWN :
            case WM_RBUTTONDBLCLK : {
                key_id      = VK_RBUTTON;
                key_pressed = true;

                break;
            }
            case WM_RBUTTONUP : {
                key_id      = VK_RBUTTON;
                key_pressed = false;

                break;
            }
            case WM_MBUTTONDOWN :
            case WM_MBUTTONDBLCLK : {
                key_id      = VK_MBUTTON;
                key_pressed = true;

                break;
            }
            case WM_MBUTTONUP : {
                key_id      = VK_MBUTTON;
                key_pressed = false;

                break;
            }
            case WM_XBUTTONDOWN :
            case WM_XBUTTONDBLCLK : {
                key_id      = static_cast< key_id_t >( GET_XBUTTON_WPARAM( u_param ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2 );
                key_pressed = true;

                break;
            }
            case WM_XBUTTONUP : {
                key_id      = static_cast< key_id_t >( GET_XBUTTON_WPARAM( u_param ) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2 );
                key_pressed = false;

                break;
            }
            default :
                break;
        }

        if ( key_id ) {
            // note: callback array is [0, 254], and keycodes are [1-255], so we need to compensate it.
            if ( auto &fn_callback { g_input->m_callbacks[ key_id - 1 ] }; key_pressed && fn_callback )
                std::invoke( fn_callback );
        }

        if ( core::g_ui ) {
            if ( ImGui::GetCurrentContext( ) )
                ImGui_ImplWin32_WndProcHandler( window, msg, u_param, i_param );

            if ( core::g_ui->opened( ) ) {
                switch ( msg ) {
                    case WM_MOUSEMOVE :
                    case WM_NCMOUSEMOVE :
                    case WM_MOUSELEAVE :
                    case WM_NCMOUSELEAVE :
                    case WM_LBUTTONDOWN :
                    case WM_LBUTTONDBLCLK :
                    case WM_RBUTTONDOWN :
                    case WM_RBUTTONDBLCLK :
                    case WM_MBUTTONDOWN :
                    case WM_MBUTTONDBLCLK :
                    case WM_XBUTTONDOWN :
                    case WM_XBUTTONDBLCLK :
                    case WM_LBUTTONUP :
                    case WM_RBUTTONUP :
                    case WM_MBUTTONUP :
                    case WM_XBUTTONUP :
                    case WM_MOUSEWHEEL :
                    case WM_MOUSEHWHEEL :
                    case WM_KEYDOWN :
                    case WM_KEYUP :
                    case WM_SYSKEYDOWN :
                    case WM_SYSKEYUP :
                    case WM_SETFOCUS :
                    case WM_KILLFOCUS :
                    case WM_CHAR :
                    case WM_SETCURSOR :
                    case WM_DEVICECHANGE :
                        return true;
                    default :
                        break;
                }

                if ( ImGui::GetIO( ).WantTextInput || ImGui::GetIO( ).MouseWheel > 0.0f )
                    return true;
            }
        }

        return CallWindowProc( wnd_proc, window, msg, u_param, i_param );
    }
} // namespace hack::utils