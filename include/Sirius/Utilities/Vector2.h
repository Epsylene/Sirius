
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
            Vector2(Vector2<T>& vec);

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

            Vector2<T>& dot(Vector2<T>& v2);
            static T dot(Vector2<T>& v1, Vector2<T>& v2);

            Vector2<T>& operator=(Vector2<T> rhs);
            Vector2<T>& operator+=(const Vector2<T>& rhs);
            Vector2<T>& operator-=(const Vector2<T>& rhs);
            friend bool operator==(Vector2<T>& lhs, Vector2<T>& rhs);
            friend bool operator!=(Vector2<T>& rhs, Vector2<T>& lhs);
            friend Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs);
            friend Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs);

            friend std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec)
            {
                return out << "(" << vec.x << ", " << vec.y << ")";
            }
    };
}

#include "Vector2.tpp"
