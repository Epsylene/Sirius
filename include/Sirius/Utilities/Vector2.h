
#include "srspch.h"

namespace Sirius
{
    template <typename T>
    class Vector2
    {
        private:

            float mag, angle;

        public:

            T x, y;

            //////////////////////////////
            /// @brief Default constructor
            Vector2();

            /////////////////////////////////////////
            /// @brief Vector constructor
            /// 
            /// @param x The x coordinate
            /// @param y The y coordinate
            Vector2(T x, T y);

            ///////////////////////////////////////
            /// @brief Vector copy constructor
            /// 
            /// @param vec The vector to be copied
            Vector2(const Vector2<T>& vec);

            //////////////////////////////////////
            /// @brief Vector move constructor
            /// 
            /// @param vec The vector to be moved
            Vector2(Vector2<T>&& vec);

            //////////////////////////////////////
            /// @brief Sets the vector magnitude
            /// 
            /// @param mag The magnitude to be set
            void setMag(float mag);

            //////////////////////////////////////
            /// @brief Sets the vector angle
            /// 
            /// @param alpha The angle to be set
            void setAngle(float alpha);

            //////////////////////////////////////////////////////////
            /// @brief Normalizes the vector (sets the magnitude to 1)
            void normalize();

            //////////////////////////////////////////
            /// @brief Normalizes a given vector
            /// 
            /// @param vec The vector to be normalized
            static void normalize(Vector2<T>& vec);

            ///////////////////////////////////
            /// @brief Get the vector magnitude
            /// 
            /// @return The vector magnitude 
            T getMag() const;

            /////////////////////////////////////////////////////////
            /// @brief Get the given vector magnitude
            /// 
            /// @param vec The vector from which to get the magnitude
            /// @return The given vector's magnitude
            static T getMag(Vector2<T>& vec);

            ///////////////////////////////
            /// @brief Get the vector angle
            /// 
            /// @return The vector angle 
            T getAngle() const;

            /////////////////////////////////////////////////
            /// @brief Get the given vector angle
            /// 
            /// @param The vector from which to get the angle 
            /// @return The given vector's angle 
            static T getAngle(Vector2<T>& vec);

            ////////////////////////////////////////////////////
            /// @brief Dot product with another vector
            /// 
            /// @param v2 The vector to do the dot product with
            /// @return The dot product scalar result
            T dot(Vector2<T>& v2);

            //////////////////////////////////////////
            /// @brief Dot product between two vectors
            /// 
            /// @param v1 The left operand
            /// @param v2 The right operand
            /// @return The dot product scalar result
            static T dot(Vector2<T>& v1, Vector2<T>& v2);

            Vector2<T>& operator=(const Vector2<T>& rhs);
            Vector2<T>& operator=(Vector2<T>&& rhs);
            Vector2<T>& operator+=(const Vector2<T>& rhs);
            Vector2<T>& operator-=(const Vector2<T>& rhs);
            Vector2<T>& operator*=(T scalar);
        
            friend bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
            {
                return (rhs.x == lhs.x) && (rhs.y == lhs.y);
            }

            friend bool operator!=(const Vector2<T>& rhs, const Vector2<T>& lhs)
            {
                return !(rhs == lhs);
            }

            friend Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
            {
                lhs += rhs;

                lhs.mag = static_cast<float>(std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y));
                lhs.angle = static_cast<float>(std::atan2(lhs.y, lhs.x));

                return lhs;
            }

            friend Vector2<T> operator-(const Vector2<T>& vec)
            {
                return { -vec.x, -vec.y };
            }

            friend Vector2<T> operator-(Vector2<T> lhs, Vector2<T>& rhs)
            {
                return lhs + (-rhs);
            }

            friend Vector2<T> operator*(T scalar, const Vector2<T>& vec)
            {
                return { vec.x * scalar, vec.y * scalar };
            }

            friend Vector2<T> operator*(const Vector2<T>& vec, T scalar)
            {
                return { vec.x * scalar, vec.y * scalar };
            }

            friend std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec)
            {
                return out << "(" << vec.x << ", " << vec.y << ")";
            }
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
}

#include "Vector2.tpp"
