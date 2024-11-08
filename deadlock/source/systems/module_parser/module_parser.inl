#pragma once
#include "module_parser.hpp"

namespace hack::systems::inline memory {
    _INLINE _CONSTRUCTOR module_parser_t::module_parser_t( ) noexcept {
        _ASSERT( this->parse_modules( ) );
    }

    _INLINE std::shared_ptr< ldr_module_t > module_parser_t::get_module( const std::size_t hash ) const noexcept {
        const auto iterator { this->m_modules_list.find( hash ) };

        if ( iterator == this->m_modules_list.cend( ) )
            return nullptr;

        return iterator->second;
    }

    _INLINE const utils::teb *module_parser_t::get_current_teb( ) noexcept {
        utils::teb *current_teb { };

        asm volatile( "mov %%gs:0x30, %0"
                      : "=r"( current_teb ) );

        return current_teb;
    }

    /// Default parser (g_module_parser) for functions
    inline constexpr auto &default_parser { systems::g_module_parser };

    /**
     * @brief Retrieves the pattern address from the specified module.
     *
     * This function uses the provided module name and pattern to search for the pattern.
     * Optionally, you can provide an offset to modify the found address.
     *
     * @param module_name The name of the module to search within.
     * @param pattern The pattern to search for in the module.
     * @param offset The optional offset to add to the found pattern (default is 0).
     * @param dereference Whether to dereference the pattern address (default is false).
     * @return The address of the found pattern, potentially adjusted by the offset.
     */
    template < typename T = utils::base_address_t >
    constexpr std::add_const_t< T > get_pattern( const std::string_view module_name, const std::string_view pattern,
                                                 const std::uint8_t offset = 0, const bool dereference = false ) noexcept {
        const auto module { default_parser->get_module( _HASH( module_name ) ) };
        auto       pattern_addr { module->find_pattern( pattern ) };

        if ( offset != 0 )
            pattern_addr = pattern_addr.relative( offset );

        if ( dereference )
            return pattern_addr.dereference( ).as< std::add_const_t< T > >( );

        return pattern_addr.as< std::add_const_t< T > >( );
    }

    /**
     * @brief Retrieves the export address from the specified module.
     *
     * @param module_name The name of the module.
     * @param export_name The name of the export.
     * @return The address of the export.
     */
    template < typename T >
    constexpr std::add_const_t< T > get_export( const std::string_view module_name, const std::string_view export_name ) noexcept {
        return default_parser->get_module( _HASH( module_name ) )
            ->get_export_address( export_name )
            .template as< std::add_const_t< T > >( );
    }

    /**
     * @brief Retrieves the interface address from the specified module.
     *
     * @param module_name The name of the module.
     * @param interface_name The name of the interface.
     * @return The address of the interface.
     */
    template < typename T >
    constexpr std::add_const_t< T > get_interface( const std::string_view module_name, const std::string_view interface_name ) noexcept {
        return default_parser->get_module( _HASH( module_name ) )
            ->find_interface( interface_name )
            .template as< std::add_const_t< T > >( );
    }

} // namespace hack::systems::inline memory