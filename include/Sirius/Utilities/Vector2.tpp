
#pragma once

namespace Sirius
{
    template<typename T>
    Vector2<T>::Vector2()
    {
        this->x = 0.f;
        this->y = 0.f;

        mag = 0.f;
        angle = 0.f;
    }

    template<typename T>
    Vector2<T>::Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;

        mag = static_cast<float>(std::sqrt(x * x + y * y));
        angle = static_cast<float>(std::atan2(y, x));
    }

    template<typename T>
    Vector2<T>::Vector2(Vector2<T>& vec)
    {
        x = vec.x;
        y = vec.y;

        mag = static_cast<float>(std::sqrt(x * x + y * y));
        angle = static_cast<float>(std::atan2(y, x));
    }

    template<typename T>
    Vector2<T>::Vector2(Vector2<T>&& vec)
    {
        x = std::move(vec.x);
        y = std::move(vec.y);
        mag = std::move(vec.mag);
        angle = std::move(vec.angle);
    }

    template<typename T>
    void Vector2<T>::setMag(float m)
    {
        this->mag = m;

        x = mag * std::cos(angle);
        y = mag * std::sin(angle);
    }

    template<typename T>
    void Vector2<T>::setAngle(float alpha)
    {
        this->angle = alpha;

        x = mag * std::cos(angle);
        y = mag * std::sin(angle);
    }

    template<typename T>
    void Vector2<T>::normalize()
    {
        mag = 1;

        x = std::cos(angle);
        y = std::sin(angle);
    }

    template<typename T>
    void Vector2<T>::normalize(Vector2<T>& vec)
    {
        vec.mag = 1;

        vec.x = std::cos(vec.angle);
        vec.y = std::sin(vec.angle);
    }

    template<typename T>
    T Vector2<T>::getMag() const
    {
        return static_cast<float>(std::sqrt(x * x + y * y));
    }

    template<typename T>
    T Vector2<T>::getMag(Vector2<T>& vec)
    {
        return static_cast<float>(std::sqrt(vec.x * vec.x + vec.y * vec.y));
    }

    template<typename T>
    T Vector2<T>::getAngle() const
    {
        return std::atan2(y, x);
    }

    template<typename T>
    T Vector2<T>::getAngle(Vector2<T>& vec)
    {
        return std::atan2(vec.y, vec.x);
    }

    template<typename T>
    Vector2<T>& Vector2<T>::dot(Vector2<T>& v2)
    {
        x * v2.x + y * v2.y;

        return *this;
    }

    template<typename T>
    T Vector2<T>::dot(Vector2<T>& v1, Vector2<T>& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    // ---------- OPERATOR OVERLOADS ---------- //
    
    template<typename T>
    Vector2<T>& Vector2<T>::operator=(Vector2<T> rhs)
    {
        std::swap(x, rhs.x);
        std::swap(y, rhs.y);
        std::swap(mag, rhs.mag);
        std::swap(angle, rhs.angle);

        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        mag = static_cast<float>(std::sqrt(x * x + y * y));
        angle = static_cast<float>(std::atan2(y, x));

        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        mag = static_cast<float>(std::sqrt(x * x + y * y));
        angle = static_cast<float>(std::atan2(y, x));

        return *this;
    }

    template<typename T>
    bool operator==(Vector2<T>& rhs, Vector2<T>& lhs)
    {
        return rhs.x == lhs.x && rhs.y == lhs.y;
    }

    template<typename T>
    bool operator!=(Vector2<T>& rhs, Vector2<T>& lhs)
    {
        return !(rhs == lhs);
    }

    template<typename T>
    Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs)
    {
        lhs += rhs;

        lhs.mag = static_cast<float>(std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y));
        lhs.angle = static_cast<float>(std::atan2(lhs.y, lhs.x));

        return lhs;
    }

    template<typename T>
    Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs)
    {
        lhs -= rhs;

        lhs.mag = static_cast<float>(std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y));
        lhs.angle = static_cast<float>(std::atan2(lhs.y, lhs.x));

        return lhs;
    }
}