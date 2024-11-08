#pragma once
#include "citadel_input.hpp"

namespace hack::valve::inline interfaces {
    _INLINE void citadel_input_t::set_view_angles( utils::vec3_t &angles ) noexcept {
        return g_set_view_angles( this, 0, &angles );
    }
} // namespace hack::valve::inline interfaces