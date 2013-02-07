#ifndef TYPETRAIT_HPP
#define TYPETRAIT_HPP

template<typename T> struct base_type
{
    typedef T type;
};
template<typename T> struct base_type<T*>
{
    typedef T type;
};
template<typename T> struct base_type<const T*>
{
    typedef T type;
};
template<typename T> struct base_type<T&>
{
    typedef T type;
};
template<typename T> struct base_type<const T&>
{
    typedef T type;
};

template<typename T> struct type_trait
{
    typedef typename base_type<T>::type base;
    typedef base& ref;
    typedef const base& const_ref;
    typedef base* ptr;
    typedef const base* const_ptr;
};

#endif // TYPETRAIT_HPP
