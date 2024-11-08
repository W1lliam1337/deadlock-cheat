#pragma once
#include "ldr_module.hpp"

namespace hack::systems::inline memory {
    _INLINE systems::ldr_module_t::ldr_module_t( const utils::base_address_t &address ) noexcept : m_base_address { address } { }

    _INLINE utils::base_address_t ldr_module_t::get_base_address( ) const noexcept {
        return utils::base_address_t { this->m_base_address.as< const utils::ldr_data_table_entry * >( )->m_dll_base };
    }

    _INLINE std::wstring ldr_module_t::get_wname( const e_name_case name_case ) const noexcept {
        _ASSERT( name_case != e_name_case::e_unknown );

        const auto *const base_name { &this->m_base_address.as< const utils::ldr_data_table_entry * >( )->m_base_dll_name };

        _ASSERT( base_name->m_buffer != nullptr && base_name->m_length != 0 );

        auto stl_name {
            std::wstring {base_name->m_buffer, base_name->m_length / sizeof( wchar_t )}
        };

        _ASSERT( !stl_name.empty( ) );

        switch ( name_case ) {
            case e_name_case::e_unmodified :
                break;
            case e_name_case::e_lowercase :
                std::ranges::transform( stl_name, stl_name.begin( ), towlower );
                break;
            case e_name_case::e_uppercase :
                std::ranges::transform( stl_name, stl_name.begin( ), towupper );
                break;
            default :
                _ASSERT( false );
        }

        return stl_name;
    }

    _INLINE std::string ldr_module_t::get_name( const e_name_case name_case ) const noexcept {
        _ASSERT( name_case != e_name_case::e_unknown );

        const auto wname { this->get_wname( name_case ) };

        _ASSERT( !wname.empty( ) );

        return { wname.cbegin( ), wname.cend( ) };
    }

    _INLINE utils::image_nt_headers_64 *ldr_module_t::get_nt_headers( ) const {
        const auto base_address { m_base_address };

        _ASSERT( base_address != nullptr );

        static constexpr auto dos_header_signature { 0x5A4D };
        static constexpr auto nt_headers_signature { 0x4550 };

        const auto dos_header { base_address.as< const utils::image_dos_header * >( ) };

        _ASSERT( dos_header != nullptr && dos_header->m_magic == dos_header_signature );

        const auto nt_headers { base_address.offset( dos_header->m_lfanew ).as< utils::image_nt_headers_64 * >( ) };

        _ASSERT( nt_headers != nullptr && nt_headers->m_signature == nt_headers_signature );
        return nt_headers;
    }

    _INLINE std::vector< std::optional< std::byte > > ldr_module_t::pattern_to_bytes( const std::string_view pattern ) noexcept {
        std::vector< std::optional< std::byte > > bytes = { };

        const auto start { pattern.data( ) };
        const auto end { start + pattern.size( ) };

        for ( auto current { start }; current < end; ++current ) {
            if ( *current == '?' ) {
                ++current;
                if ( *current == '?' )
                    ++current;

                bytes.emplace_back( std::nullopt );
            } else
                bytes.emplace_back( static_cast< std::byte >( std::strtoul( current, const_cast< char ** >( &current ), 16 ) ) );
        }

        return bytes;
    }

    _INLINE utils::base_address_t ldr_module_t::find_interface( const std::string_view interface_name ) const noexcept {
        const auto base_address { this->get_base_address( ) };

        _ASSERT( base_address != nullptr );

        const auto interface_func_addr { this->get_export_address( "CreateInterface" ) };

        _ASSERT( interface_func_addr != nullptr );

        const auto create_interface { interface_func_addr.as< fastcall_t< void *, const char *, int * > >( ) };

        return utils::base_address_t( create_interface( interface_name.data( ), nullptr ) );
    }

    _INLINE utils::base_address_t ldr_module_t::find_pattern( const std::string_view pattern ) const noexcept {
        const auto bytes { pattern_to_bytes( pattern ) };

        _ASSERT( !bytes.empty( ) );

        const auto base_address { this->get_base_address( ) };

        _ASSERT( base_address != nullptr );

        const auto *const optional_header { get_optional_header( base_address ).as< const utils::image_optional_header_64 * >( ) };

        _ASSERT( optional_header != nullptr );

        const auto size_of_image { optional_header->m_size_of_image };

        _ASSERT( size_of_image != 0 );

        const auto scan_bytes {
            std::span {base_address.as< const std::byte * >( ), size_of_image}
        };

        for ( auto i { std::size_t {} }; i < scan_bytes.size( ); ++i ) {
            auto found { true };

            for ( auto j { std::size_t {} }; j < bytes.size( ); ++j ) {
                if ( bytes.at( j ) == std::nullopt )
                    continue;

                if ( scan_bytes[ i + j ] != bytes.at( j ) ) {
                    found = false;
                    break;
                }
            }

            if ( found ) {
                return base_address.offset( static_cast< std::ptrdiff_t >( i ) );
            }
        }

        return { };
    }

    _INLINE constexpr utils::base_address_t ldr_module_t::get_data_directory( const utils::base_address_t &base_address,
                                                                              const e_data_directory       data_directory ) noexcept {
        _ASSERT( base_address != nullptr
                 && ( data_directory >= e_data_directory::e_export && data_directory <= e_data_directory::e_com_descriptor ) );

        const auto *const optional_header { get_optional_header( base_address ).as< const utils::image_optional_header_64 * >( ) };

        _ASSERT( optional_header != nullptr
                 && static_cast< const std::uint16_t >( data_directory ) < optional_header->m_data_directory.size( ) );

        const auto data_directory_entry { optional_header->m_data_directory.at( static_cast< const std::uint16_t >( data_directory ) ) };

        _ASSERT( data_directory_entry.m_virtual_address != 0 && data_directory_entry.m_size != 0 );

        return base_address.offset( data_directory_entry.m_virtual_address );
    }

    _INLINE constexpr utils::base_address_t ldr_module_t::get_export_address( const std::string_view procedure_name ) const noexcept {
        _ASSERT( !procedure_name.empty( ) );
        return utils::base_address_t { GetProcAddress( this->get_base_address( ).as< HMODULE >( ), procedure_name.data( ) ) };
    }

    _INLINE constexpr utils::base_address_t ldr_module_t::get_optional_header( const utils::base_address_t &base_address ) noexcept {
        _ASSERT( base_address != nullptr );

        static constexpr auto dos_header_signature { 0x5A4D };
        static constexpr auto nt_headers_signature { 0x4550 };
        static constexpr auto optional_header_magic { 0x20B };

        const auto *const dos_header { base_address.as< const utils::image_dos_header * >( ) };

        _ASSERT( dos_header != nullptr && dos_header->m_magic == dos_header_signature );

        const auto *const nt_headers { base_address.offset( dos_header->m_lfanew ).as< const utils::image_nt_headers_64 * >( ) };

        _ASSERT( nt_headers != nullptr && nt_headers->m_signature == nt_headers_signature );

        const auto *const optional_header { &nt_headers->m_optional_header };

        _ASSERT( optional_header != nullptr && optional_header->m_magic == optional_header_magic );

        return utils::base_address_t { optional_header };
    }
} // namespace hack::systems::inline memory