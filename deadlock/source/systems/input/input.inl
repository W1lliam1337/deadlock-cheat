#pragma once
#include "input.hpp"

namespace hack::systems {
    _INLINE c_input::c_input( const HWND game_window ) noexcept {
        m_game_window = game_window;
        m_wnd_proc
            = reinterpret_cast< WNDPROC >( SetWindowLongPtr( m_game_window, GWLP_WNDPROC, reinterpret_cast< std::intptr_t >( wnd_proc ) ) );
    }

    _INLINE c_input::~c_input( ) noexcept {
        SetWindowLongPtr( m_game_window, GWLP_WNDPROC, reinterpret_cast< std::intptr_t >( m_wnd_proc ) );

        {
            const std::unique_lock lock_wnd_proc( m_wnd_proc_mutex );

            m_wnd_proc = nullptr;
        }

        m_game_window = nullptr;
    }

    _INLINE void c_input::register_callback( const key_id_t key_id, std::function< void( ) > &&callback ) noexcept {
        m_callbacks[ key_id - 1 ] = std::move( callback );
    }

    _INLINE auto c_input::get_hwnd( ) noexcept {
        return m_game_window;
    }

    _INLINE void c_input::remove_callback( const key_id_t key_id ) noexcept {
        m_callbacks[ key_id - 1 ] = nullptr;
    }
} // namespace hack::systems