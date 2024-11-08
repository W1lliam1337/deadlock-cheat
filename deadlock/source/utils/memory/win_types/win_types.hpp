#pragma once

#include "vendor.hpp"

namespace hack::utils::inline memory::inline structs {
    struct exceptions_registration_record {
        exceptions_registration_record *m_next { };    // 0x0000
        void                           *m_handler { }; // 0x0008
    };                                                 // Size: 0x0010

    static_assert( sizeof( exceptions_registration_record ) == 0x0010 );

    struct nt_tib {
        exceptions_registration_record *m_exception_list { };      // 0x0000
        void                           *m_stack_base { };          // 0x0008
        void                           *m_stack_limit { };         // 0x0010
        void                           *m_sub_system_tib { };      // 0x0018
        void                           *m_fiber_data { };          // 0x0020
        void                           *m_arbitrary_user_data { }; // 0x0028
        nt_tib                         *m_self { };                // 0x0030
    };                                                             // Size: 0x0038

    static_assert( sizeof( nt_tib ) == 0x0038 );

    struct client_id {
        void *m_unique_process { }; // 0x0000
        void *m_unique_thread { };  // 0x0008
    };                              // Size: 0x0010

    static_assert( sizeof( client_id ) == 0x0010 );

    struct list_entry {
        list_entry *m_flink { }; // 0x0000
        list_entry *m_blink { }; // 0x0008
    };                           // Size: 0x0010

    static_assert( sizeof( list_entry ) == 0x0010 );

    struct peb_ldr_data {
        uint32_t   m_length { };                              // 0x0000
        uint32_t   m_initialized { };                         // 0x0004
        void      *m_handle { };                              // 0x0008
        list_entry m_in_load_order_module_list { };           // 0x0010
        list_entry m_in_memory_order_module_list { };         // 0x0020
        list_entry m_in_initialization_order_module_list { }; // 0x0030
        void      *m_entry_in_progress { };                   // 0x0040
        uint8_t    m_shutdown_in_progress { };                // 0x0048
        void      *m_shutdown_thread_id { };                  // 0x0050
    };                                                        // Size: 0x0058

    static_assert( sizeof( peb_ldr_data ) == 0x0058 );

    struct unicode_string {
        uint16_t m_length { };         // 0x0000
        uint16_t m_maximum_length { }; // 0x0002
        wchar_t *m_buffer { };         // 0x0008
    };                                 // Size: 0x0010

    static_assert( sizeof( unicode_string ) == 0x0010 );

    struct cur_dir {
        unicode_string m_dos_path { }; // 0x0000
        void          *m_handle { };   // 0x0010
    };                                 // Size: 0x0018

    static_assert( sizeof( cur_dir ) == 0x0018 );

    struct regular_string {
        uint16_t m_length { };         // 0x0000
        uint16_t m_maximum_length { }; // 0x0002
        char    *m_buffer { };         // 0x0008
    };                                 // Size: 0x0010

    static_assert( sizeof( regular_string ) == 0x0010 );

    struct rtl_drive_letter_cur_dir {
        uint16_t       m_flags { };      // 0x0000
        uint16_t       m_length { };     // 0x0002
        uint32_t       m_time_stamp { }; // 0x0004
        regular_string m_dos_path { };   // 0x0008
    };                                   // Size: 0x0018

    static_assert( sizeof( rtl_drive_letter_cur_dir ) == 0x0018 );

    struct rtl_user_process_parameters {
        uint32_t                                           m_maximum_length { };                         // 0x0000
        uint32_t                                           m_length { };                                 // 0x0004
        uint32_t                                           m_flags { };                                  // 0x0008
        uint32_t                                           m_debug_flags { };                            // 0x000C
        void                                              *m_console_handle { };                         // 0x0010
        uint32_t                                           m_console_flags { };                          // 0x0018
        void                                              *m_standard_input { };                         // 0x0020
        void                                              *m_standard_output { };                        // 0x0028
        void                                              *m_standard_error { };                         // 0x0030
        cur_dir                                            m_current_directory { };                      // 0x0038
        unicode_string                                     m_dll_path { };                               // 0x0050
        unicode_string                                     m_image_path_name { };                        // 0x0060
        unicode_string                                     m_command_line { };                           // 0x0070
        void                                              *m_environment { };                            // 0x0080
        uint32_t                                           m_starting_x { };                             // 0x0088
        uint32_t                                           m_starting_y { };                             // 0x008C
        uint32_t                                           m_count_x { };                                // 0x0090
        uint32_t                                           m_count_y { };                                // 0x0094
        uint32_t                                           m_count_chars_x { };                          // 0x0098
        uint32_t                                           m_count_chars_y { };                          // 0x009C
        uint32_t                                           m_fill_attribute { };                         // 0x00A0
        uint32_t                                           m_window_flags { };                           // 0x00A4
        uint32_t                                           m_show_window_flags { };                      // 0x00A8
        unicode_string                                     m_window_title { };                           // 0x00B0
        unicode_string                                     m_desktop_name { };                           // 0x00C0
        unicode_string                                     m_shell_info { };                             // 0x00D0
        unicode_string                                     m_runtime_data { };                           // 0x00E0
        std::array< const rtl_drive_letter_cur_dir, 0x20 > m_current_directories { };                    // 0x00F0
        uint64_t                                           m_environment_size { };                       // 0x03F0
        uint64_t                                           m_environment_version { };                    // 0x03F8
        void                                              *m_package_dependency_data { };                // 0x0400
        uint32_t                                           m_process_group_id { };                       // 0x0408
        uint32_t                                           m_loader_threads_count { };                   // 0x040C
        unicode_string                                     m_redirection_dll_name { };                   // 0x0410
        unicode_string                                     m_heap_partition_name { };                    // 0x0420
        void                                              *m_default_thread_pool_cpu_set_masks { };      // 0x0430
        uint32_t                                           m_default_thread_pool_cpu_set_mask_count { }; // 0x0438
        uint32_t                                           m_defalut_thread_pool_thread_maximum { };     // 0x043C
        uint32_t                                           m_heap_memory_type_mask { };                  // 0x0440
    };                                                                                                   // Size: 0x0448

    static_assert( sizeof( rtl_user_process_parameters ) == 0x0448 );

    struct rtl_critical_section {
        void    *m_debug_info { };      // 0x0000
        int32_t  m_lock_count { };      // 0x0008
        int32_t  m_recursion_count { }; // 0x000C
        void    *m_owning_thread { };   // 0x0010
        void    *m_lock_semaphore { };  // 0x0018
        uint64_t m_spin_count { };      // 0x0020
    };                                  // Size: 0x0028

    static_assert( sizeof( rtl_critical_section ) == 0x0028 );

    struct rtl_bit_map {
        uint32_t m_size_of_bit_map { }; // 0x0000
        void    *m_buffer { };          // 0x0008
    };                                  // Size: 0x0010

    static_assert( sizeof( rtl_bit_map ) == 0x0010 );

    struct peb {
        uint8_t                            m_inherited_address_space { };                 // 0x0000
        uint8_t                            m_read_image_file_exec_options { };            // 0x0001
        uint8_t                            m_being_debugged { };                          // 0x0002
        uint8_t                            m_bit_field { };                               // 0x0003
        std::array< const uint8_t, 0x4 >   m_unknown_0 { };                               // 0x0004
        void                              *m_mutant { };                                  // 0x0008
        void                              *m_image_base_address { };                      // 0x0010
        peb_ldr_data                      *m_ldr { };                                     // 0x0018
        rtl_user_process_parameters       *m_process_parameters { };                      // 0x0020
        void                              *m_sub_system_data { };                         // 0x0028
        void                              *m_process_heap { };                            // 0x0030
        rtl_critical_section              *m_fast_peb_lock { };                           // 0x0038
        std::array< const uint8_t, 0x8 >   m_unknown_1 { };                               // 0x0040
        void                              *m_ifeo_key { };                                // 0x0048
        uint32_t                           m_cross_process_flags { };                     // 0x0050
        std::array< const uint8_t, 0x4 >   m_unknown_2 { };                               // 0x0054
        void                              *m_kernel_callback_table { };                   // 0x0058
        uint32_t                           m_system_reserved { };                         // 0x0060
        uint32_t                           m_atl_thunk_slist_ptr_32 { };                  // 0x0064
        void                              *m_api_set_map { };                             // 0x0068
        uint32_t                           m_tls_expansion_counter { };                   // 0x0070
        std::array< const uint8_t, 0x4 >   m_unknown_3 { };                               // 0x0074
        rtl_bit_map                       *m_tls_bitmap { };                              // 0x0078
        std::array< const uint8_t, 0x2 >   m_tls_bitmap_bits { };                         // 0x0080
        void                              *m_read_only_shared_memory_base { };            // 0x0088
        void                              *m_shared_data { };                             // 0x0090
        void                             **m_read_only_static_server_data { };            // 0x0098
        void                              *m_ansi_code_page_data { };                     // 0x00A0
        void                              *m_oem_code_page_data { };                      // 0x00A8
        void                              *m_unicode_case_table_data { };                 // 0x00B0
        uint32_t                           m_number_of_processors { };                    // 0x00B8
        uint32_t                           m_nt_global_flag_1 { };                        // 0x00BC
        uint64_t                           m_critical_section_timeout { };                // 0x00C0
        uint64_t                           m_heap_segment_reserve { };                    // 0x00C8
        uint64_t                           m_heap_segment_commit { };                     // 0x00D0
        uint64_t                           m_heap_decommit_total_free_threshold { };      // 0x00D8
        uint64_t                           m_heap_decommit_free_block_threshold { };      // 0x00E0
        uint32_t                           m_number_of_heaps { };                         // 0x00E8
        uint32_t                           m_maximum_number_of_heaps { };                 // 0x00EC
        void                             **m_process_heaps { };                           // 0x00F0
        void                              *m_gdi_shared_handle_table { };                 // 0x00F8
        void                              *m_process_starter_helper { };                  // 0x0100
        uint32_t                           m_gdi_dc_attribute_list { };                   // 0x0108
        std::array< const uint8_t, 0x4 >   m_unknown_4 { };                               // 0x010C
        rtl_critical_section              *m_loader_lock { };                             // 0x0110
        uint32_t                           m_os_major_version { };                        // 0x0118
        uint32_t                           m_os_minor_version { };                        // 0x011C
        uint16_t                           m_os_build_number { };                         // 0x0120
        uint16_t                           m_os_csd_version { };                          // 0x0122
        uint32_t                           m_os_platform_id { };                          // 0x0124
        uint32_t                           m_image_sub_system { };                        // 0x0128
        uint32_t                           m_image_sub_system_major_version { };          // 0x012C
        uint32_t                           m_image_sub_system_minor_version { };          // 0x0130
        std::array< const uint8_t, 0x4 >   m_unknown_5 { };                               // 0x0134
        uint64_t                           m_active_process_affinity_mask { };            // 0x0138
        std::array< const uint32_t, 0x3C > m_gdi_handle_buffer { };                       // 0x0140
        void                              *m_post_process_init_routine { };               // 0x0230
        rtl_bit_map                       *m_tls_expansion_bitmap { };                    // 0x0238
        std::array< const uint32_t, 0x20 > m_tls_expansion_bitmap_bits { };               // 0x0240
        uint32_t                           m_session_id { };                              // 0x02C0
        std::array< const uint8_t, 0x4 >   m_unknown_6 { };                               // 0x02C4
        uint64_t                           m_app_compat_flags { };                        // 0x02C8
        uint64_t                           m_app_compat_flags_user { };                   // 0x02D0
        void                              *m_shim_data { };                               // 0x02D8
        void                              *m_app_compat_info { };                         // 0x02E0
        unicode_string                     m_csd_version { };                             // 0x02E8
        void                              *m_activation_context_data { };                 // 0x02F8
        void                              *m_process_assembly_storage_map { };            // 0x0300
        void                              *m_system_default_activation_context_data { };  // 0x0308
        void                              *m_system_assembly_storage_map { };             // 0x0310
        uint64_t                           m_minimum_stack_commit { };                    // 0x0318
        std::array< void *, 0x2 >          m_spare_pointers { };                          // 0x0320
        void                              *m_patch_loader_data { };                       // 0x0330
        void                              *m_chpe_v2_process_info { };                    // 0x0338
        uint32_t                           m_app_model_feature_state { };                 // 0x0340
        std::array< const uint32_t, 0x2 >  m_spare_ulongs { };                            // 0x0344
        uint16_t                           m_active_code_page { };                        // 0x034C
        uint16_t                           m_oem_code_page { };                           // 0x034E
        uint16_t                           m_use_case_mapping { };                        // 0x0350
        uint16_t                           m_unused_nls_field { };                        // 0x0352
        void                              *m_wer_registration_data { };                   // 0x0358
        void                              *m_wer_ship_assert_ptr { };                     // 0x0360
        void                              *m_ec_code_bit_map { };                         // 0x0368
        void                              *m_image_header_hash { };                       // 0x0370
        uint32_t                           m_tracing_flags { };                           // 0x0378
        std::array< const uint8_t, 0x4 >   m_unknown_7 { };                               // 0x037C
        uint64_t                           m_csr_server_read_only_shared_memory_base { }; // 0x0380
        uint64_t                           m_tpp_workerp_list_lock { };                   // 0x0388
        list_entry                         m_tpp_workerp_list { };                        // 0x0390
        std::array< void *, 0x80 >         m_wait_on_address_hash_table { };              // 0x03A0
        void                              *m_telemetry_coverage_header { };               // 0x07A0
        uint32_t                           m_cloud_file_flags { };                        // 0x07A8
        uint32_t                           m_cloud_file_diag_flags { };                   // 0x07AC
        uint8_t                            m_place_holder_compatiblity_mode { };          // 0x07B0
        std::array< const uint8_t, 0x7 >   m_place_holder_reserved { };                   // 0x07B1
        void                              *m_leap_second_data { };                        // 0x07B8
        uint32_t                           m_leap_second_flags { };                       // 0x07C0
        uint32_t                           m_nt_global_flag_2 { };                        // 0x07C4
        uint64_t                           m_extended_feature_disable_mask { };           // 0x07C8
    };                                                                                    // Size: 0x07D0

    static_assert( sizeof( peb ) == 0x07D0 );

    struct activation_context_stack {
        void      *m_active_frame { };         // 0x0000
        list_entry m_frame_list_cache { };     // 0x0008
        uint32_t   m_flags { };                // 0x0018
        uint32_t   m_next_cookie_sequence { }; // 0x001C
        uint32_t   m_stack_id { };             // 0x0020
    };                                         // Size: 0x0028

    static_assert( sizeof( activation_context_stack ) == 0x0028 );

    struct gdi_teb_batch {
        uint32_t                            m_offset { }; // 0x0000
        uint64_t                            m_hdc { };    // 0x0008
        std::array< const uint32_t, 0x136 > m_buffer { }; // 0x0010
    };                                                    // Size: 0x04E8

    static_assert( sizeof( gdi_teb_batch ) == 0x04E8 );

    struct guid {
        uint32_t                         m_data_1 { }; // 0x0000
        uint16_t                         m_data_2 { }; // 0x0004
        uint16_t                         m_data_3 { }; // 0x0006
        std::array< const uint8_t, 0x8 > m_data_4 { }; // 0x0008
    };                                                 // Size: 0x0010

    static_assert( sizeof( guid ) == 0x0010 );

    struct processor_number {
        uint16_t m_group { };    // 0x0000
        uint8_t  m_number { };   // 0x0002
        uint8_t  m_reserved { }; // 0x0003
    };                           // Size: 0x0004

    static_assert( sizeof( processor_number ) == 0x0004 );

    struct teb_active_frame_context {
        uint32_t m_flags { };      // 0x0000
        uint8_t *m_frame_name { }; // 0x0008
    };                             // Size: 0x0010

    static_assert( sizeof( teb_active_frame_context ) == 0x0010 );

    struct teb_active_frame {
        uint32_t                  m_flags { };    // 0x0000
        teb_active_frame         *m_previous { }; // 0x0008
        teb_active_frame_context *m_context { };  // 0x0010
    };                                            // Size: 0x0018

    static_assert( sizeof( teb_active_frame ) == 0x0018 );

    struct teb {
        nt_tib                             m_nt_tib { };                                // 0x0000
        void                              *m_environment_pointer { };                   // 0x0038
        client_id                          m_client_id { };                             // 0x0040
        void                              *m_active_rpc_handle { };                     // 0x0050
        void                              *m_thread_local_storage { };                  // 0x0058
        peb                               *m_process_environment_block { };             // 0x0060
        uint32_t                           m_last_error_value { };                      // 0x0068
        uint32_t                           m_count_of_owned_critical_sections { };      // 0x006C
        void                              *m_csr_client_thread { };                     // 0x0070
        void                              *m_win_32_thread_info { };                    // 0x0078
        std::array< const uint32_t, 0x1A > m_user_32_reserved { };                      // 0x0080
        std::array< const uint32_t, 0x5 >  m_user_reserved { };                         // 0x00E8
        void                              *m_wow32_reserved { };                        // 0x0100
        uint32_t                           m_current_locale { };                        // 0x0108
        uint32_t                           m_fp_soft_status_register { };               // 0x010C
        std::array< const void *, 0x10 >   m_reserved_for_debugger_instrumenation { };  // 0x0110
        std::array< const void *, 0x1E >   m_system_reserved { };                       // 0x0190
        uint8_t                            m_place_holder_compatiblity_mode { };        // 0x0280
        uint8_t                            m_place_holder_hydration_always_explcit { }; // 0x0281
        std::array< const uint8_t, 0xA >   m_place_holder_reserved { };                 // 0x0282
        uint32_t                           m_proxied_process_id { };                    // 0x028C
        activation_context_stack           m_activation_context_stack { };              // 0x0290
        std::array< const uint8_t, 0x8 >   m_working_on_behalf_ticket { };              // 0x02B8
        int32_t                            m_exception_code { };                        // 0x02C0
        std::array< const uint8_t, 0x4 >   m_unknown_0 { };                             // 0x02C4
        activation_context_stack          *m_activation_context_stack_pointer { };      // 0x02C8
        uint64_t                           m_instrumenation_callback_sp { };            // 0x02D0
        uint64_t                           m_instrumenation_callback_previous_pc { };   // 0x02D8
        uint64_t                           m_instrumenation_callback_previous_sp { };   // 0x02E0
        uint32_t                           m_tx_fs_context { };                         // 0x02E8
        uint8_t                            m_intrumentation_callback_disabled { };      // 0x02EC
        uint8_t                            m_unaligned_load_store_exceptions { };       // 0x02ED
        std::array< const uint8_t, 0x2 >   m_unknown_1 { };                             // 0x02EE
        gdi_teb_batch                      m_gdi_teb_batch { };                         // 0x02F0
        client_id                          m_real_client_id { };                        // 0x07D8
        void                              *m_gdi_cached_process_handle { };             // 0x07E8
        uint32_t                           m_gdi_client_pid { };                        // 0x07F0
        uint32_t                           m_gdi_client_tid { };                        // 0x07F4
        void                              *m_gdi_thread_local_info { };                 // 0x07F8
        std::array< const uint64_t, 0x3E > m_win32_client_info { };                     // 0x0800
        std::array< const void *, 0xE9 >   m_gl_dispatch_table { };                     // 0x09F0
        std::array< const uint64_t, 0x1D > m_gl_reserved_1 { };                         // 0x1138
        void                              *m_gl_reserved_2 { };                         // 0x1220
        void                              *m_gl_section_info { };                       // 0x1228
        void                              *m_gl_section { };                            // 0x1230
        void                              *m_gl_table { };                              // 0x1238
        void                              *m_gl_current_rc { };                         // 0x1240
        void                              *m_gl_context { };                            // 0x1248
        uint32_t                           m_last_status_value { };                     // 0x1250
        std::array< const uint8_t, 0x4 >   m_unknown_2 { };                             // 0x1254
        unicode_string                     m_static_unicode_string { };                 // 0x1258
        std::array< const wchar_t, 0x105 > m_static_unicode_buffer { };                 // 0x1268
        std::array< const uint8_t, 0x6 >   m_unknown_3 { };                             // 0x1472
        void                              *m_deallocation_stack { };                    // 0x1478
        std::array< const void *, 0x40 >   m_tls_slots { };                             // 0x1480
        list_entry                         m_tls_links { };                             // 0x1680
        void                              *m_vdm { };                                   // 0x1690
        void                              *m_reserved_for_nt_rpc { };                   // 0x1698
        std::array< const void *, 0x2 >    m_debug_reserved { };                        // 0x16A0
        uint32_t                           m_hard_errror_mode { };                      // 0x16B0
        std::array< const uint8_t, 0x4 >   m_unknown_4 { };                             // 0x16B4
        std::array< const void *, 0xB >    m_instrumentation { };                       // 0x16B8
        guid                               m_activity_id { };                           // 0x1710
        void                              *m_sub_process_tag { };                       // 0x1720
        void                              *m_perf_lib_data { };                         // 0x1728
        void                              *m_etw_trace_data { };                        // 0x1730
        void                              *m_win_sock_data { };                         // 0x1738
        uint32_t                           m_gdi_batch_count { };                       // 0x1740
        processor_number                   m_current_ideal_processor { };               // 0x1744
        uint32_t                           m_guaranteed_stack_bytes { };                // 0x1748
        std::array< const uint8_t, 0x4 >   m_unknown_5 { };                             // 0x174C
        void                              *m_reserved_for_pref { };                     // 0x1750
        void                              *m_reserved_for_ole { };                      // 0x1758
        uint32_t                           m_waiting_on_loader_lock { };                // 0x1760
        std::array< const uint8_t, 0x4 >   m_unknown_6 { };                             // 0x1764
        void                              *m_saved_priority_state { };                  // 0x1768
        uint64_t                           m_reserved_for_code_coverage { };            // 0x1770
        void                              *m_threadpool_data { };                       // 0x1778
        void                              *m_tls_expansion_slots { };                   // 0x1780
        void                              *m_chpe_v2_cpu_area_info { };                 // 0x1788
        std::array< const uint8_t, 0x8 >   m_unknown_7 { };                             // 0x1790
        uint32_t                           m_mui_generation { };                        // 0x1798
        uint32_t                           m_is_impersonating { };                      // 0x179C
        void                              *m_nls_cache { };                             // 0x17A0
        void                              *m_shim_data { };                             // 0x17A8
        uint32_t                           m_heap_data { };                             // 0x17B0
        std::array< const uint8_t, 0x4 >   m_unknown_8 { };                             // 0x17B4
        void                              *m_current_transaction_handle { };            // 0x17B8
        teb_active_frame                  *m_active_frame { };                          // 0x17C0
        void                              *m_fls_data { };                              // 0x17C8
        void                              *m_prefered_langauges { };                    // 0x17D0
        void                              *m_user_prefered_langauges { };               // 0x17D8
        void                              *m_merged_prefeered_langauges { };            // 0x17E0
        uint32_t                           m_mui_impersonation { };                     // 0x17E8
        uint16_t                           m_cross_teb_flags { };                       // 0x17EC
        uint16_t                           m_same_teb_flags { };                        // 0x17EE
        void                              *m_txn_scope_enter_callback { };              // 0x17F0
        void                              *m_txn_scope_exit_callback { };               // 0x17F8
        void                              *m_txn_scope_context { };                     // 0x1800
        uint32_t                           m_lock_count { };                            // 0x1808
        int32_t                            m_wow_teb_offset { };                        // 0x180C
        void                              *m_resource_return_value { };                 // 0x1810
        void                              *m_reserved_for_wdf { };                      // 0x1818
        uint64_t                           m_reserved_for_crt { };                      // 0x1820
        guid                               m_effective_container_id { };                // 0x1828
        uint64_t                           m_last_sleep_counter { };                    // 0x1838
        uint32_t                           m_spin_call_count { };                       // 0x1840
        std::array< const uint8_t, 0x4 >   m_unknown_9 { };                             // 0x1844
        uint64_t                           m_extended_feature_disable_mask { };         // 0x1848
    };                                                                                  // Size: 0x1850

    static_assert( sizeof( teb ) == 0x1850 );

    struct rtl_balanced_node {
        std::array< const rtl_balanced_node *, 2 > m_children { };     // 0x0000
        uint64_t                                   m_parent_value { }; // 0x0010
    };                                                                 // Size: 0x0018

    static_assert( sizeof( rtl_balanced_node ) == 0x0018 );

    struct ldr_data_table_entry {
        list_entry        m_in_load_order_links { };            // 0x0000
        list_entry        m_in_memory_order_links { };          // 0x0010
        list_entry        m_in_initialization_order_links { };  // 0x0020
        void             *m_dll_base { };                       // 0x0030
        void             *m_entry_point { };                    // 0x0038
        uint32_t          m_size_of_image { };                  // 0x0040
        unicode_string    m_full_dll_name { };                  // 0x0048
        unicode_string    m_base_dll_name { };                  // 0x0058
        uint32_t          m_flags { };                          // 0x0068
        uint16_t          m_load_count { };                     // 0x006C
        uint16_t          m_tls_index { };                      // 0x006E
        list_entry        m_hash_links { };                     // 0x0070
        uint32_t          m_time_date_stamp { };                // 0x0080
        void             *m_entry_point_activation_context { }; // 0x0088
        void             *m_lock { };                           // 0x0090
        void             *m_ddag_node { };                      // 0x0098
        list_entry        m_node_module_links { };              // 0x00A0
        void             *m_load_context { };                   // 0x00B0
        void             *m_parent_dll_base { };                // 0x00B8
        void             *m_switch_back_context { };            // 0x00C0
        rtl_balanced_node m_base_address_index_node { };        // 0x00C8
        rtl_balanced_node m_mapping_info_index_node { };        // 0x00E0
        uint64_t          m_original_base { };                  // 0x00F8
        uint64_t          m_load_time { };                      // 0x0100
        uint32_t          m_base_name_hash_value { };           // 0x0108
        uint32_t          m_load_reason { };                    // 0x010C
        uint32_t          m_implicit_path_options { };          // 0x0110
        uint32_t          m_reference_count { };                // 0x0114
        uint32_t          m_dependent_load_flags { };           // 0x0118
        uint8_t           m_signature_level { };                // 0x011C
        uint32_t          m_check_sum { };                      // 0x0120
        void             *m_active_patch_image_base { };        // 0x0128
        uint32_t          hot_patch_state { };                  // 0x0130
    };                                                          // Size: 0x0138

    static_assert( sizeof( ldr_data_table_entry ) == 0x0138 );

    struct image_dos_header {
        uint16_t                          m_magic { };     // 0x0000
        uint16_t                          m_cblp { };      // 0x0002
        uint16_t                          m_cp { };        // 0x0004
        uint16_t                          m_crlc { };      // 0x0006
        uint16_t                          m_cparhdr { };   // 0x0008
        uint16_t                          m_min_alloc { }; // 0x000A
        uint16_t                          m_max_alloc { }; // 0x000C
        uint16_t                          m_ss { };        // 0x000E
        uint16_t                          m_sp { };        // 0x0010
        uint16_t                          m_csum { };      // 0x0012
        uint16_t                          m_ip { };        // 0x0014
        uint16_t                          m_cs { };        // 0x0016
        uint16_t                          m_lfarlc { };    // 0x0018
        uint16_t                          m_ovno { };      // 0x001A
        std::array< const uint16_t, 0x4 > m_res_1 { };     // 0x001C
        uint16_t                          m_oem_id { };    // 0x0024
        uint16_t                          m_oem_info { };  // 0x0026
        std::array< const uint16_t, 0xA > m_res_2 { };     // 0x0028
        uint32_t                          m_lfanew { };    // 0x003C
    };                                                     // Size: 0x0040

    static_assert( sizeof( image_dos_header ) == 0x0040 );

    struct image_file_header {
        uint16_t m_machine { };                 // 0x0000
        uint16_t m_number_of_sections { };      // 0x0002
        uint32_t m_time_date_stamp { };         // 0x0004
        uint32_t m_pointer_to_symbol_table { }; // 0x0008
        uint32_t m_number_of_symbols { };       // 0x000C
        uint16_t m_size_of_optional_header { }; // 0x0010
        uint16_t m_characteristics { };         // 0x0012
    };                                          // Size: 0x0014

    static_assert( sizeof( image_file_header ) == 0x0014 );

    struct image_data_directory {
        uint32_t m_virtual_address { }; // 0x0000
        uint32_t m_size { };            // 0x0004
    };                                  // Size: 0x0008

    static_assert( sizeof( image_data_directory ) == 0x0008 );

    struct image_optional_header_64 {
        uint16_t                                 m_magic { };                          // 0x0000
        uint8_t                                  m_major_linker_version { };           // 0x0002
        uint8_t                                  m_minor_linker_version { };           // 0x0003
        uint32_t                                 m_size_of_code { };                   // 0x0004
        uint32_t                                 m_size_of_initialized_data { };       // 0x0008
        uint32_t                                 m_size_of_uninitialized_data { };     // 0x000C
        uint32_t                                 m_address_of_entry_point { };         // 0x0010
        uint32_t                                 m_base_of_code { };                   // 0x0014
        uint64_t                                 m_image_base { };                     // 0x0018
        uint32_t                                 m_section_alignment { };              // 0x0020
        uint32_t                                 m_file_alignment { };                 // 0x0024
        uint16_t                                 m_major_operating_system_version { }; // 0x0028
        uint16_t                                 m_minor_operating_system_version { }; // 0x002A
        uint16_t                                 m_major_image_version { };            // 0x002C
        uint16_t                                 m_minor_image_version { };            // 0x002E
        uint16_t                                 m_major_sub_system_version { };       // 0x0030
        uint16_t                                 m_minor_sub_system_version { };       // 0x0032
        uint32_t                                 m_win32_version_value { };            // 0x0034
        uint32_t                                 m_size_of_image { };                  // 0x0038
        uint32_t                                 m_size_of_headers { };                // 0x003C
        uint32_t                                 m_check_sum { };                      // 0x0040
        uint16_t                                 m_sub_system { };                     // 0x0044
        uint16_t                                 m_dll_characteristics { };            // 0x0046
        uint64_t                                 m_size_of_stack_reserve { };          // 0x0048
        uint64_t                                 m_size_of_stack_commit { };           // 0x0050
        uint64_t                                 m_size_of_heap_reserve { };           // 0x0058
        uint64_t                                 m_size_of_heap_commit { };            // 0x0060
        uint32_t                                 m_loader_flags { };                   // 0x0068
        uint32_t                                 m_number_of_rva_and_sizes { };        // 0x006C
        std::array< image_data_directory, 0x10 > m_data_directory;                     // 0x0070
    };                                                                                 // Size: 0x00F0

    static_assert( sizeof( image_optional_header_64 ) == 0x00F0 );

    struct image_nt_headers_64 {
        uint32_t                 m_signature { };       // 0x0000
        image_file_header        m_file_header { };     // 0x0004
        image_optional_header_64 m_optional_header { }; // 0x0018
    };                                                  // Size: 0x0108

    static_assert( sizeof( image_nt_headers_64 ) == 0x0108 );

    struct image_export_directory {
        uint32_t m_characteristics { };          // 0x0000
        uint32_t m_time_date_stamp { };          // 0x0004
        uint16_t m_major_version { };            // 0x0008
        uint16_t m_minor_version { };            // 0x000A
        uint32_t m_name { };                     // 0x000C
        uint32_t m_base { };                     // 0x0010
        uint32_t m_number_of_functions { };      // 0x0014
        uint32_t m_number_of_names { };          // 0x0018
        uint32_t m_address_of_functions { };     // 0x001C
        uint32_t m_address_of_names { };         // 0x0020
        uint32_t m_address_of_name_ordinals { }; // 0x0024
    };                                           // Size: 0x0028

    static_assert( sizeof( image_export_directory ) == 0x0028 );

    struct image_section_header {
        BYTE m_name[ IMAGE_SIZEOF_SHORT_NAME ];

        union {
            DWORD m_physical_address;
            DWORD m_virtual_size;
        } m_misc;

        DWORD m_virtual_address { };         // 0x000C
        DWORD m_size_of_raw_data { };        // 0x0010
        DWORD m_pointer_to_raw_data { };     // 0x0014
        DWORD m_pointer_to_relocations { };  // 0x0018
        DWORD m_pointer_to_line_numbers { }; // 0x001C
        WORD  m_number_of_relocations { };   // 0x0020
        WORD  m_number_of_line_numbers { };  // 0x0022
        DWORD m_characteristics { };         // 0x0024
    };                                       // Size: 0x0028

    static_assert( sizeof( image_section_header ) == 0x0028 );

    _INLINE auto image_first_section( image_nt_headers_64 *ntheader ) {
        return reinterpret_cast< image_section_header * >( reinterpret_cast< ULONG_PTR >( ntheader )
                                                           + _OFFSETOF( image_nt_headers_64, m_optional_header )
                                                           + ( ( ntheader ) )->m_file_header.m_size_of_optional_header );
    }

} // namespace hack::utils::inline memory::inline structs