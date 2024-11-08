#pragma once
#include "ui.hpp"

namespace hack::core {
    _INLINE ui_t::ui_t( ) noexcept {
        auto &style { ImGui::GetStyle( ) };

        style.AntiAliasedFill   = false;
        style.AntiAliasedLines  = false;
        style.WindowRounding    = 0.0f;
        style.ChildRounding     = 6.f;
        style.PopupRounding     = 2.f;
        style.FrameRounding     = 2.f;
        style.ScrollbarRounding = 2.f;
        style.GrabRounding      = 2.f;
        style.TabRounding       = 2.f;

        ImGui::StyleColorsDark( ); ///< Set a dark theme by default
    }

    _INLINE bool &ui_t::opened( ) noexcept {
        return m_opened;
    }
} // namespace hack::core
