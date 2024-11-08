#pragma once
#include "vendor.hpp"

namespace hack::systems {
    /// @brief Type alias for key identifier.
    using key_id_t = std::uint8_t;

    /// @brief Class for handling input events.
    class c_input {
      public:
        /**
         * @brief Constructor.
         * @param game_window Handle to the game window.
         */
        _INLINE c_input( HWND game_window ) noexcept;

        /// @brief Destructor.
        _INLINE ~c_input( ) noexcept;

        /**
         * @brief Registers a callback function for a specific key.
         * @param key_id Identifier of the key.
         * @param callback Callback function to be executed.
         */
        _INLINE void register_callback( key_id_t key_id, std::function< void( ) > &&callback ) noexcept;

        _INLINE auto get_hwnd( ) noexcept;

        /**
         * @brief Removes the callback function associated with a key.
         * @param key_id Identifier of the key.
         */
        _INLINE void remove_callback( key_id_t key_id ) noexcept;

      private:
        WNDPROC m_wnd_proc { };    /**< Pointer to the original window procedure. */
        HWND    m_game_window { }; /**< Handle to the game window. */

        std::function< void( ) > m_callbacks[ std::numeric_limits< key_id_t >::max( ) ]
            = { }; /**< Array of callback functions for each key.
                    */

        std::mutex m_wnd_proc_mutex { }; /**< Mutex for thread safety. */

        /**
         * @brief Handle window procedure.
         *
         * A callback function, which you define in your application, that processes messages sent to a window. The
         * WNDPROC type defines a pointer to this callback function. The WndProc name is a placeholder for the name of
         * the function that you define in your application.
         *
         * @param window Handle to the window.
         * @param msg Message identifier.
         * @param u_param Additional message information.
         * @param i_param Additional message information.
         * @param window
         * @param msg
         * @param u_param
         * @return Result of the window procedure.
         */
        static std::intptr_t wnd_proc( HWND window, std::uint32_t msg, std::uintptr_t u_param, std::intptr_t i_param ) noexcept;
    };

    inline std::unique_ptr< c_input > g_input { };
} // namespace hack::utils

#include "input.inl"