#pragma once
#include "render.hpp"

namespace hack::systems {
    _INLINE render_t::render_t( ) noexcept {
        // Retrieves the path to the system's font directory
        std::filesystem::path fonts_path { };
        {
            wchar_t *path { };
            // Retrieves the font directory path
            if ( FAILED( SHGetKnownFolderPath( FOLDERID_Fonts, 0, nullptr, &path ) ) )
                return;

            fonts_path = path;

            /* Frees the allocated memory for the font directory path
             * @note: @william:
             * ATL provides some classes like ATL::CComPtr which are wrapper objects that handle the reference counting
             * of COM objects for you. They are not foolproof to use correctly, and, in fact, have a few more gotchas
             * than most of the modern STL classes, so read the documentation carefully. When used correctly, it's
             * relatively easy to make sure the AddRef and Release calls all match up.
             */
            CoTaskMemFree( path );
        }

        // Creates a new ImGui context if one does not already exist
        if ( !ImGui::GetCurrentContext( ) ) {
            ImGui::CreateContext( );
        }

        m_imgui_io = &ImGui::GetIO( );

        // Disables mouse cursor change and keyboard capture for navigation
        m_imgui_io->LogFilename = m_imgui_io->IniFilename = nullptr;

        m_imgui_io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavNoCaptureKeyboard;

        // Defines ranges of Unicode characters for font rendering
        ImVector< ImWchar >      ranges { };
        ImFontGlyphRangesBuilder ranges_builder { };

        static constexpr auto base_ranges { std::to_array< ImWchar >( {
            0x0020,
            0x00FF, // Basic Latin + Latin Supplement
            0x0400,
            0x044F, // Cyrillic
            0xF000,
            0xF3FF, // icons
            0,
        } ) };

        // Adds base character ranges
        ranges_builder.AddRanges( base_ranges.data( ) );

        // Adds Cyrillic character ranges
        ranges_builder.AddRanges( m_imgui_io->Fonts->GetGlyphRangesCyrillic( ) );

        // Builds the final character ranges for font rendering
        ranges_builder.BuildRanges( &ranges );

        // Configures and loads the Verdana font for rendering
        const ImFontConfig verdana_config { };

        m_imgui_io->Fonts->Clear( );
        m_fonts.m_esp = m_imgui_io->Fonts->AddFontFromFileTTF( ( fonts_path / "Verdana.ttf" ).string( ).c_str( ), 12.0f, &verdana_config,
                                                               ranges.Data );

        // Builds the font atlas
        m_imgui_io->Fonts->Build( );
    }

    _INLINE render_t::~render_t( ) noexcept {
        // Destroys the ImGui context
        if ( ImGui::GetCurrentContext( ) ) {
            if ( m_imgui_io->Fonts )
                m_imgui_io->Fonts->ClearFonts( );

            ImGui_ImplDX11_Shutdown( );
            ImGui_ImplWin32_Shutdown( );

            ImGui::DestroyContext( );
        }
    }
} // namespace hack::systems