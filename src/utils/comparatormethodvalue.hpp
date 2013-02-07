#ifndef COMPARATORMETHODVALUE_HPP
#define COMPARATORMETHODVALUE_HPP

#include "comparator.hpp"

#include <boost/function.hpp>

template<typename CLASS, typename T> class ComparatorMethodValue : public Comparator<CLASS, T>
{
    typedef Comparator<CLASS, T> base;

public:
    typedef boost::function<T (const CLASS&)> type_callback;

    ComparatorMethodValue(const type_callback& callback, typename base::type_param value): base(value), m_callback(callback)
    {}

    bool operator()(const CLASS& p) const
    {
        return m_callback(p) == base::get();
    }

private:
    type_callback m_callback;
};

#endif // COMPARATORMETHODVALUE_HPP
