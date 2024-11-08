#pragma once
#include "vendor.hpp"

namespace hack::valve {
    inline namespace entities {
        struct entity_t;
    } // namespace entities

    inline namespace data_types {
        static inline constexpr std::uint32_t k_ent_entry_mask { 0x7fffu }, k_invalid_ehandle_index { 0xffffffffu };
        static inline constexpr auto          k_max_edicts { 16384 };

        class c_handle {
            std::uint32_t m_index { };

          public:
            constexpr c_handle( ) noexcept : m_index( k_invalid_ehandle_index ) { }

            explicit constexpr c_handle( const std::uint32_t index ) noexcept : m_index( index ) { }

            /**
             * @brief Retrieves the index of the c_handle.
             *
             * This method retrieves the index of the c_handle.
             *
             * @return The index of the c_handle.
             */
            _INLINE constexpr void set_index( const std::uint32_t index );

            /**
             * @brief Checks if the c_handle is valid.
             *
             * This method checks if the c_handle is valid.
             *
             * @return true if the c_handle is valid, false otherwise.
             */
            [[nodiscard]] _INLINE constexpr bool is_valid( ) const noexcept;

            /**
             * @brief Retrieves the index of the c_handle.
             *
             * This method retrieves the index of the c_handle.
             *
             * @return The index of the c_handle.
             */
            [[nodiscard]] _INLINE constexpr int get_index( ) const noexcept;

            /**
             * @brief Equality operator for c_handle.
             *
             * This method checks for equality between two c_handle objects.
             *
             * @param rhs The right-hand side c_handle object to compare.
             * @return true if the c_handle objects are equal, false otherwise.
             */
            [[nodiscard]] _INLINE constexpr bool operator== ( const c_handle rhs ) const noexcept;

            /**
             * @brief Inequality operator for c_handle.
             *
             * This method checks for inequality between two c_handle objects.
             *
             * @param rhs The right-hand side c_handle object to compare.
             * @return true if the c_handle objects are not equal, false otherwise.
             */
            [[nodiscard]] _INLINE constexpr bool operator!= ( const c_handle rhs ) const noexcept;

            /**
             * @brief Retrieves the integer value of the c_handle.
             *
             * This method retrieves the integer value of the c_handle.
             *
             * @return The integer value of the c_handle.
             */
            [[nodiscard]] _INLINE constexpr std::uint32_t get_int( ) const noexcept;
        };
    } // namespace data_types
} // namespace hack::valve

#include "handle.inl"