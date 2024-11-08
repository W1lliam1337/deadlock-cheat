#pragma once

namespace hack::valve::inline interfaces {
    inline const auto g_alloc_func = systems::get_export< fastcall_t< void *, std::size_t > >( "tier0.dll", "MemAlloc_AllocFunc" );
    inline const auto g_realloc_func
        = systems::get_export< fastcall_t< void *, void *, std::size_t > >( "tier0.dll", "MemAlloc_ReallocFunc" );
    inline const auto g_free_func    = systems::get_export< fastcall_t< void, void    *> >( "tier0.dll", "MemAlloc_FreeFunc" );
    inline const auto g_str_dup_func = systems::get_export< fastcall_t< char *, const char * > >( "tier0.dll", "MemAlloc_StrDupFunc" );
} // namespace hack::valve::inline interfaces