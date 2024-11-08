#pragma once
#include "ldr_module/ldr_module.hpp"
#include "utils/hash/hash.hpp"

namespace hack::systems::inline memory {
    struct module_parser_t {
        /**
         * @brief Constructor that initializes the module parser and parses modules.
         *
         * This constructor calls the `parse_modules` function to populate the module list.
         * It also prints the number of parsed modules in debug mode.
         */
        explicit _INLINE _CONSTRUCTOR module_parser_t( ) noexcept;

        /**
         * @brief Parses the modules and populates the module list.
         *
         * This function retrieves the list of loaded modules from the process environment block (PEB)
         * and populates the `m_modules_list` with module information.
         *
         * @return True if modules were successfully parsed, false otherwise.
         */
        bool parse_modules( ) noexcept;

        /**
         * @brief Retrieves a module by its hash.
         *
         * This function searches the module list for a module with the specified hash and returns it.
         *
         * @param hash The hash of the module to retrieve.
         * @return A shared pointer to the module if found, nullptr otherwise.
         */
        [[nodiscard]] _INLINE std::shared_ptr< ldr_module_t > get_module( const std::size_t hash ) const noexcept;

      private:
        /**
         * @brief Retrieves the current thread environment block (TEB).
         *
         * This function uses inline assembly to get the current TEB.
         *
         * @return A pointer to the current TEB.
         */
        [[nodiscard]] static _INLINE const utils::teb *_HIDDEN get_current_teb( ) noexcept;

        /**
         * @brief Type definition for the map of modules.
         *
         * This map stores modules indexed by their hash values.
         */
        using modules_map_t = std::unordered_map< std::size_t, const std::shared_ptr< ldr_module_t > >;

        /**
         * @brief The list of parsed modules.
         *
         * This member variable holds the parsed modules in an unordered map indexed by their hash values.
         */
        modules_map_t m_modules_list { };
    };

    inline auto g_module_parser { std::make_unique< module_parser_t >( ) };
} // namespace hack::systems::inline memory

#include "module_parser.inl"