#pragma once
#include "systems/module_parser/module_parser.hpp"
#include "utils/memory/memory.hpp"
#include "valve/structs/data_types/utl/utl_hash.hpp"

namespace hack::valve::inline interfaces {
    struct class_field_t;
    struct class_info_t;

    struct [[nodiscard]] base_class_info_data_t {
        std::int32_t  m_offset { };
        class_info_t *m_class { };
    };

    struct base_class_info_t : base_class_info_data_t { };

    struct class_info_data_t {
        _PAD( 0x8 )
        const char  *m_name { }, *m_description { };
        std::int32_t m_size_of { };
        std::uint8_t m_fields_count { };
        _PAD( 0x5 )
        std::uint8_t m_align_of { }, m_base_classes_count { };
        _PAD( 0x4 )
        class_field_t *m_fields { };
        _PAD( 0x8 )
        base_class_info_t *m_base_classes { };
        _PAD( 0x28 )
    };

    struct class_info_t : class_info_data_t { };

    struct [[nodiscard]] class_field_data_t {
        const char *m_name { };
        _PAD( 0x8 )
        std::int32_t m_offset { };
        _PAD( 0xC )
    };

    struct class_field_t : class_field_data_t {
      public:
    };
} // namespace hack::valve::inline interfaces

#include "schema_system.inl"