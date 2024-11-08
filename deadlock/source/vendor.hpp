#pragma once

#if defined( __x86_64__ ) || defined( _M_AMD64 ) || defined( _M_X64 )
#define _ARCH_X64
#elif defined( __i386 ) || defined( _M_IX86 )
#define _ARCH_X86
#endif

#define _COMBINE_IMPL( x, y ) x##y
#define _COMBINE( x, y )      _COMBINE_IMPL( x, y )

#define _PAD( bytes )                                                                    \
  private:                                                                               \
    [[maybe_unused]] std::array< std::byte, bytes > _COMBINE( __pad_, __COUNTER__ ) { }; \
                                                                                         \
  public:

#define _CHECK_SIZE( type, size )                                                                \
    static_assert( sizeof( type ) >= ( size ), #type " too small: sizeof(" #type ") < " #size ); \
    static_assert( sizeof( type ) <= ( size ), #type " too large: sizeof(" #type ") > " #size )

/// Function calling conventions
#if defined( __GNUC__ ) || defined( __clang__ )
#define _CDECL       __attribute__( ( cdecl ) )
#define _STDCALL     __attribute__( ( stdcall ) )
#define _THISCALL    __attribute__( ( thiscall ) )
#define _FASTCALL    __attribute__( ( fastcall ) )
#define _VECTORCALL  __attribute__( ( vectorcall ) )
#define _HIDDEN      __attribute__( ( visibility( "hidden" ) ) )
#define _NAKED       __attribute__( ( naked ) )
#define _CONSTRUCTOR __attribute__( ( constructor ) )
#define _LIKE( x )   __builtin_expect( static_cast< bool >( x ), 1 )
#define _UNLIKE( x ) __builtin_expect( static_cast< bool >( x ), 0 )
#elif defined( _MSC_VER )
#define _CDECL      __cdecl
#define _STDCALL    __stdcall
#define _THISCALL   __thiscall
#define _FASTCALL   __fastcall
#define _VECTORCALL __vectorcall
#define _HIDDEN
#define _NAKED       __declspec( naked )
#define _LIKE( x )   static_cast< bool >( x )
#define _UNLIKE( x ) static_cast< bool >( x )
#else
#define _CDECL
#define _STDCALL
#define _THISCALL
#define _FASTCALL
#define _VECTORCALL
#define _HIDDEN
#define _NAKED
#endif

/// Inline and noinline attributes
#if defined( __GNUC__ ) || defined( __clang__ )
#define _INLINE __attribute__( ( always_inline ) ) inline
#elif defined( _MSC_VER )
#define _INLINE __pragma( warning( suppress : 4714 ) ) inline __forceinline
#else
#define _INLINE inline

#endif
#if defined( __GNUC__ ) || defined( __clang__ )
#define _NOINLINE __attribute__( ( noinline ) )
#elif defined( _MSC_VER )
#define _NOINLINE __declspec( noinline )
#else
#define _NOINLINE
#endif

#if defined( __cplusplus ) && defined( __has_cpp_attribute )
#define _HAS_ATTRIBUTE( attrib, value ) ( __has_cpp_attribute( attrib ) >= value )
#else
#define _HAS_ATTRIBUTE( attrib, value ) ( 0 )
#endif

#if _HAS_ATTRIBUTE( likely, 201803L )
#define _ATTR_LIKELY likely
#else
#define _ATTR_LIKELY
#endif

#if _HAS_ATTRIBUTE( unlikely, 201803L )
#define _ATTR_UNLIKELY unlikely
#else
#define _ATTR_UNLIKELY
#endif

#if defined( __has_builtin )
#define _HAS_BUILTIN( feature ) __has_builtin( feature )
#else
#define CS2_HAS_BUILTIN( feature ) 0
#endif

#if _HAS_BUILTIN( __builtin_debugtrap )
#define _DEBUG_BREAK( ) __builtin_debugtrap( )
#endif

#if defined( _DEBUG_BREAK )
#if defined( _DEBUG )
#define _ASSERT( expression ) static_cast< void >( static_cast< bool >( expression ) || ( ( _DEBUG_BREAK( ), 0 ) != 0 ) )
#elif _HAS_BUILTIN( __builtin_unreachable )
#define _ASSERT( expression ) static_cast< void >( static_cast< bool >( expression ) || ( __builtin_unreachable( ), 0 ) )
#else
#define _ASSERT( expression ) static_cast< void >( expression )
#endif
#endif

#if _HAS_BUILTIN( __builtin_offsetof )
#define _OFFSETOF( type, member ) __builtin_offsetof( type, member )
#else
#define _OFFSETOF( type, member ) \
    ( reinterpret_cast< std::size_t >( &( reinterpret_cast< type * >( sizeof( type ) )->member ) ) - sizeof( type ) )
#endif

namespace hack {
    template < typename type, typename... compare_types >
    concept is_any_of = ( std::same_as< type, compare_types > || ... );

    inline namespace conventions {
        template < typename result_t, typename... args_t >
        using func_t = result_t ( * )( args_t... );

        template < typename result_t, typename class_t, typename... args_t >
        using member_func_t = result_t ( class_t::* )( args_t... );

        template < typename result_t, typename... args_t >
        using cdecl_t = result_t( _CDECL * )( args_t... );

        template < typename result_t, typename... args_t >
        using stdcall_t = result_t( _STDCALL * )( args_t... );

        template < typename result_t, typename... args_t >
        using fastcall_t = result_t( _FASTCALL * )( args_t... );

        template < typename result_t, typename... args_t >
        using thiscall_t = result_t( _THISCALL * )( args_t... );
    } // namespace conventions
} // namespace hack