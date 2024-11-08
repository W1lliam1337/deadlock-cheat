#pragma once
#include "utils/memory/memory.hpp"
#include "valve/structs/data_types/handle/handle.hpp"
#include "valve/structs/data_types/utl/utl_vector.hpp"
#include "vendor.hpp"

namespace hack::valve {
    static inline constexpr auto k_max_entities_in_list { 512 };
    static inline constexpr auto k_max_entity_lists { 64 };                                            // 0x3F
    static inline constexpr auto k_max_total_entities { k_max_entities_in_list * k_max_entity_lists }; // 0x8000

    inline namespace entities {
        struct entity_t;

        struct entity_identity_t {
            entity_t   *m_entity { };
            void       *m_entity_class { };
            c_handle    m_handle { };                // LOWORD(handle) & 0x7FFF = entID
            int         m_name_stringable_index { }; // always seems to be -1
            const char *m_internal_name { };         // these two strings are optional!
            const char *m_entity_name { };           // ex: item_tpscroll
            _PAD( 0x8 );
            std::uint32_t m_flags { };
            _PAD( 0x4 );
            int           m_world_group_id { };
            std::uint32_t m_data_object_types { };
            std::uint16_t m_path_index { };
            _PAD( 0x16 );
            entity_identity_t *m_prev { };
            entity_identity_t *m_next { };
            entity_identity_t *m_prev_by_class { };
            entity_identity_t *m_next_by_class { };
        };
    } // namespace entities

    inline namespace interfaces {
        struct entity_identities_t {
            entity_identity_t m_identities[ k_max_entities_in_list ];
        };

        // The entity system utilizes listeners for the events mentioned below
        // I almost feel like a Valve employee doing these things the intended way
        struct entity_listener_t {
            virtual void on_entity_created( entity_t *ent )                          = 0;
            virtual void on_entity_spawned( entity_t *ent )                          = 0;
            virtual void on_entity_deleted( entity_t *ent )                          = 0;
            virtual void on_entity_parent_changed( entity_t *ent, entity_t *parent ) = 0;
        };

        struct entity_system_t {
            entity_system_t( )                         = delete;
            entity_system_t( entity_system_t && )      = delete;
            entity_system_t( const entity_system_t & ) = delete;

            virtual void      build_resource_manifest( void )                    = 0; // 01
            virtual void      n_2( )                                             = 0;
            virtual void      n_3( )                                             = 0;
            virtual void      n_4( )                                             = 0;
            virtual void      n_5( )                                             = 0;
            virtual void      n_6( )                                             = 0;
            virtual void      n_7( )                                             = 0;
            virtual void      add_ref_key_values( void const      *)                 = 0; // 7
            virtual void      release_key_values( void const      *)                 = 0; // 8
            virtual void      n_9( )                                             = 0;
            virtual void      n_10( )                                            = 0;
            virtual void      clear_entity_database( void )                      = 0; // 11
            virtual entity_t *find_entity_procedural( const char *... )          = 0;
            virtual entity_t *on_entity_parent_changed( entity_t *, entity_t * ) = 0; // 13
            virtual entity_t *on_add_entity( entity_t *, c_handle )              = 0; // 14
            virtual entity_t *on_remove_entity( entity_t *, c_handle )           = 0; // 15
            virtual void      n_16( )                                            = 0;
            virtual void      sort_entities( int, void *, int *, int      *)         = 0; // 17
            virtual void      n_18( )                                            = 0;
            virtual void      n_19( )                                            = 0;
            virtual void      n_20( )                                            = 0;
            virtual void      n_21( )                                            = 0;
        };

        struct game_entity_system_t : entity_system_t {
            /**
             * @brief Retrieves the identity of a game entity by index.
             *
             * @param idx The index of the entity.
             * @return A pointer to the entity's identity or nullptr if out of range.
             */
            [[nodiscard]] _INLINE entity_identity_t *get_identity( int idx ) const noexcept;

            /**
             * @brief Retrieves a pointer to a game entity.
             *
             * @param ent The handle of the entity.
             */
            [[nodiscard]] _INLINE entity_identity_t *get_entity( c_handle ent ) const noexcept;

            /**
             * @brief Retrieves a pointer to a game entity.
             *
             * @tparam type_t The type of the entity.
             * @param idx The index of the entity.
             * @return A pointer to the entity or nullptr if not found.
             */
            template < class type_t = entity_t >
            [[nodiscard]] std::add_pointer_t< type_t > get_entity( int idx ) noexcept;

            // Iterated in OnAddEntity/OnRemoveEntity
            _OFFSET( 0x10, get_identity_chunks, std::array< entity_identities_t *, k_max_entity_lists > );

            // Iterated in OnAddEntity/OnRemoveEntity
            // Func: 8B 81 10 15 00
            // #STR: "(missing),", "(missing)", "Ent %3d: %s class %s name %s\n"
            _OFFSET( 0x1530, get_highest_entity_index, int );

            // Iterated in OnAddEntity/OnRemoveEntity
            /*
             * mov     eax, [rdi+1548h]
             * sub     eax, 1
             * movsxd  rbx, eax
             * js      short loc_180C2D1FA
             */
            _OFFSET( 0x1568, get_listeners, utl_vector_t< entity_listener_t * > );
        };

    } // namespace interfaces
} // namespace hack::valve

#include "entity_system.inl"