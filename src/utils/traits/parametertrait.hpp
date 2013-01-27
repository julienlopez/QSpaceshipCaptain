#ifndef __PARAMETERTRAIT_HPP__
#define __PARAMETERTRAIT_HPP__

template<class T> class ParameterTrait
{
public:
	typedef T& reference;
    typedef const T& const_reference;
};

template<class T> class ParameterTrait<T*>
{
public:
    typedef T* reference;
    typedef const T* const_reference;
};

#endif
