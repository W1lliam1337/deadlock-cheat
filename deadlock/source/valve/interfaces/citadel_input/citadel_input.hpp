#pragma once
#include "utils/math/data_types/vector.hpp"
#include "utils/memory/memory.hpp"

namespace hack::valve::inline interfaces {
    // note: you can find the pattern in the CCitadelInput::CreateMove
    inline const auto g_cmd_base
        = systems::get_pattern< void ** >( "client.dll", "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B CF 4C 8B E8", 3, true );

    // ref: "cl_demoviewoverride"
    inline const auto g_set_view_angles = systems::get_pattern< fastcall_t< void, void *, int, utils::vec3_t * > >(
        "client.dll", "E8 ? ? ? ? 48 8B 0D ? ? ? ? 41 B1 01 48 8B 05" );

    // note: you can find the pattern in the CCitadelInput::CreateMove
    inline const auto g_get_user_cmd
        = systems::get_pattern< fastcall_t< user_cmd_pb_t *, void *, int > >( "client.dll", "40 53 48 83 EC 20 8B DA 85 D2 78" );

    struct msg_qangle_t {
        _PAD( 0x18 );
        utils::vec3_t m_view_angles { };
    };

    struct msg_vector_t {
        _PAD( 0x18 );
        utils::vec3_t m_vector { };
    };

    struct in_button_state_pb_t {
        _PAD( 0x18 );
        std::uint32_t m_buttons { };
    };

    struct base_user_cmd_t {
        _PAD( 0x38 );
        in_button_state_pb_t *m_in_button_state_pb { };
        msg_qangle_t         *m_angle { };
        _PAD( 0x10 );
        float m_forward_move { };
        float m_side_move { };
    };

    struct user_cmd_pb_t {
        _PAD( 0x28 );
        base_user_cmd_t *m_base_user_cmd { };
        msg_vector_t    *m_camera_pos { };
        msg_qangle_t    *m_camera_angle { };
        _PAD( 0x18 );
        std::uint32_t m_buttons { };
    };

    struct citadel_input_t {
        _PAD( 0x251 );
        bool m_is_td { };
        _PAD( 0x19E );
        std::uint32_t m_td_distance { };
        _OFFSET( 0x2F5C, view_angle, utils::vec3_t )

        _INLINE void set_view_angles( utils::vec3_t &angles ) noexcept;
    };

    // ref: "c_thirdpersonshoulder"
    inline const auto g_citadel_input
        = systems::get_pattern< citadel_input_t ** >( "client.dll", "48 8B 05 ?? ?? ?? ?? 33 C9 C6 80 51 02 00 00 00", 3, true );

} // namespace hack::valve::inline interfaces

#include "citadel_input.inl"