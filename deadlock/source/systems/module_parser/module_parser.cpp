#include "pch.hpp"

#include "module_parser.hpp"
#include "utils/hash/hash.hpp"

namespace hack::systems::inline memory {
    bool module_parser_t::parse_modules( ) noexcept {
        const auto *const peb { get_current_teb( )->m_process_environment_block };

        _ASSERT( peb != nullptr );

        const auto *const modules_order { &peb->m_ldr->m_in_load_order_module_list };

        _ASSERT( modules_order != nullptr );

        for ( const auto *module { modules_order->m_flink }; module != nullptr && module != modules_order; module = module->m_flink ) {
            const auto ldr_table { utils::base_address_t { module }.self_offset(
                -_OFFSETOF( utils::ldr_data_table_entry, m_in_load_order_links ) ) };

            if ( !ldr_table )
                continue;

            auto module_record { std::make_unique< ldr_module_t >( ldr_table ) };

            if ( !module_record )
                continue;

            m_modules_list.try_emplace( _HASH( module_record->get_name( ) ), std::move( module_record ) );
        }

        return !m_modules_list.empty( );
    }
} // namespace hack::systems::inline memory