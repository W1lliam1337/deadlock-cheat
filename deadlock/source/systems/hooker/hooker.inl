#pragma once
#include "hooker.hpp"

namespace hack::systems {
    _INLINE hook_t::hook_t( void *table, void *hook_func ) noexcept : m_table( table ), m_hook_func( hook_func ) {
        if ( m_table && m_hook_func )
            ( void ) MH_CreateHook( m_table, m_hook_func, reinterpret_cast< void ** >( &m_original_func ) );
    }

    _INLINE void hook_t::hook( void *replace ) const noexcept {
        if ( MH_EnableHook( m_table ) != MH_OK )
            return;
    }

    _INLINE void hook_t::unhook( ) const noexcept {
        if ( MH_DisableHook( m_table ) != MH_OK )
            return;
    }

    _INLINE hook_manager_t::hook_manager_t( ) noexcept {
        MH_Initialize( );
    }

    _INLINE hook_manager_t::~hook_manager_t( ) noexcept {
        MH_Uninitialize( );
    }

    _INLINE void hook_manager_t::add_hook( const std::size_t token, void *table, void *hook_func ) noexcept {
        if ( m_hook_map.contains( token ) )
            return;

        m_hook_map[ token ] = hook_t( table, hook_func );
        m_hook_map[ token ].hook( hook_func );
    }

    _INLINE void hook_manager_t::remove_hook( const std::size_t token ) noexcept {
        if ( const auto it { m_hook_map.find( token ) }; it != m_hook_map.end( ) ) {
            it->second.unhook( );
            m_hook_map.erase( it );
        }
    }

    _INLINE hook_t *hook_manager_t::get_hook( const std::size_t token ) noexcept {
        const auto it { m_hook_map.find( token ) };
        return it != m_hook_map.end( ) ? &it->second : nullptr;
    }

    template < typename fn_t >
    _INLINE fn_t hook_t::get_original( ) const noexcept {
        return reinterpret_cast< fn_t >( m_original_func );
    }

    template < typename fn_t >
    fn_t hook_impl( const std::size_t token, void *table, void *func ) {
        // If the hook does not exist, add it
        if ( g_hook_manager->get_hook( token ) == nullptr ) {
            g_hook_manager->add_hook( token, table, func );
        }

        // Retrieve the hook and apply it
        const auto &hook { *g_hook_manager->get_hook( token ) };
        return hook.get_original< fn_t >( );
    }
} // namespace hack::systems