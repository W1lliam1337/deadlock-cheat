#pragma once
#include "base_address/base_address.hpp"

#define _OFFSET( add_offset, var, treturn, ... )                                                                                       \
    [[nodiscard]] _INLINE std::add_lvalue_reference_t< treturn __VA_OPT__(, ) __VA_ARGS__ > var( ) const noexcept {                    \
        return *utils::base_address_t { this }.offset( add_offset ).as< std::add_pointer_t< treturn __VA_OPT__(, ) __VA_ARGS__ > >( ); \
    }

#define _VFUNC( ret_type, name, index, ... )                               \
    [[nodiscard]] _INLINE constexpr auto name const noexcept {             \
        return hack::utils::get_virtual< ret_type >( index, __VA_ARGS__ ); \
    }

namespace hack::utils::inline memory {
    /**
     * Retrieves the function pointer at the specified index in the virtual function table
     * @tparam T Integral type
     * @param base Base address of the vtable
     * @param args Argument list
     * @param index Index of the function pointer in the vtable
     * @return Function call
     */
    template < typename T, typename... args_t >
    _INLINE T get_virtual( const std::uint32_t index, const void *base, args_t... args ) noexcept {
        const auto vtable { *reinterpret_cast< fastcall_t< T, void *, args_t... > ** >( const_cast< void * >( base ) ) };
        return vtable[ index ]( const_cast< void * >( base ), args... );
    }
} // namespace hack::utils::inline memory