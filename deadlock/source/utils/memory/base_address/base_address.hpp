#pragma once

#include "vendor.hpp"

namespace hack::utils::inline memory {
    /**
     * @class c_base_address
     * @brief A generic address manipulation class that operates on unsigned integral types.
     *
     * This class provides utilities for performing various pointer operations such as offsetting,
     * dereferencing, and type-casting for low-level memory manipulation.
     *
     * @tparam address_type The underlying address type, constrained to unsigned integral types.
     */
    template < typename address_type = std::uintptr_t >
        requires std::unsigned_integral< address_type >
    class c_base_address {
      public:
        /// Type representing a non-constant address.
        using value_type = std::conditional_t< std::is_const_v< address_type >, std::remove_const_t< address_type >, address_type >;

        /// Type representing a constant address.
        using const_value_type = std::conditional_t< std::is_const_v< address_type >, address_type, std::add_const_t< address_type > >;

        /// Reference type for non-constant address.
        using reference_type = std::add_lvalue_reference_t< value_type >;

        /// Reference type for constant address.
        using const_reference_type = std::add_lvalue_reference_t< const_value_type >;

        /// Type for size-related values.
        using size_type = std::size_t;

        /// Type for difference or offset values.
        using difference_type = std::ptrdiff_t;

        /**
         * @brief Default constructor initializing an empty address.
         */
        _INLINE constexpr c_base_address( ) noexcept = default;

        /**
         * @brief Constructs a base address with a specific address value.
         *
         * @param address The address to initialize.
         */
        _INLINE constexpr explicit c_base_address( const_reference_type address ) noexcept;

        /**
         * @brief Constructs a base address from a pointer.
         *
         * @tparam pointer_type The pointer type being cast to the address type.
         * @param pointer A pointer representing the address.
         */
        template < typename pointer_type = std::add_pointer< std::uint8_t > >
            requires std::is_pointer_v< pointer_type >
        _INLINE constexpr explicit c_base_address( pointer_type pointer ) noexcept;

        /**
         * @brief Assigns a new address to the current object.
         *
         * @param address The address to assign.
         * @return Reference to the current object.
         */
        _INLINE constexpr c_base_address &operator= ( const_reference_type address ) noexcept;

        /**
         * @brief Assigns an address from a void pointer.
         *
         * @param address A void pointer representing the new address.
         * @return Reference to the current object.
         */
        _INLINE constexpr c_base_address &operator= ( const void *const address ) noexcept;

        /**
         * @brief Offsets the current address by a specified value.
         *
         * @param value The offset to apply.
         * @return Reference to the current object.
         */
        _INLINE constexpr c_base_address &self_offset( const difference_type value ) noexcept;

        /**
         * @brief Dereferences the current address a specified number of times.
         *
         * @param count The number of times to dereference.
         * @return Reference to the current object.
         */
        _INLINE constexpr c_base_address &self_dereference( const size_type count = 1 ) noexcept;

        /**
         * @brief Returns a new address offset by a specified value.
         *
         * @param value The offset to apply.
         * @return A new c_base_address with the offset applied.
         */
        [[nodiscard]] _INLINE constexpr c_base_address offset( const difference_type value ) const noexcept;

        /**
         * @brief Returns a new address after dereferencing a specified number of times.
         *
         * @param count The number of times to dereference.
         * @return A new c_base_address with the dereferenced value.
         */
        [[nodiscard]] _INLINE constexpr c_base_address dereference( const size_type count = 1 ) const noexcept;

        /**
         * @brief Returns a relative address based on an offset.
         *
         * @param offset The offset for relative addressing.
         * @return A new c_base_address representing the relative address.
         */
        [[nodiscard]] _INLINE constexpr c_base_address relative( const difference_type offset ) noexcept;

        /**
         * @brief Casts the current address to a specified pointer type.
         *
         * @tparam pointer_type The type of pointer to cast to.
         * @return The address as the specified pointer type.
         */
        template < typename pointer_type = std::add_pointer_t< std::uint8_t > >
            requires std::is_pointer_v< pointer_type >
        [[nodiscard]] _INLINE constexpr pointer_type as( ) const noexcept;

        /**
         * @brief Compares two c_base_address objects.
         *
         * @param other The address to compare with.
         * @return Comparison result.
         */
        [[nodiscard]] _INLINE constexpr auto operator<=> ( const c_base_address &other ) const noexcept = default;

        /**
         * @brief Checks if the address is null.
         *
         * @return True if address is null, otherwise false.
         */
        [[nodiscard]] _INLINE constexpr bool operator!( ) const noexcept;

        /**
         * @brief Checks if the address is equal to nullptr.
         *
         * @return True if the address is nullptr, otherwise false.
         */
        [[nodiscard]] _INLINE constexpr bool operator== ( std::nullptr_t ) const noexcept;

        /**
         * @brief Checks if the address is equal to a specified value.
         *
         * @tparam compare_type The type of value to compare with.
         * @param other The value to compare.
         * @return True if addresses are equal, otherwise false.
         */
        template < typename compare_type = const_value_type >
        [[nodiscard]] _INLINE constexpr bool operator== ( const compare_type &other ) const noexcept;

        /**
         * @brief Converts the address to its underlying value type.
         *
         * @return The address as value_type.
         */
        [[nodiscard]] _INLINE constexpr explicit operator value_type ( ) const noexcept;

      protected:
        /// The underlying address value.
        address_type m_address { };
    };

    /// Alias for `c_base_address` using `std::uintptr_t` as the address type.
    using base_address_t = c_base_address< std::uintptr_t >;
} // namespace hack::utils::inline memory

#include "base_address.inl"