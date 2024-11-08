#pragma once
#include "imgui/imgui.h"
#include "vendor.hpp"

namespace hack::core {
    /**
     * @brief Structure representing the core UI.
     */
    struct ui_t {
        /**
         * @brief Initializes the UI components and sets up the layout.
         */
        _INLINE ui_t( ) noexcept;

        _INLINE bool &opened( ) noexcept;

        /**
         * @brief Renders the main menu interface.
         */
        void render( ) const noexcept;

        /**
         * @brief Cleans up UI resources if needed.
         */
        static void cleanup( ) noexcept;

      private:
        bool m_opened { };
    };

    inline auto g_ui { std::unique_ptr< ui_t > {} };
} // namespace hack::core

#include "ui.inl"