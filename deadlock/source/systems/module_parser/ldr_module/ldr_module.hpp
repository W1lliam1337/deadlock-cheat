#pragma once
#include "utils/memory/base_address/base_address.hpp"
#include "utils/memory/win_types/win_types.hpp"

namespace hack::systems::inline memory {
    struct ldr_module_t {
      private:
        /**
         * @brief Address of the module (ldr_data_table_entry structure).
         */
        utils::base_address_t m_base_address { };

      public:
        /**
         * @brief Constructor that initializes the module with a given base address.
         *
         * @param address The base address of the module.
         */
        explicit _INLINE ldr_module_t( const utils::base_address_t &address ) noexcept;

        /**
         * @brief Retrieves the base address of the module.
         *
         * @return The base address of the module.
         */
        [[nodiscard]] _INLINE utils::base_address_t get_base_address( ) const noexcept;

        /**
         * @brief Enumeration for specifying the case of the module name.
         */
        enum class e_name_case : std::uint8_t {
            e_unknown = 0, ///< Unknown case (should not be used).
            e_unmodified,  ///< Unmodified case.
            e_lowercase,   ///< Lowercase.
            e_uppercase    ///< Uppercase.
        };

        /**
         * @brief Retrieves the wide string name of the module.
         *
         * @param name_case The case to convert the name to (default is lowercase).
         * @return The wide string name of the module.
         */
        [[nodiscard]] _INLINE std::wstring get_wname( const e_name_case name_case = e_name_case::e_lowercase ) const noexcept;

        /**
         * @brief Retrieves the string name of the module.
         *
         * @param name_case The case to convert the name to (default is lowercase).
         * @return The string name of the module.
         */
        [[nodiscard]] _INLINE std::string get_name( const e_name_case name_case = e_name_case::e_lowercase ) const noexcept;

        /**
         * @brief Retrieves the NT headers of the module.
         *
         * @return A pointer to the NT headers of the module.
         */
        _INLINE utils::image_nt_headers_64 *get_nt_headers( ) const;

        /**
         * @brief Retrieves the optional header of the module.
         *
         * @param base_address The base address of the module.
         * @return The optional header of the module.
         */
        static _INLINE constexpr utils::base_address_t _HIDDEN get_optional_header( const utils::base_address_t &base_address ) noexcept;

        /**
         * @brief Converts a pattern string to a vector of bytes.
         *
         * @param pattern The pattern string to convert.
         * @return A vector of bytes representing the pattern.
         */
        [[nodiscard]] _INLINE static std::vector< std::optional< std::byte > > pattern_to_bytes( const std::string_view pattern ) noexcept;
        [[nodiscard]] _INLINE utils::base_address_t find_interface( std::string_view interface_name ) const noexcept;

        /**
         * @brief Finds a pattern in the module's memory.
         *
         * @param pattern The pattern to search for.
         * @return The base address of the found pattern, or an empty base_address_t if not found.
         */
        [[nodiscard]] _INLINE utils::base_address_t find_pattern( const std::string_view pattern ) const noexcept;

        enum class e_data_directory : std::uint16_t {
            e_export = 0,
            e_import,
            e_resource,
            e_exception,
            e_security,
            e_base_reloc,
            e_debug,
            e_architecture,
            e_global_ptr,
            e_tls,
            e_load_config,
            e_bound_import,
            e_iat,
            e_delay_import,
            e_com_descriptor
        };

        [[nodiscard]] static constexpr utils::base_address_t get_data_directory( const utils::base_address_t &base_address,
                                                                                 e_data_directory             data_directory ) noexcept;

        [[nodiscard]] constexpr utils::base_address_t get_export_address( std::string_view procedure_name ) const noexcept;
    };
} // namespace hack::systems::inline memory

#include "ldr_module.inl"