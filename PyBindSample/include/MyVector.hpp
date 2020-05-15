#pragma once

#include <vector>
#include <sstream>


class MyVector
{
public:
    MyVector()
        : m_data() { }

    MyVector(size_t size)
        : m_data(size) { }

    MyVector(size_t size, double init)
        : m_data(size)
    {
        for (size_t i = 0; i < size; ++i)
            m_data[i] = init;
    }

    double& at(const size_t idx)
    {
        return m_data.at(idx);
    }

    const double& at(const size_t idx) const
    {
        return m_data.at(idx);
    }

    double& operator[](const size_t idx)
    {
        return m_data[idx];
    }

    const double& operator[](const size_t idx) const
    {
        return m_data[idx];
    }

    size_t size() const
    {
        return m_data.size();
    }

    MyVector operator+(const MyVector& rhs) const
    {
        if (this->size() != rhs.size()) throw std::exception("Vectors of different lengths");
        MyVector result(*this);
        for (size_t i = 0; i < size(); ++i)
            result[i] += rhs[i];
        return result;
    }

    MyVector operator-(const MyVector& rhs) const
    {
        if (this->size() != rhs.size()) throw std::exception("Vectors of different lengths");
        MyVector result(*this);
        for (size_t i = 0; i < size(); ++i)
            result[i] -= rhs[i];
        return result;
    }

    MyVector operator*(const MyVector& rhs) const
    {
        if (this->size() != rhs.size()) throw std::exception("Vectors of different lengths");
        MyVector result(*this);
        for (size_t i = 0; i < size(); ++i)
            result[i] *= rhs[i];
        return result;
    }

    MyVector operator/(const MyVector& rhs) const
    {
        if (this->size() != rhs.size()) throw std::exception("Vectors of different lengths");
        MyVector result(*this);
        for (size_t i = 0; i < size(); ++i)
            result[i] /= rhs[i];
        return result;
    }

    std::string toString() const
    {
        std::ostringstream os;
        os << "{";
        for (size_t i = 0, size = m_data.size(); i < size; ++i)
            os << m_data[i] << (i + 1 < size ? "," : "");
        os << "}";
        return os.str();
    }

private:
    std::vector<double> m_data;
};

