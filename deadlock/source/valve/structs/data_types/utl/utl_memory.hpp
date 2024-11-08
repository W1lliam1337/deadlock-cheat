#pragma once
#include "valve/interfaces/mem_alloc/mem_alloc.hpp"
#include "vendor.hpp"

namespace hack::valve::inline data_types {
    template < typename t_memory, typename... t_args >
    _INLINE t_memory *construct( t_memory *p_memory, t_args... arg_list ) {
        return ::new ( p_memory ) t_memory { arg_list... };
    }

    template < typename t_memory >
    _INLINE t_memory *copy_construct( t_memory *p_memory, const t_memory &copy_memory ) {
        return ::new ( p_memory ) t_memory { copy_memory };
    }

    template < typename t_memory >
    _INLINE t_memory *move_construct( t_memory *p_memory, t_memory &&move_memory ) {
        return ::new ( p_memory ) t_memory { std::forward< t_memory >( move_memory ) };
    }

    template < typename t_memory >
    _INLINE void destruct( t_memory *p_memory ) {
        p_memory->~t_memory( );
    }

    template < typename t_element, typename t_index = int >
    class utl_memory_t {
      public:
        explicit utl_memory_t( int grow_size = 0, int init_size = 0 ) noexcept;
        utl_memory_t( t_element *p_memory, int num_elements ) noexcept;
        utl_memory_t( const t_element *p_memory, int num_elements ) noexcept;
        ~utl_memory_t( ) noexcept;

        utl_memory_t( const utl_memory_t & )             = delete;
        utl_memory_t &operator= ( const utl_memory_t & ) = delete;

        utl_memory_t( utl_memory_t &&utl_memory ) noexcept;
        utl_memory_t &operator= ( utl_memory_t &&utl_memory ) noexcept;

        void init( int grow_size, int init_size = 0 ) noexcept;

        struct iterator_t {
            constexpr explicit iterator_t( t_index index ) noexcept : i_index( index ) { }

            t_index i_index;

            [[nodiscard]] constexpr bool operator== ( const iterator_t it ) const noexcept {
                return i_index == it.i_index;
            }

            [[nodiscard]] constexpr bool operator!= ( const iterator_t it ) const noexcept {
                return i_index != it.i_index;
            }
        };

        [[nodiscard]] _INLINE iterator_t first( ) const noexcept;

        [[nodiscard]] _INLINE iterator_t next( const iterator_t &it ) const noexcept;

        [[nodiscard]] static _INLINE t_index get_index( const iterator_t &it ) noexcept;

        [[nodiscard]] static _INLINE constexpr bool is_index_after( t_index index, const iterator_t &it ) noexcept;

        [[nodiscard]] _INLINE bool is_valid_iterator( const iterator_t &it ) const noexcept {
            return is_index_valid( it.i_index );
        }

        [[nodiscard]] static _INLINE constexpr iterator_t invalid_iterator( ) noexcept;

        [[nodiscard]] t_element       &operator[] ( t_index index ) noexcept;
        [[nodiscard]] const t_element &operator[] ( t_index index ) const noexcept;

        [[nodiscard]] t_element       &element( t_index index ) noexcept;
        [[nodiscard]] const t_element &element( t_index index ) const noexcept;

        [[nodiscard]] bool is_index_valid( t_index index ) const noexcept;

        void swap( utl_memory_t< t_element, t_index > &utl_memory ) noexcept;

        void convert_to_growable_memory( int grow_size ) noexcept;

        [[nodiscard]] int num_allocated( ) const noexcept;
        [[nodiscard]] int count( ) const noexcept;

        void grow( int num = 1 ) noexcept;

        void ensure_capacity( int num ) noexcept;

        void purge( ) noexcept;
        void purge( int num_elements ) noexcept;

        [[nodiscard]] bool is_externally_allocated( ) const noexcept;
        [[nodiscard]] bool is_read_only( ) const noexcept;

        void set_grow_size( int size ) noexcept;

        static inline constexpr t_index m_invalid_index = static_cast< t_index >( -1 );

        [[nodiscard]] static _INLINE consteval t_index invalid_index( ) noexcept;

        [[nodiscard]] t_element       *base( ) noexcept;
        [[nodiscard]] const t_element *base( ) const noexcept;

        void                     set_external_buffer( t_element *p_memory, int num_elements ) noexcept;
        void                     set_external_buffer( const t_element *p_memory, int num_elements ) noexcept;
        void                     assume_memory( t_element *p_memory, int size ) noexcept;
        [[nodiscard]] t_element *detach( ) noexcept;
        [[nodiscard]] void      *detach_memory( ) noexcept;

      private:
        static inline constexpr int external_buffer_marker       = -1;
        static inline constexpr int external_const_buffer_marker = -2;

        t_element *m_memory { };
        int        m_allocation_count { };
        int        m_grow_size { };
    };

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::init( const int grow_size, const int init_size ) noexcept {
        purge( );

        m_grow_size        = grow_size;
        m_allocation_count = init_size;

        if ( m_allocation_count )
            m_memory = static_cast< t_element * >( g_alloc_func( m_allocation_count * sizeof( t_element ) ) );
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::swap( utl_memory_t< t_element, t_index > &utl_memory ) noexcept {
        std::swap( m_grow_size, utl_memory.m_grow_size );
        std::swap( m_memory, utl_memory.m_memory );
        std::swap( m_allocation_count, utl_memory.m_allocation_count );
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::convert_to_growable_memory( const int grow_size ) noexcept {
        if ( !is_externally_allocated( ) )
            return;

        m_grow_size = grow_size;
        if ( m_allocation_count ) {
            int        num_bytes = m_allocation_count * sizeof( t_element );
            t_element *p_memory  = static_cast< t_element  *>( g_alloc_func( num_bytes ) );
            std::memcpy( p_memory, m_memory, num_bytes );
            m_memory = p_memory;
        } else
            m_memory = nullptr;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::set_external_buffer( t_element *p_memory, const int num_elements ) noexcept {
        purge( );

        m_memory           = p_memory;
        m_allocation_count = num_elements;

        m_grow_size = external_buffer_marker;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::set_external_buffer( const t_element *p_memory, const int num_elements ) noexcept {
        purge( );

        m_memory           = p_memory;
        m_allocation_count = num_elements;

        m_grow_size = external_const_buffer_marker;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::assume_memory( t_element *p_memory, const int size ) noexcept {
        purge( );

        m_memory           = p_memory;
        m_allocation_count = size;
    }

    template < typename t_element, typename t_index >
    void *utl_memory_t< t_element, t_index >::detach_memory( ) noexcept {
        if ( is_externally_allocated( ) )
            return nullptr;

        void *p_memory     = m_memory;
        m_memory           = nullptr;
        m_allocation_count = 0;
        return p_memory;
    }

    template < typename t_element, typename t_index >
    t_element *utl_memory_t< t_element, t_index >::detach( ) noexcept {
        return static_cast< t_element * >( detach_memory( ) );
    }

    template < typename t_element, typename t_index >
    t_element &utl_memory_t< t_element, t_index >::operator[] ( t_index index ) noexcept {
        return m_memory[ index ];
    }

    template < typename t_element, typename t_index >
    const t_element &utl_memory_t< t_element, t_index >::operator[] ( t_index index ) const noexcept {
        return m_memory[ index ];
    }

    template < typename t_element, typename t_index >
    t_element &utl_memory_t< t_element, t_index >::element( t_index index ) noexcept {
        return m_memory[ index ];
    }

    template < typename t_element, typename t_index >
    const t_element &utl_memory_t< t_element, t_index >::element( t_index index ) const noexcept {
        return m_memory[ index ];
    }

    template < typename t_element, typename t_index >
    bool utl_memory_t< t_element, t_index >::is_externally_allocated( ) const noexcept {
        return ( m_grow_size < 0 );
    }

    template < typename t_element, typename t_index >
    bool utl_memory_t< t_element, t_index >::is_read_only( ) const noexcept {
        return ( m_grow_size == external_const_buffer_marker );
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::set_grow_size( const int size ) noexcept {
        m_grow_size = size;
    }

    template < typename t_element, typename t_index >
    t_element *utl_memory_t< t_element, t_index >::base( ) noexcept {
        return m_memory;
    }

    template < typename t_element, typename t_index >
    const t_element *utl_memory_t< t_element, t_index >::base( ) const noexcept {
        return m_memory;
    }

    template < typename t_element, typename t_index >
    int utl_memory_t< t_element, t_index >::num_allocated( ) const noexcept {
        return m_allocation_count;
    }

    template < typename t_element, typename t_index >
    int utl_memory_t< t_element, t_index >::count( ) const noexcept {
        return m_allocation_count;
    }

    template < typename t_element, typename t_index >
    bool utl_memory_t< t_element, t_index >::is_index_valid( t_index index ) const noexcept {
        return ( index >= 0 ) && ( index < m_allocation_count );
    }

    _INLINE constexpr int utl_memory_calc_new_allocation_count( int allocation_count, const int grow_size, const int new_size,
                                                                const int bytes_item ) noexcept {
        if ( grow_size )
            allocation_count = ( ( 1 + ( ( new_size - 1 ) / grow_size ) ) * grow_size );
        else {
            if ( !allocation_count ) {
                allocation_count = ( 31 + bytes_item ) / bytes_item;

                if ( allocation_count < new_size )
                    allocation_count = new_size;
            }

            while ( allocation_count < new_size )
                allocation_count *= 2;
        }

        return allocation_count;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::grow( const int num ) noexcept {
        if ( is_externally_allocated( ) )
            return;

        int allocation_requested = m_allocation_count + num;
        int new_allocation_count
            = utl_memory_calc_new_allocation_count( m_allocation_count, m_grow_size, allocation_requested, sizeof( t_element ) );

        if ( static_cast< int >( static_cast< t_index >( new_allocation_count ) ) < allocation_requested ) {
            if ( static_cast< int >( static_cast< t_index >( new_allocation_count ) ) == 0
                 && static_cast< int >( static_cast< t_index >( new_allocation_count - 1 ) ) >= allocation_requested )
                --new_allocation_count;
            else {
                if ( static_cast< int >( static_cast< t_index >( allocation_requested ) != allocation_requested ) )
                    return;
                while ( static_cast< int >( static_cast< t_index >( new_allocation_count ) ) < allocation_requested )
                    new_allocation_count = ( new_allocation_count + allocation_requested ) / 2;
            }
        }

        m_memory = static_cast< t_element * >( g_realloc_func( m_memory, new_allocation_count * sizeof( t_element ) ) );

        m_allocation_count = new_allocation_count;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::ensure_capacity( const int num ) noexcept {
        if ( m_allocation_count >= num )
            return;

        if ( is_externally_allocated( ) )
            return;

        m_memory = static_cast< t_element * >( realloc_func( m_memory, num * sizeof( t_element ) ) );

        m_allocation_count = num;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::purge( ) noexcept {
        if ( is_externally_allocated( ) )
            return;

        if ( m_memory ) {
            mem_alloc_free_func( m_memory );
            m_memory = nullptr;
        }

        m_allocation_count = 0;
    }

    template < typename t_element, typename t_index >
    void utl_memory_t< t_element, t_index >::purge( const int num_elements ) noexcept {
        if ( num_elements >= m_allocation_count )
            return;

        if ( num_elements == 0 )
            return purge( );

        if ( is_externally_allocated( ) )
            return;

        if ( !m_memory )
            return;

        m_memory           = static_cast< t_element           *>( mem_alloc_realloc_func( m_memory, num_elements * sizeof( t_element ) ) );
        m_allocation_count = num_elements;
    }
} // namespace hack::valve::inline data_types

#include "utl_memory.inl"