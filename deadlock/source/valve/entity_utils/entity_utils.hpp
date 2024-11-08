#pragma once
#include "systems/module_parser/module_parser.hpp"
#include "valve/interfaces/entity_system/entity_system.hpp"
#include "valve/structs/entities/base_player.hpp"

namespace hack::valve {
    inline namespace interfaces {
        struct game_entity_system_t;
    }

    inline game_entity_system_t *g_game_entity_system { };

    class c_entity_list {
        static inline auto m_entity_system { systems::get_pattern< game_entity_system_t * >(
            "client.dll",
            "48 8B 0D ?? ?? ?? ?? 89 45 CB E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? 0F 28 00 0F 29 45 D7 0F "
            "28 48 10 0F 29 4D E7 0F 28 40 "
            "20 48 8B 05 ?? ?? ?? ?? 48 89 45 B7 0F 29 45 F7 4C 89 7D A7",
            3, true ) };
      public:
        class c_entity_listener : public entity_listener_t {
          public:
            void on_entity_created( entity_t *ent ) noexcept final;
            void on_entity_spawned( [[maybe_unused]] entity_t *ent ) noexcept final { };
            void on_entity_deleted( entity_t *ent ) noexcept final;
            void on_entity_parent_changed( [[maybe_unused]] entity_t *ent, [[maybe_unused]] entity_t *parent ) noexcept final { };
        };

        _INLINE c_entity_list( );
        _INLINE ~c_entity_list( ) noexcept;

        /**
         * @brief Retrieves all entities in the list.
         *
         * @return A span of pointers to entities.
         */
        [[nodiscard]] _INLINE std::span< entity_t *const > get_entities( ) const noexcept;

        /**
         * @brief Retrieves all player pawns.
         *
         * @return A span of pointers to player pawns.
         */
        [[nodiscard]] _INLINE std::span< player_pawn_t *const > get_player_pawns( ) const noexcept;

        /**
         * @brief Retrieves all player controllers.
         *
         * @return A span of pointers to player controllers.
         */
        [[nodiscard]] _INLINE std::span< player_controller_t *const > get_player_controllers( ) const noexcept;

        /**
         * @brief Retrieves the local player's controller.
         *
         * This method retrieves the local player's controller.
         *
         * @return A pointer to the local player's controller.
         */
        [[nodiscard]] static _INLINE player_controller_t *get_local_controller( ) noexcept;

      private:
        /**
         * @brief Adds an entity to the list.
         *
         * @param entity Pointer to the entity to add.
         */
        void _HIDDEN add_entity( entity_t *entity ) noexcept;

        /**
         * @brief Removes an entity from the list.
         *
         * @param entity Pointer to the entity to remove.
         */
        void _HIDDEN remove_entity( entity_t *entity ) noexcept;

        /**
         * @brief Sorts entities, player pawns, and player controllers by their index.
         */
        void _HIDDEN sort( ) noexcept;

        c_entity_listener m_entity_listener = { };

        std::vector< entity_t * >            m_entities           = { };
        std::vector< player_pawn_t * >       m_player_pawns       = { };
        std::vector< player_controller_t * > m_player_controllers = { };
    };

    inline std::unique_ptr< c_entity_list > g_entity_list { };
} // namespace hack::valve

#include "entity_utils.inl"