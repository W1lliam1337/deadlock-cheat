#pragma once
#include "schema_system.hpp"

namespace hack::valve::inline interfaces {
    struct class_info_t;

    struct system_type_scope_t {
        system_type_scope_t( )                             = delete;
        system_type_scope_t( system_type_scope_t && )      = delete;
        system_type_scope_t( const system_type_scope_t & ) = delete;

        _VFUNC( class_info_t *, find_decl_class( const char *class_name ), 2, this, class_name )

        _OFFSET( 0x8, get_name, char[ 256 ] )
        _OFFSET( 0x500, get_bindings_table, utl_ts_hash_t< class_info_data_t *, 256 > )
    };

    struct schema_system_t {
        schema_system_t( )                         = delete;
        schema_system_t( schema_system_t && )      = delete;
        schema_system_t( const schema_system_t & ) = delete;

        _VFUNC( system_type_scope_t *, find_type_scope( const char *name, std::uint64_t *unk = nullptr ), 13, this, name, nullptr )
    };

    inline auto g_schema_system = systems::get_interface< schema_system_t * >( "schemasystem.dll", "SchemaSystem_001" );
} // namespace hack::valve::inline interfaces
