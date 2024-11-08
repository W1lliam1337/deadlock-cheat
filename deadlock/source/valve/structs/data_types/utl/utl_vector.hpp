#pragma once
#include "utl_memory.hpp"
#include "vendor.hpp"

namespace hack::valve::inline data_types {
    template < typename element_t, class allocator_t = utl_memory_t< element_t > >
    struct utl_vector_t {
        explicit utl_vector_t( int grow_size = 0, int init_capacity = 0 ) noexcept;

        utl_vector_t( element_t *memory, int init_capacity = 0, int init_count = 0 ) noexcept;
        ~utl_vector_t( ) noexcept;

        utl_vector_t( const utl_vector_t< element_t, allocator_t > &utl_vector ) = delete;
        utl_vector_t< element_t, allocator_t > &operator= ( const utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept;

        element_t       &operator[] ( int idx ) noexcept;
        const element_t &operator[] ( int idx ) const noexcept;
        element_t       &element( int idx ) noexcept;
        const element_t &element( int idx ) const noexcept;
        element_t       &head( ) noexcept;
        const element_t &head( ) const noexcept;
        element_t       &tail( ) noexcept;
        const element_t &tail( ) const noexcept;

        element_t *base( ) noexcept {
            return m_memory.base( );
        };

        const element_t *base( ) const noexcept {
            return m_memory.base( );
        };

        [[nodiscard]] int count( ) const;

        [[nodiscard]] inline bool is_empty( ) const noexcept {
            return ( count( ) == 0 );
        }

        bool                 is_valid_index( int idx ) const;
        static constexpr int invalid_index( ) noexcept;

        int add_to_head( ) noexcept;
        int add_to_tail( ) noexcept;
        int insert_before( int idx ) noexcept;
        int insert_after( int idx ) noexcept;

        int add_to_head( const element_t &element ) noexcept;
        int add_to_tail( const element_t &element ) noexcept;
        int insert_before( int idx, const element_t &element ) noexcept;
        int insert_after( int idx, const element_t &element ) noexcept;

        int add_multiple_to_head( int num ) noexcept;
        int add_multiple_to_tail( int num ) noexcept;
        int add_multiple_to_tail( int num, const element_t *elements ) noexcept;
        int insert_multiple_before( int idx, int num ) noexcept;
        int insert_multiple_before( int idx, int num, const element_t *elements ) noexcept;
        int insert_multiple_after( int idx, int num ) noexcept;

        void set_size( int size ) noexcept;
        void set_count( int count ) noexcept;
        void set_count_non_destructively( int count ) noexcept;

        void copy_array( const element_t *elements, int size ) noexcept;

        void swap( utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept;

        int add_vector_to_tail( const utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept;

        int  find( const element_t &element ) const noexcept;
        bool has_element( const element_t &element ) const noexcept;

        void ensure_capacity( int num ) noexcept;

        void fast_remove( int idx ) noexcept;
        void remove( int idx ) noexcept;
        bool find_and_remove( const element_t &element ) noexcept;
        bool find_and_fast_remove( const element_t &element ) noexcept;
        void remove_multiple( int idx, int num ) noexcept;
        void remove_multiple_from_head( int num ) noexcept;
        void remove_multiple_from_tail( int num ) noexcept;
        void remove_all( ) noexcept;

        void purge( ) noexcept;
        void purge_and_delete_elements( ) noexcept;

        void compact( ) noexcept;

        void set_grow_size( int size ) noexcept {
            m_memory.set_grow_size( size );
        }

        int num_allocated( ) const noexcept;

        void reverse( ) noexcept;

      protected:
        void grow_vector( int num = 1 ) noexcept;

        void shift_elements_right( int idx, int num = 1 ) noexcept;
        void shift_elements_left( int idx, int num = 1 ) noexcept;

        std::int32_t m_size { };
        _PAD( 4 )
        allocator_t m_memory { };
        _PAD( 8 )
    };

    template < typename element_t, class allocator_t >
    utl_vector_t< element_t, allocator_t >::utl_vector_t( int grow_size, int init_capacity ) noexcept :
        m_size( 0 ),
        m_memory( grow_size, init_capacity ) { }

    template < typename element_t, class allocator_t >
    utl_vector_t< element_t, allocator_t >::utl_vector_t( element_t *memory, int init_capacity, int init_count ) noexcept :
        m_size( init_count ),
        m_memory( memory, init_capacity ) { }

    template < typename element_t, class allocator_t >
    utl_vector_t< element_t, allocator_t >::~utl_vector_t( ) noexcept {
        purge( );
    }

    template < typename element_t, class allocator_t >
    utl_vector_t< element_t, allocator_t > &
        utl_vector_t< element_t, allocator_t >::operator= ( const utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept {
        int count = utl_vector.count( );
        set_size( count );
        for ( int idx = 0; idx < count; idx++ )
            ( *this )[ idx ] = utl_vector[ idx ];

        return *this;
    }

    template < typename element_t, class allocator_t >
    element_t &utl_vector_t< element_t, allocator_t >::operator[] ( int idx ) noexcept {
        return m_memory[ idx ];
    }

    template < typename element_t, class allocator_t >
    const element_t &utl_vector_t< element_t, allocator_t >::operator[] ( int idx ) const noexcept {
        return m_memory[ idx ];
    }

    template < typename element_t, class allocator_t >
    element_t &utl_vector_t< element_t, allocator_t >::element( int idx ) noexcept {
        return m_memory[ idx ];
    }

    template < typename element_t, class allocator_t >
    const element_t &utl_vector_t< element_t, allocator_t >::element( int idx ) const noexcept {
        return m_memory[ idx ];
    }

    template < typename element_t, class allocator_t >
    element_t &utl_vector_t< element_t, allocator_t >::head( ) noexcept {
        return m_memory[ 0 ];
    }

    template < typename element_t, class allocator_t >
    const element_t &utl_vector_t< element_t, allocator_t >::head( ) const noexcept {
        return m_memory[ 0 ];
    }

    template < typename element_t, class allocator_t >
    element_t &utl_vector_t< element_t, allocator_t >::tail( ) noexcept {
        return m_memory[ m_size - 1 ];
    }

    template < typename element_t, class allocator_t >
    const element_t &utl_vector_t< element_t, allocator_t >::tail( ) const noexcept {
        return m_memory[ m_size - 1 ];
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::reverse( ) noexcept {
        for ( int idx = 0; idx < m_size / 2; idx++ )
            std::swap( m_memory[ idx ], m_memory[ m_size - 1 - idx ] );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::count( ) const {
        return m_size;
    }

    template < typename element_t, class allocator_t >
    bool utl_vector_t< element_t, allocator_t >::is_valid_index( int idx ) const {
        return ( idx >= 0 ) && ( idx < m_size );
    }

    template < typename element_t, class allocator_t >
    constexpr int utl_vector_t< element_t, allocator_t >::invalid_index( ) noexcept {
        return -1;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::grow_vector( int num ) noexcept {
        if ( m_size + num > m_memory.num_allocated( ) )
            m_memory.grow( m_size + num - m_memory.num_allocated( ) );

        m_size += num;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::ensure_capacity( int num ) noexcept {
        m_memory.ensure_capacity( num );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::shift_elements_right( int idx, int num ) noexcept {
        int num_to_move = m_size - idx - num;
        if ( num_to_move > 0 && num > 0 )
            std::memmove( &element( idx + num ), &element( idx ), num_to_move * sizeof( element_t ) );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::shift_elements_left( int idx, int num ) noexcept {
        int num_to_move = m_size - idx - num;
        if ( num_to_move > 0 && num > 0 )
            std::memmove( &element( idx ), &element( idx + num ), num_to_move * sizeof( element_t ) );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_to_head( ) noexcept {
        return insert_before( 0 );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_to_tail( ) noexcept {
        return insert_before( m_size );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_after( int idx ) noexcept {
        return insert_before( idx + 1 );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_before( int idx ) noexcept {
        grow_vector( );
        shift_elements_right( idx );
        construct( &element( idx ) );
        return idx;
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_to_head( const element_t &element ) noexcept {
        return insert_before( 0, element );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_to_tail( const element_t &element ) noexcept {
        return insert_before( m_size, element );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_after( int idx, const element_t &element ) noexcept {
        return insert_before( idx + 1, element );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_before( int idx, const element_t &element ) noexcept {
        grow_vector( );
        shift_elements_right( idx );
        copy_construct( &this->element( idx ), element );
        return idx;
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_multiple_to_head( int num ) noexcept {
        return insert_multiple_before( 0, num );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_multiple_to_tail( int num ) noexcept {
        return insert_multiple_before( m_size, num );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_multiple_to_tail( int num, const element_t *elements ) noexcept {
        return insert_multiple_before( m_size, num, elements );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_multiple_after( int idx, int num ) noexcept {
        return insert_multiple_before( idx + 1, num );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::set_count( int count ) noexcept {
        remove_all( );
        add_multiple_to_tail( count );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::set_size( int size ) noexcept {
        set_count( size );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::set_count_non_destructively( int count ) noexcept {
        int delta = count - m_size;
        if ( delta > 0 )
            add_multiple_to_tail( delta );
        else if ( delta < 0 )
            remove_multiple_from_tail( delta );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::copy_array( const element_t *elements, int size ) noexcept {
        set_size( size );
        for ( int idx = 0; idx < size; idx++ )
            ( *this )[ idx ] = elements[ idx ];
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::swap( utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept {
        m_memory.swap( utl_vector.m_memory );
        std::swap( m_size, utl_vector.m_size );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::add_vector_to_tail( const utl_vector_t< element_t, allocator_t > &utl_vector ) noexcept {
        int destcount = count( );
        int srccount  = utl_vector.count( );
        ensure_capacity( destcount + srccount );
        m_size += srccount;
        for ( int idx = 0; idx < srccount; idx++ )
            copy_construct( &element( destcount + idx ), utl_vector[ idx ] );

        return destcount;
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_multiple_before( int idx, int num ) noexcept {
        if ( num == 0 )
            return idx;

        grow_vector( num );
        shift_elements_right( idx, num );

        for ( int new_idx = 0; new_idx < num; ++new_idx )
            construct( &element( idx + new_idx ) );

        return idx;
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::insert_multiple_before( int idx, int num, const element_t *elements ) noexcept {
        if ( num == 0 )
            return idx;

        grow_vector( num );
        shift_elements_right( idx, num );

        if ( !elements ) {
            for ( int new_idx = 0; new_idx < num; ++new_idx )
                construct( &element( idx + new_idx ) );
        } else {
            for ( int new_idx = 0; new_idx < num; ++new_idx )
                copy_construct( &element( idx + new_idx ), elements[ new_idx ] );
        }

        return idx;
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::find( const element_t &element ) const noexcept {
        for ( int idx = 0; idx < count( ); ++idx ) {
            if ( this->element( idx ) == element )
                return idx;
        }

        return -1;
    }

    template < typename element_t, class allocator_t >
    bool utl_vector_t< element_t, allocator_t >::has_element( const element_t &element ) const noexcept {
        return ( find( element ) >= 0 );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::fast_remove( int idx ) noexcept {
        destruct( &element( idx ) );
        if ( m_size > 0 ) {
            if ( idx != m_size - 1 )
                std::memcpy( &element( idx ), &element( idx - 1 ), sizeof( element_t ) );

            --m_size;
        }
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::remove( int idx ) noexcept {
        destruct( &element( idx ) );
        shift_elements_left( idx );
        --m_size;
    }

    template < typename element_t, class allocator_t >
    bool utl_vector_t< element_t, allocator_t >::find_and_remove( const element_t &element ) noexcept {
        int idx = find( element );
        if ( idx != -1 ) {
            remove( idx );
            return true;
        }
        return false;
    }

    template < typename element_t, class allocator_t >
    bool utl_vector_t< element_t, allocator_t >::find_and_fast_remove( const element_t &element ) noexcept {
        int idx = find( element );
        if ( idx != -1 ) {
            fast_remove( idx );
            return true;
        }
        return false;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::remove_multiple( int idx, int num ) noexcept {
        for ( int ielement = idx + num; --ielement >= idx; )
            destruct( &element( ielement ) );

        shift_elements_left( idx, num );
        m_size -= num;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::remove_multiple_from_head( int num ) noexcept {
        for ( int idx = num; --idx >= 0; )
            Destruct( &element( idx ) );

        shift_elements_left( 0, num );
        m_size -= num;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::remove_multiple_from_tail( int num ) noexcept {
        for ( int idx = m_size - num; idx < m_size; idx++ )
            Destruct( &element( idx ) );

        m_size -= num;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::remove_all( ) noexcept {
        for ( int idx = m_size; --idx >= 0; )
            Destruct( &element( idx ) );

        m_size = 0;
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::purge( ) noexcept {
        remove_all( );
        m_memory.purge( );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::purge_and_delete_elements( ) noexcept {
        for ( int idx = 0; idx < m_size; idx++ )
            delete element( idx );

        purge( );
    }

    template < typename element_t, class allocator_t >
    void utl_vector_t< element_t, allocator_t >::compact( ) noexcept {
        m_memory.purge( m_size );
    }

    template < typename element_t, class allocator_t >
    int utl_vector_t< element_t, allocator_t >::num_allocated( ) const noexcept {
        return m_memory.num_allocated( );
    }
} // namespace hack::valve::inline data_types
