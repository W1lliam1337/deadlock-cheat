#include "pch.hpp"

#include "base_entity.hpp"
#include "base_player.hpp"
#include "valve/entity_utils/entity_utils.hpp"

namespace hack::valve::inline entities {
    bool entity_t::is_enemy( ) noexcept {
        return true;
    }
} // namespace hack::valve::inline entities