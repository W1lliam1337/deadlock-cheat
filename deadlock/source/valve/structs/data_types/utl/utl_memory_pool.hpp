#pragma once

namespace hack::valve::inline data_types {
    class utl_memory_pool_t {
    public:
        struct free_list_t {
            free_list_t *m_next{ }, *m_prev{ };
            void* m_data{ };
        };

        struct blob_t {
            blob_t* m_next_blob{ };
            std::int32_t m_num_bytes{ };
            free_list_t m_free_list[ 1 ] = { };
        };

        int m_block_size{ }, m_blocks_per_blob{ }, m_grow_mode{ }, m_blocks_allocated{ }, m_peak_alloc{ };
        std::uint16_t m_alignment{ }, m_num_blobs{ };
        free_list_t *m_head_of_free_list{ }, *m_free_list{ };
        blob_t *m_last_blob{ }, *m_first_blob{ };
        int m_mem_alloc_attribute{ };
        std::uint8_t m_unknown{ };
    };
} // namespace hack::cs2::inline data_types