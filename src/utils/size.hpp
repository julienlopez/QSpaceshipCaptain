#ifndef SIZE_HPP
#define SIZE_HPP

#include <utils/traits/parametertrait.hpp>

template<typename T> class Size
{
public:
    Size(typename   ParameterTrait<T>::const_reference width, typename ParameterTrait<T>::const_reference height)
    {
        m_width = width;
        m_height = height;
    }

    typename ParameterTrait<T>::const_reference width() const
    {
        return m_width;
    }

    typename ParameterTrait<T>::const_reference height() const
    {
        return m_height;
    }

protected:
    void setWidth(typename ParameterTrait<T>::const_reference width)
    {
        m_width = width;
    }

    void setHeight(typename ParameterTrait<T>::const_reference height)
    {
        m_height = height;
    }

private:
    T m_width;
    T m_height;
};

#endif // SIZE_HPP
