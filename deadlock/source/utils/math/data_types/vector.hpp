#pragma once
#include "imgui/imgui.h"

namespace hack::utils::inline math {
    enum class e_axis {
        x = 0, ///< X-axis (index 0)
        y = 1, ///< Y-axis (index 1)
        z = 2  ///< Z-axis (index 2)
    };

    template < std::size_t N >
    struct vec_t {
        static_assert( N == 2 || N == 3, "Only 2D and 3D vectors are supported." );

        /**
         * @brief Default constructor, initializes all components to zero.
         */
        constexpr vec_t( ) noexcept = default;

        /**
         * @brief Constructor that initializes the vector with specific values.
         * @param args Initial values for the vector components.
         */
        template < typename... Args >
            requires ( sizeof...( Args ) == N )
        explicit constexpr vec_t( Args... args ) noexcept : m_data { static_cast< float >( args )... } { }

        /**
         * @brief Accesses the component at the given index.
         * @param i Index of the component to access (0-based).
         * @return Reference to the vector component.
         */
        constexpr float &operator[] ( std::size_t i ) noexcept {
            return m_data[ i ];
        }

        /**
         * @brief Accesses the component at the given index (const version).
         * @param i Index of the component to access (0-based).
         * @return Constant reference to the vector component.
         */
        constexpr const float &operator[] ( std::size_t i ) const noexcept {
            return m_data[ i ];
        }

        float &operator[] ( e_axis axis ) {
            if constexpr ( N == 2 ) {
                if ( axis == e_axis::z ) {
                    throw std::out_of_range( "Z axis is not valid for 2D vectors." );
                }
            }
            return m_data[ static_cast< std::size_t >( axis ) ];
        }

        /**
         * @brief Adds another vector to this vector.
         * @param other Vector to add.
         * @return Reference to the resulting vector.
         */
        constexpr vec_t &operator+= ( const vec_t &other ) noexcept {
            for ( std::size_t i { }; i < N; ++i )
                m_data[ i ] += other[ i ];
            return *this;
        }

        /**
         * @brief Subtracts another vector from this vector.
         * @param other Vector to subtract.
         * @return Reference to the resulting vector.
         */
        constexpr vec_t &operator-= ( const vec_t &other ) noexcept {
            for ( std::size_t i { }; i < N; ++i )
                m_data[ i ] -= other[ i ];
            return *this;
        }

        /**
         * @brief Multiplies the vector by a scalar value.
         * @param scalar Scalar value to multiply by.
         * @return Reference to the resulting vector.
         */
        constexpr vec_t &operator*= ( float scalar ) noexcept {
            for ( std::size_t i { }; i < N; ++i )
                m_data[ i ] *= scalar;
            return *this;
        }

        /**
         * @brief Divides the vector by a scalar value.
         * @param scalar Scalar value to divide by.
         * @return Reference to the resulting vector.
         */
        constexpr vec_t &operator/= ( float scalar ) noexcept {
            for ( std::size_t i { }; i < N; ++i )
                m_data[ i ] /= scalar;
            return *this;
        }

        /**
         * @brief Computes the length (magnitude) of the vector.
         * @return Length of the vector.
         */
        [[nodiscard]] constexpr float length( ) const noexcept {
            auto sum { 0.0f };
            for ( const auto &val : m_data )
                sum += val * val;
            return std::sqrt( sum );
        }

        /**
         * @brief Normalizes the vector to a unit vector.
         * @return Normalized vector.
         */
        [[nodiscard]] constexpr vec_t normalized( ) const noexcept {
            const auto len { length( ) };
            return ( *this ) / ( len > 0.0f ? len : 1.0f ); // Avoid division by zero
        }

        /**
         * @brief Computes the dot product with another vector.
         * @param other Vector to compute the dot product with.
         * @return Dot product result.
         */
        [[nodiscard]] constexpr float dot( const vec_t &other ) const noexcept {
            auto result { 0.0f };
            for ( std::size_t i = 0; i < N; ++i )
                result += m_data[ i ] * other[ i ];
            return result;
        }

        /**
         * @brief Computes the cross product with another vector.
         * @note Only defined for 3D vectors (vec3_t).
         * @param other 3D vector to compute the cross product with.
         * @return Resulting 3D vector from the cross product.
         */
        [[nodiscard]] constexpr vec_t< 3 > cross( const vec_t< 3 > &other ) const
            requires ( N == 3 )
        {
            return vec_t< 3 > { m_data[ 1 ] * other[ 2 ] - m_data[ 2 ] * other[ 1 ], m_data[ 2 ] * other[ 0 ] - m_data[ 0 ] * other[ 2 ],
                                m_data[ 0 ] * other[ 1 ] - m_data[ 1 ] * other[ 0 ] };
        }

        /**
         * @brief Compares two vectors for equality.
         * @param other Vector to compare with.
         * @return True if vectors are equal, false otherwise.
         */
        constexpr bool operator== ( const vec_t &other ) const noexcept = default;

      private:
        std::array< float, N > m_data { }; ///< Array holding vector components.
    };

    /**
     * @brief Adds two vectors.
     * @tparam N Dimension of the vectors.
     * @param lhs Left-hand side vector.
     * @param rhs Right-hand side vector.
     * @return Resulting vector after addition.
     */
    template < std::size_t N >
    constexpr vec_t< N > operator+ ( const vec_t< N > &lhs, const vec_t< N > &rhs ) noexcept {
        vec_t< N > result  = lhs;
        result            += rhs;
        return result;
    }

    /**
     * @brief Subtracts two vectors.
     * @tparam N Dimension of the vectors.
     * @param lhs Left-hand side vector.
     * @param rhs Right-hand side vector.
     * @return Resulting vector after subtraction.
     */
    template < std::size_t N >
    constexpr vec_t< N > operator- ( const vec_t< N > &lhs, const vec_t< N > &rhs ) noexcept {
        vec_t< N > result  = lhs;
        result            -= rhs;
        return result;
    }

    /**
     * @brief Multiplies a vector by a scalar.
     * @tparam N Dimension of the vector.
     * @param vec Vector to multiply.
     * @param scalar Scalar value to multiply by.
     * @return Resulting vector after scalar multiplication.
     */
    template < std::size_t N >
    constexpr vec_t< N > operator* ( const vec_t< N > &vec, float scalar ) noexcept {
        vec_t< N > result  = vec;
        result            *= scalar;
        return result;
    }

    /**
     * @brief Divides a vector by a scalar.
     * @tparam N Dimension of the vector.
     * @param vec Vector to divide.
     * @param scalar Scalar value to divide by.
     * @return Resulting vector after scalar division.
     */
    template < std::size_t N >
    constexpr vec_t< N > operator/ ( const vec_t< N > &vec, float scalar ) noexcept {
        vec_t< N > result  = vec;
        result            /= scalar;
        return result;
    }

    using vec2_t = vec_t< 2 >; ///< Alias for 2D vector
    using vec3_t = vec_t< 3 >; ///< Alias for 3D vector
} // namespace hack::utils::inline math