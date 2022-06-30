#pragma once
// HEADER ONLY
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>

template<typename T>
class LineFunction{
public:
    LineFunction() = default;
    LineFunction(const sf::Vector2<T>& A, const sf::Vector2<T>& B);
    LineFunction getOrthogonal(const sf::Vector2<T>& point) const;
    LineFunction(const LineFunction& other);
    T operator()(const T& x) const;
    sf::Vector2<T> intersectLines(const LineFunction<T>& other) const;
    bool isWithinBoundries(const sf::Vector2<T>& point) const;
    sf::Vector2<T> getBegin() const;
    sf::Vector2<T> getEnd() const;
    double getA() const;
    double getB() const;
private:
    LineFunction(double a, double b);
    double m_a{};
    double m_b{};
    sf::Vector2<T> m_begin_point;
    sf::Vector2<T> m_end_point;
};




// DEFINITIONS

template<typename T>
LineFunction<T>::LineFunction(const sf::Vector2<T>& A, const sf::Vector2<T>& B) {
    m_begin_point = (A.x <= B.x) ? A : B;
    m_end_point = (A.x > B.x) ? A : B;
    m_a = static_cast<double>(m_begin_point.y - m_end_point.y)/(m_begin_point.x - m_end_point.x);
    m_b = m_begin_point.y - static_cast<double>(m_begin_point.y - m_end_point.y)/(m_begin_point.x - m_end_point.x) * m_begin_point.x;
}

template<typename T>
LineFunction<T>::LineFunction(double a, double b)
    : m_a{a}, m_b{b}, m_end_point{}, m_begin_point{} {}

template<typename T>
LineFunction<T>::LineFunction(const LineFunction<T> &other)
    : m_a{other.m_a}, m_b{other.m_b},
      m_begin_point{other.m_begin_point},
      m_end_point{other.m_end_point} {}

template<typename T>
LineFunction<T> LineFunction<T>::getOrthogonal(const sf::Vector2<T>& point) const {
    return LineFunction<T>(-1.f/m_a, static_cast<double>(point.y + (1.f/m_a*point.x)));
}

template<typename T>
T LineFunction<T>::operator()(const T &x) const {
    return m_a * x + m_b;
}

template<typename T>
sf::Vector2<T> LineFunction<T>::intersectLines(const LineFunction<T>& other) const {
    if(m_a == other.m_a){
        throw std::invalid_argument("Lines are parallel");
    }
    T x = (other.m_b - m_b)/(m_a - other.m_a);
    T y = operator()(x);
    return sf::Vector2<T>(x, y);
}

template<typename T>
bool LineFunction<T>::isWithinBoundries(const sf::Vector2<T> &point) const {
    if(point.x >= m_begin_point.x && point.x <= m_end_point.x)  // Checking only x value (Not Ideal solution, but faster)
        return true;
    return false;
}

template<typename T>
sf::Vector2<T> LineFunction<T>::getBegin() const { return m_begin_point; }

template<typename T>
sf::Vector2<T> LineFunction<T>::getEnd() const { return m_end_point; }

template<typename T>
double LineFunction<T>::getA() const { return m_a; }

template<typename T>
double LineFunction<T>::getB() const { return m_b; }
