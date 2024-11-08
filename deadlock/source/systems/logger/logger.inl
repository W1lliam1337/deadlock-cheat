#pragma once
#include "logger.hpp"

namespace hack::systems {
    static inline constexpr std::array k_log_level_strings = { " [INFO] ", " [WARNING] ", " [ERROR] " };

    _INLINE logger_t::logger_t( const std::string &file_name ) noexcept {
        if ( AllocConsole( ) ) {
            std::freopen( "CONOUT$", "w", stdout );
            std::freopen( "CONOUT$", "w", stderr );
        }

        if ( !std::filesystem::exists( "C:\\deadlock\\" ) )
            std::filesystem::create_directory( "C:\\deadlock\\" );

        m_log_file.open( file_name, std::ios::app );
        if ( !m_log_file.is_open( ) ) {
            std::printf( "Failed to open log file: %s\n", file_name.c_str( ) );
        }
    }

    _INLINE logger_t::~logger_t( ) noexcept {
        if ( m_log_file.is_open( ) ) {
            m_log_file.close( );
        }

        std::fclose( stdout );
        std::fclose( stderr );
        FreeConsole( );
    }

    _INLINE std::string logger_t::log_level_to_string( e_log_level level ) noexcept {
        if ( static_cast< std::size_t >( level ) < k_log_level_strings.size( ) ) {
            return k_log_level_strings[ static_cast< std::size_t >( level ) ];
        }
        return "[UNKNOWN] ";
    }

    _INLINE std::string logger_t::current_timestamp( ) noexcept {
        const auto now { std::chrono::system_clock::now( ) };
        const auto now_c { std::chrono::system_clock::to_time_t( now ) };
        auto       oss { std::ostringstream {} };
        oss << std::put_time( std::localtime( &now_c ), "%Y-%m-%d %H:%M:%S" );
        return oss.str( );
    }

    _INLINE void logger_t::log( const e_log_level level, const std::string &message ) const noexcept {
        std::lock_guard lock( m_mutex );
        {
            auto log_entry { current_timestamp( ) + log_level_to_string( level ) + message };

            // Log to console
            std::printf( ( log_entry + "\n" ).c_str( ) );

            // Log to file
            if ( m_log_file.is_open( ) ) {
                m_log_file << log_entry << std::endl;
            }
        }
    }

    template < typename... Args >
    void logger_t::log( const e_log_level level, const std::string &format_str, Args &&...args ) const noexcept {
        const auto message { std::format( format_str, std::forward< Args >( args )... ) };
        log( level, message );
    }
} // namespace hack::systems