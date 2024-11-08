#include "pch.hpp"

#include "ui.hpp"

namespace hack::core {
    void ui_t::render( ) const noexcept {
        if ( !m_opened )
            return;

        ImGui::SetNextWindowSize( { 630, 460 } );

        // Begin rendering a simple main menu
        ImGui::Begin( "Hack Menu" );

        // Display tabs or main options
        if ( ImGui::CollapsingHeader( "Settings" ) ) {
            ImGui::Text( "Configuration Settings" );

            static auto feature_enabled { false };
            ImGui::Checkbox( "Enable Feature", &feature_enabled );

            static auto slider_value { 0.5f };
            ImGui::SliderFloat( "Intensity", &slider_value, 0.0f, 1.0f, "%.2f" );

            static auto choice { 0 };
            const char *items[] = { "Option 1", "Option 2", "Option 3" };
            ImGui::Combo( "Choose Option", &choice, items, IM_ARRAYSIZE( items ) );
        }

        if ( ImGui::CollapsingHeader( "Debug Tools" ) ) {
            ImGui::Text( "Debugging Options" );
            static auto show_metrics { false };
            ImGui::Checkbox( "Show Metrics Window", &show_metrics );

            if ( show_metrics ) {
                ImGui::ShowMetricsWindow( &show_metrics );
            }
        }

        ImGui::End( );
    }

    void ui_t::cleanup( ) noexcept {
        // todo: cleanup resources if necessary
    }
} // namespace hack::core
