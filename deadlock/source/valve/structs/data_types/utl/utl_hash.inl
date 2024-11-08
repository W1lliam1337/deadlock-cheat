#pragma once
#include "utl_hash.hpp"
#include "vendor.hpp"

namespace hack::valve::inline data_types {
    _INLINE constexpr std::uint32_t _HIDDEN hash_int_conventional( const int value ) noexcept {
        std::uint32_t hash { ( 0xAAAAAAAA ) + ( value & 0xFF ) };
        hash = ( hash << 5 ) + hash + ( ( value >> 8 ) & 0xFF );
        hash = ( hash << 5 ) + hash + ( ( value >> 16 ) & 0xFF );
        hash = ( hash << 5 ) + hash + ( ( value >> 24 ) & 0xFF );

        return hash;
    }

    template < int bucket_count_t, class key_t >
    constexpr int utl_ts_hash_generic_hash_t< bucket_count_t, key_t >::hash( const key_t &key, const int bucket_mask ) noexcept {
        int hash_value { hash_int_conventional( reinterpret_cast< std::uintptr_t >( key ) ) };
        if ( bucket_count_t <= std::numeric_limits< std::uint16_t >::max( ) ) {
            hash_value ^= ( hash_value >> 16 );
        }

        if ( bucket_count_t <= std::numeric_limits< std::uint8_t >::max( ) ) {
            hash_value ^= ( hash_value >> 8 );
        }

        return ( hash_value & bucket_mask );
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    consteval utl_ts_hash_handle_t
        utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::invalid_handle( ) noexcept {
        return 0;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    utl_ts_hash_handle_t utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::find( key_t key ) noexcept {
        auto        bucket { hash_funcs_t::hash( key, bucket_count_t ) };
        const auto &hash_bucket { m_buckets[ bucket ] };
        const auto  hash_handle { find( key, hash_bucket.m_first, nullptr ) };
        return hash_handle ? hash_handle : find( key, hash_bucket.m_first_uncommited, hash_bucket.m_first );
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    int utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::get_elements(
        int first_element, const int count, utl_ts_hash_handle_t *elements ) const noexcept {
        int index { };
        for ( int i { }; i < bucket_count_t; i++ ) {
            const auto &hash_bucket { m_buckets[ i ] };

            for ( auto element { hash_bucket.m_first_uncommited }; element; element = element->m_next ) {
                if ( --first_element >= 0 )
                    continue;

                elements[ index++ ] = reinterpret_cast< utl_ts_hash_handle_t >( element );
                if ( index >= count )
                    return index;
            }
        }

        return index;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    element_t &utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::element( utl_ts_hash_handle_t hash ) noexcept {
        return reinterpret_cast< hash_fixed_data_t * >( hash )->get_data( );
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    const element_t &
        utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::element( utl_ts_hash_handle_t hash ) const noexcept {
        return reinterpret_cast< hash_fixed_data_t * >( hash )->m_data;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    element_t &
        utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::operator[] ( utl_ts_hash_handle_t hash ) noexcept {
        return reinterpret_cast< hash_fixed_data_t * >( hash )->m_data;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    const element_t &utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::operator[] (
        utl_ts_hash_handle_t hash ) const noexcept {
        return reinterpret_cast< hash_fixed_data_t * >( hash )->m_data;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    key_t utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::get_id( utl_ts_hash_handle_t hash ) noexcept {
        return reinterpret_cast< hash_fixed_data_t * >( hash )->m_key;
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    template < typename data_t >
    std::add_lvalue_reference_t< typename utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t,
                                                         alignment_t >::template hash_fixed_data_internal_t< data_t > * >
        utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t,

                       alignment_t >::hash_fixed_data_internal_t< data_t >::get_next( ) noexcept {
        return *reinterpret_cast< std::add_pointer_t< hash_fixed_data_internal_t< data_t > * > >( reinterpret_cast< std::uintptr_t >( this )
                                                                                                  + 0x8 );
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    template < typename data_t >
    std::add_lvalue_reference_t< data_t > utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t,
                                                         alignment_t >::hash_fixed_data_internal_t< data_t >::get_data( ) noexcept {
        return *reinterpret_cast< std::add_pointer_t< data_t > >( reinterpret_cast< std::uintptr_t >( this ) + 0x10 );
    }

    template < class element_t, int bucket_count_t, class key_t, class hash_funcs_t, int alignment_t >
    utl_ts_hash_handle_t
        utl_ts_hash_t< element_t, bucket_count_t, key_t, hash_funcs_t, alignment_t >::find( key_t key, hash_fixed_data_t *first_element,
                                                                                            hash_fixed_data_t *last_element ) noexcept {
        for ( auto element { first_element }; element != last_element; element = element->m_next ) {
            if ( hash_funcs_t::compare( element->m_key, key ) )
                return reinterpret_cast< utl_ts_hash_handle_t >( element );
        }

        return invalid_handle( );
    }
} // namespace hack::cs2::inline data_types