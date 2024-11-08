#pragma once
#include "net_vars.hpp"

namespace hack::valve {
    _INLINE net_vars_t::net_vars_t( ) noexcept {
        const auto type_scope { g_schema_system->find_type_scope( "client.dll" ) };
        if ( !type_scope )
            return;

        auto      &binding_table { type_scope->get_bindings_table( ) };
        const auto elements { std::make_unique_for_overwrite< utl_ts_hash_handle_t[] >( binding_table.count( ) ) };
        const auto elements_count { binding_table.get_elements( 0, binding_table.count( ), elements.get( ) ) };

        for ( int i { }; i < elements_count; i++ ) {
            const auto element { elements[ i ] };
            if ( !element )
                continue;

            const auto class_binding { binding_table.element( element ) };
            if ( !class_binding )
                continue;

            const auto class_hashed { _HASH( class_binding->m_name ) };
            const auto delimiter_hashed { _HASH( "->", class_hashed ) };
            for ( int j { }; j < class_binding->m_fields_count; j++ ) {
                auto      &schema_field { class_binding->m_fields[ j ] };
                const auto field_hashed { _HASH( schema_field.m_name, delimiter_hashed ) };

                m_cache.try_emplace( field_hashed, schema_field.m_offset );
            }
        }
    }

    net_vars_t::~net_vars_t( ) noexcept {
        m_cache.clear( );
    }

    _INLINE std::uint32_t net_vars_t::get_offset( const std::size_t property_key ) noexcept {
        const auto &offset { m_cache.find( property_key ) };
        return offset == m_cache.end( ) ? 0 : offset->second;
    }
} // namespace hack::valve