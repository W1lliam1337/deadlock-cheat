#pragma once
#include "utils/hash/hash.hpp"
#include "valve/interfaces/schema_system/schema_system.hpp"
#include "vendor.hpp"

#define NET_VAR_OFFSET( datatable, prop_name, add_offset, type )                                                \
    [[nodiscard]] _INLINE std::add_lvalue_reference_t< std::add_const_t< type > > prop_name( ) const noexcept { \
        static const auto class_hashed { _HASH( ( datatable ) ) };                                              \
        static const auto delimiter_hashed { _HASH( ( "->" ), class_hashed ) };                                 \
        static const auto field_hashed { _HASH( ( #prop_name ), delimiter_hashed ) };                           \
        static const auto offset { ::hack::valve::g_net_vars->get_offset( field_hashed ) };                     \
        return *::hack::utils::base_address_t { this }                                                          \
                    .offset( static_cast< std::ptrdiff_t >( offset + ( add_offset ) ) )                         \
                    .as< std::add_pointer_t< std::add_const_t< type > > >( );                                   \
    }

#define NET_VAR_OFFSET_NON_CONST( datatable, prop_name, add_offset, type )                  \
    [[nodiscard]] _INLINE std::add_lvalue_reference_t< type > prop_name( ) const noexcept { \
        static const auto class_hashed { _HASH( ( datatable ) ) };                          \
        static const auto delimiter_hashed { _HASH( ( "->" ), class_hashed ) };             \
        static const auto field_hashed { _HASH( ( #prop_name ), delimiter_hashed ) };       \
        static const auto offset { ::hack::valve::g_net_vars->get_offset( field_hashed ) }; \
        return *::hack::utils::base_address_t { this }                                      \
                    .offset( static_cast< std::ptrdiff_t >( offset + ( add_offset ) ) )     \
                    .as< std::add_pointer_t< type > >( );                                   \
    }

#define NET_VAR( datatable, prop_name, type )    NET_VAR_OFFSET( datatable, prop_name, 0, type )
#define NET_VAR_EX( datatable, prop_name, type ) NET_VAR_OFFSET_NON_CONST( datatable, prop_name, 0, type )

namespace hack::valve {
    /**
     * @brief Manages network variable offsets and caching for efficient retrieval.
     */
    struct net_vars_t {
        /**
         * @brief Constructs a net_vars_t object, initializing and caching network variable offsets.
         *
         * @details Scans through available classes and fields within the "client.dll" type scope to
         *          populate a cache of hashed property keys and their offsets.
         */
        _INLINE net_vars_t( ) noexcept;

        /**
         * @brief Destroys the net_vars_t object, clearing the cached offset data.
         */
        _INLINE ~net_vars_t( ) noexcept;

        /**
         * @brief Retrieves the offset for a specified property key.
         *
         * @param property_key A hashed key representing the network variable property.
         * @return The offset of the network variable if found; otherwise, returns 0.
         */
        [[nodiscard]] static _INLINE std::uint32_t get_offset( const std::size_t property_key ) noexcept;

      private:
        /// A cache of property keys mapped to their corresponding offsets for quick lookup.
        inline static std::unordered_map< std::size_t, std::uint32_t > m_cache { };
    };

    inline std::unique_ptr< net_vars_t > g_net_vars { };
} // namespace hack::valve

#include "net_vars.inl"