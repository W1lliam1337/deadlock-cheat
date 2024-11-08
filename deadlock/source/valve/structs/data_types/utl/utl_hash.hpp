#pragma once
#include "utl_memory_pool.hpp"
#include "vendor.hpp"

namespace hack::valve::inline data_types {
    using utl_ts_hash_handle_t = std::uintptr_t;

    template < int bucket_count_t, class key_t = std::uintptr_t >
    struct utl_ts_hash_generic_hash_t {
        static _INLINE constexpr int hash( const key_t &key, const int bucket_mask ) noexcept;

        static _INLINE bool compare( const key_t &lhs, const key_t &rhs ) noexcept {
            return lhs == rhs;
        }
    };

    template < class element_t, int                                                          bucket_count_t, class key_t = std::uintptr_t,
               class hash_funcs_t = utl_ts_hash_generic_hash_t< bucket_count_t, key_t >, int alignment_t = 0 >
    struct utl_ts_hash_t {
        static inline constexpr int                           m_bucket_mask { bucket_count_t - 1 };
        static _INLINE consteval utl_ts_hash_handle_t _HIDDEN invalid_handle( ) noexcept;

        [[nodiscard]] _INLINE utl_ts_hash_handle_t find( key_t key ) noexcept;

        [[nodiscard]] _INLINE int count( ) const noexcept {
            return m_entry_memory.m_peak_alloc;
        }

        [[nodiscard]] _INLINE int get_elements( int first_element, const int count, utl_ts_hash_handle_t *elements ) const noexcept;

        [[nodiscard]] _INLINE element_t       &element( utl_ts_hash_handle_t hash ) noexcept;
        [[nodiscard]] _INLINE const element_t &element( utl_ts_hash_handle_t hash ) const noexcept;

        [[nodiscard]] _INLINE element_t       &operator[] ( utl_ts_hash_handle_t hash ) noexcept;
        [[nodiscard]] _INLINE const element_t &operator[] ( utl_ts_hash_handle_t hash ) const noexcept;

        [[nodiscard]] static _INLINE key_t get_id( utl_ts_hash_handle_t hash ) noexcept;

      private:
        template < typename data_t >
        struct hash_fixed_data_internal_t {
            key_t                                 m_key { };
            hash_fixed_data_internal_t< data_t > *m_next { };
            data_t                                m_data { };

            [[nodiscard]] std::add_lvalue_reference_t< hash_fixed_data_internal_t< data_t > * > get_next( ) noexcept;
            [[nodiscard]] _INLINE std::add_lvalue_reference_t< data_t > get_data( ) noexcept;
        };

        using hash_fixed_data_t = hash_fixed_data_internal_t< element_t >;

        struct hash_bucket_t {
            _PAD( 0x18 )
            hash_fixed_data_t *m_first { }, *m_first_uncommited { };
        };

        [[nodiscard]] _INLINE utl_ts_hash_handle_t find( key_t key, hash_fixed_data_t *first_element,
                                                         hash_fixed_data_t *last_element ) noexcept;

        utl_memory_pool_t m_entry_memory { };
        _PAD( 0x40 )
        hash_bucket_t m_buckets[ bucket_count_t ] { };
        bool          m_needs_commit { };
    };

} // namespace hack::cs2::inline data_types

#include "utl_hash.inl"