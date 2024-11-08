#pragma once
#include "base_address.hpp"

namespace hack::utils::inline memory {
    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type >::c_base_address( const_reference_type address ) noexcept : m_address { address } { }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    template < typename pointer_type >
        requires std::is_pointer_v< pointer_type >
    constexpr c_base_address< address_type >::c_base_address( pointer_type pointer ) noexcept :
        m_address { reinterpret_cast< const_value_type >( pointer ) } { }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > &c_base_address< address_type >::operator= ( const_reference_type address ) noexcept {
        this->m_address = address;

        return *this;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > &c_base_address< address_type >::operator= ( const void *const address ) noexcept {
        this->m_address = reinterpret_cast< const_value_type >( address );

        return *this;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > &c_base_address< address_type >::self_offset( const difference_type value ) noexcept {
        if ( value == 0 )
            return *this;

        _ASSERT( this->m_address && ( value > 0 ? this->m_address + value >= this->m_address : this->m_address + value <= this->m_address )
                 && this->m_address >= 0 );

        this->m_address += value;

        return *this;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > &c_base_address< address_type >::self_dereference( const size_type count ) noexcept {
        if ( count == 0 )
            return *this;

        _ASSERT( this->m_address && this->m_address >= 0 );

        for ( auto i { count }; i > 0 && this->m_address != 0; --i )
            this->m_address = *this->template as< std::add_pointer_t< const_value_type > >( );

        return *this;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > c_base_address< address_type >::offset( const difference_type value ) const noexcept {
        return c_base_address { *this }.self_offset( value );
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > c_base_address< address_type >::dereference( const size_type count ) const noexcept {
        return c_base_address { *this }.self_dereference( count );
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type > c_base_address< address_type >::relative( const difference_type offset ) noexcept {
        if ( offset == 0 )
            return *this;

        _ASSERT( this->m_address && this->m_address >= 0 );

        const std::int32_t relative_address = *this->offset( offset ).template as< std::add_pointer_t< const_value_type > >( );

        return c_base_address { this->offset( relative_address + sizeof( int ) + offset ) };
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    template < typename pointer_type >
        requires std::is_pointer_v< pointer_type >
    constexpr pointer_type c_base_address< address_type >::as( ) const noexcept {
        return reinterpret_cast< pointer_type >( this->m_address );
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr bool c_base_address< address_type >::operator!( ) const noexcept {
        return this->m_address == 0;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr bool c_base_address< address_type >::operator== ( std::nullptr_t ) const noexcept {
        return this->m_address == 0;
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    template < typename compare_type >
    constexpr bool c_base_address< address_type >::operator== ( const compare_type &other ) const noexcept {
        if constexpr ( std::is_pointer_v< compare_type > ) {
            return this->m_address == reinterpret_cast< const_value_type >( other );
        } else
            return this->m_address == static_cast< const_value_type >( other );
    }

    template < typename address_type >
        requires std::unsigned_integral< address_type >
    constexpr c_base_address< address_type >::operator std::conditional_t<
        std::is_const_v< address_type >, std::remove_const_t< address_type >, address_type > ( ) const noexcept {
        return this->m_address;
    }

} // namespace hack::utils::inline memory