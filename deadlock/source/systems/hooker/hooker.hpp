#pragma once
#include "minhk/minhook.hpp"
#include "systems/logger/logger.hpp"
#include "utils/memory/base_address/base_address.hpp"

namespace hack::systems {
    /**
     * @brief Manages the function hooks, including installation and removal.
     */
    struct hook_t {
        /**
         * @brief Constructs a hook with a function table and installs the hook.
         * @param table Pointer to the function table where the hook is applied.
         */
        explicit _INLINE hook_t( void *table = nullptr, void *hook_func = nullptr ) noexcept;

        void *m_table { };         ///< The function table to be hooked.
        void *m_original_func { }; ///< The original function pointer before hooking.
        void *m_hook_func { };     ///< The function pointer to be used as the hook.

        /**
         * @brief Applies the hook by enabling it.
         * @param replace Pointer to the replacement function.
         */
        _INLINE void hook( void *replace ) const noexcept;

        /**
         * @brief Disables the hook.
         */
        _INLINE void unhook( ) const noexcept;

        /**
         * @brief Retrieves the original function pointer.
         * @tparam fn_t The function signature type.
         * @return The original function pointer cast to the specified signature.
         */
        template < typename fn_t >
        [[nodiscard]] _INLINE fn_t get_original( ) const noexcept;
    };

    /**
     * @brief Manages a collection of hooks, indexed by unique tokens.
     */
    struct hook_manager_t {
        _INLINE hook_manager_t( ) noexcept;
        _INLINE ~hook_manager_t( ) noexcept;

        /// Map of hooks, indexed by a unique token (e.g., function address or identifier).
        std::unordered_map< std::size_t, hook_t > m_hook_map { };

        /**
         * @brief Adds a new hook to the map.
         * @param token Unique identifier for the hook.
         * @param table Pointer to the function table where the hook is applied.
         * @param hook_func Pointer to the function that replaces the original.
         */
        _INLINE void add_hook( const std::size_t token, void *table, void *hook_func ) noexcept;

        /**
         * @brief Removes a hook from the map by its unique token.
         * @param token Unique identifier for the hook.
         */
        _INLINE void remove_hook( const std::size_t token ) noexcept;

        /**
         * @brief Retrieves a hook by its unique token.
         * @param token Unique identifier for the hook.
         * @return Pointer to the hook if found, or nullptr if not.
         */
        _INLINE hook_t *get_hook( const std::size_t token ) noexcept;
    };

    inline auto g_hook_manager { std::make_unique< hook_manager_t >( ) };
} // namespace hack::systems

#include "hooker.inl"