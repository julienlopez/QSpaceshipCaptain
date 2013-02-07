#ifndef ISPOINTER_HPP
#define ISPOINTER_HPP

template<class T> struct is_pointer {
    static const bool value = false;
};

template<class T> struct is_pointer<T*> {
    static const bool value = true;
};

template<class T> struct is_pointer<const T*> {
    static const bool value = true;
};

template<class T> struct is_pointer<const T* const> {
    static const bool value = true;
};

template<class T> struct is_pointer<T* const> {
    static const bool value = true;
};

#endif // ISPOINTER_HPP
