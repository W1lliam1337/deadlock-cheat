#pragma once
#include "utl_memory.hpp"

namespace hack::valve::inline data_types {
    template < typename t_element, typename t_index > typename utl_memory_t< t_element, t_index >::iterator_t
    utl_memory_t< t_element, t_index >::first( ) const noexcept {
        return iterator_t( is_index_valid( 0 ) ? 0 : invalid_index( ) );
    }

    template < typename t_element, typename t_index > typename utl_memory_t< t_element, t_index >::iterator_t
    utl_memory_t< t_element, t_index >::next( const iterator_t& it ) const noexcept {
        return iterator_t( is_index_valid( it.i_index + 1 ) ? it.i_index + 1 : invalid_index( ) );
    }

    template < typename t_element, typename t_index >
    t_index utl_memory_t< t_element, t_index >::get_index( const iterator_t& it ) noexcept {
        return it.i_index;
    }

    template < typename t_element, typename t_index >
    constexpr bool utl_memory_t< t_element, t_index >::is_index_after( t_index index, const iterator_t& it ) noexcept {
        return index > it.i_index;
    }

    template < typename t_element, typename t_index > constexpr typename utl_memory_t< t_element, t_index >::iterator_t
    utl_memory_t< t_element, t_index >::invalid_iterator( ) noexcept {
        return iterator_t( invalid_index( ) );
    }

    template < typename t_element, typename t_index >
    consteval t_index utl_memory_t< t_element, t_index >::invalid_index( ) noexcept {
        return m_invalid_index;
    }

    template < typename t_element, typename t_index >
    utl_memory_t< t_element, t_index >::utl_memory_t( int grow_size, int init_size ) noexcept :
        m_memory( nullptr ),
        m_allocation_count( init_size ),
        m_grow_size( grow_size ) {
        if ( m_allocation_count )
            m_memory = static_cast< t_element* >( mem_alloc.MemAlloc_AllocFunc( m_allocation_count * sizeof( t_element ) ) );
    }

    template < typename t_element, typename t_index >
    utl_memory_t< t_element, t_index >::utl_memory_t( t_element* p_memory, int num_elements ) noexcept :
        m_memory( p_memory ),
        m_allocation_count( num_elements ) {
        m_grow_size = external_buffer_marker;
    }

    template < typename t_element, typename t_index >
    utl_memory_t< t_element, t_index >::utl_memory_t( const t_element* p_memory, int num_elements ) noexcept :
        m_memory( p_memory ),
        m_allocation_count( num_elements ) {
        m_grow_size = external_const_buffer_marker;
    }

    template < typename t_element, typename t_index > utl_memory_t< t_element, t_index >::~utl_memory_t( ) noexcept {
        purge( );
    }

    template < typename t_element, typename t_index >
    utl_memory_t< t_element, t_index >::utl_memory_t( utl_memory_t&& utl_memory ) noexcept :
        m_memory( utl_memory.m_memory ),
        m_allocation_count( utl_memory.m_allocation_count ),
        m_grow_size( utl_memory.m_grow_size ) {
        utl_memory.m_memory = nullptr;
        utl_memory.m_allocation_count = 0;
        utl_memory.m_grow_size = 0;
    }

    template < typename t_element, typename t_index > utl_memory_t< t_element, t_index >&
    utl_memory_t< t_element, t_index >::operator=( utl_memory_t&& utl_memory ) noexcept {
        t_element* p_memory = utl_memory.m_memory;
        const int allocation_count = utl_memory.m_allocation_count;
        const int grow_size = utl_memory.m_grow_size;

        utl_memory.m_memory = nullptr;
        utl_memory.m_allocation_count = 0;
        utl_memory.m_grow_size = 0;

        purge( );

        m_memory = p_memory;
        m_allocation_count = allocation_count;
        m_grow_size = grow_size;

        return *this;
    }
} // namespace hack::cs2::inline data_types
