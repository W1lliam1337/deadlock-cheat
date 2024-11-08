#pragma once
#include "vendor.hpp"

#if defined( _DEBUG )
#define _ERROR_LOG( ... )          \
    if ( hack::systems::g_logger ) \
    hack::systems::g_logger->log( hack::systems::e_log_level::error, __VA_ARGS__ )
#define _INFO_LOG( ... )           \
    if ( hack::systems::g_logger ) \
    hack::systems::g_logger->log( hack::systems::e_log_level::info, __VA_ARGS__ )
#define _WARN_LOG( ... )           \
    if ( hack::systems::g_logger ) \
    hack::systems::g_logger->log( hack::systems::e_log_level::warning, __VA_ARGS__ )
#else
#define _ERROR_LOG( ... ) void( 0 )
#define _INFO_LOG( ... )  void( 0 )
#define _WARN_LOG( ... )  void( 0 )
#endif

namespace hack::systems {
    enum class e_log_level : std::uint8_t {
        info,
        warning,
        error
    };

    /**
     * @brief Logger class for logging messages to console and file.
     */
    struct logger_t {
        /**
         * @brief Constructs a Logger object.
         * @param file_name Name of the log file.
         */
        _INLINE explicit logger_t( const std::string &file_name ) noexcept;

        /**
         * @brief Logs a message with a specific log level.
         * @param level The log level.
         * @param message The message to log.
         */
        _INLINE void log( e_log_level level, const std::string &message ) const noexcept;

        /**
         * @brief Logs a formatted message with a specific log level.
         * @param level The log level.
         * @param format_str The format string.
         * @param args Arguments for the format string.
         */
        template < typename... args_t >
        void log( e_log_level level, const std::string &format_str, args_t &&...args ) const noexcept;

        /**
         * @brief Destructor that closes the log file.
         */
        _INLINE ~logger_t( ) noexcept;

      private:
        mutable std::ofstream m_log_file { }; ///< Log file stream.
        mutable std::mutex    m_mutex { };    ///< Mutex for thread-safe logging.

        /**
         * @brief Returns a string representation of the log level.
         * @param level The log level.
         * @return String representation of the log level.
         */
        [[nodiscard]] static _INLINE std::string _HIDDEN log_level_to_string( e_log_level level ) noexcept;

        /**
         * @brief Returns the current timestamp as a string.
         * @return Current timestamp.
         */
        [[nodiscard]] static _INLINE std::string _HIDDEN current_timestamp( ) noexcept;
    };

    inline auto g_logger { std::unique_ptr< logger_t > {} };
} // namespace hack::systems

#include "logger.inl"