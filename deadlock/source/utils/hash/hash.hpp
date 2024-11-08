#pragma once

#include "vendor.hpp"

#define _HASH \
    ::hack::utils::c_string_hash< std::string_view > { }

namespace hack::utils {
    template < typename string_type >
        requires is_any_of< string_type, char, wchar_t, std::string, std::wstring, std::string_view, std::wstring_view >
    class c_string_hash {
      public:
        using basic_string
            = std::conditional_t< is_any_of< string_type, char, wchar_t >, std::basic_string_view< const string_type >, const string_type >;

        _INLINE constexpr std::size_t operator( ) ( const basic_string &string, std::size_t basis = m_basis ) const noexcept {
            for ( const auto &character : string )
                basis = ( basis ^ static_cast< std::uint8_t >( character ) ) * m_prime;

            return basis;
        }

      private:
        static constexpr auto m_prime { 0x100000001B3 };
        static constexpr auto m_basis { 0xCBF29CE484222325 };
    };

    namespace literals {
        _INLINE constexpr std::size_t operator""_hash ( const char *const string, [[maybe_unused]] const std::size_t length ) noexcept {
            return c_string_hash< char > { }( string );
        }

        _INLINE constexpr std::size_t operator""_hash ( const wchar_t *const string, [[maybe_unused]] const std::size_t length ) noexcept {
            return c_string_hash< wchar_t > { }( string );
        }
    } // namespace literals
} // namespace hack::utils