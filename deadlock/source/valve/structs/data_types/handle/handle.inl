#pragma once
#include "handle.hpp"

namespace hack::valve::inline data_types {
    _INLINE constexpr void c_handle::set_index( const std::uint32_t index ) {
        m_index = index;
    }

    _INLINE constexpr bool c_handle::is_valid( ) const noexcept {
        return m_index != k_invalid_ehandle_index;
    }

    _INLINE constexpr int c_handle::get_index( ) const noexcept {
        return is_valid( ) ? static_cast< int >( m_index & k_ent_entry_mask ) : 0;
    }

    _INLINE constexpr std::uint32_t c_handle::get_int( ) const noexcept {
        return m_index;
    }

    _INLINE constexpr bool c_handle::operator== ( const c_handle rhs ) const noexcept {
        return m_index == rhs.m_index;
    }

    _INLINE constexpr bool c_handle::operator!= ( const c_handle rhs ) const noexcept {
        return m_index != rhs.m_index;
    }
} // namespace hack::valve::inline data_types