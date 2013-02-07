#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

#include "typetrait.hpp"
#include "ispointer.hpp"
#include "select.hpp"

#include <unistd.h>

/**
 * \brief Un wrapper autour de std::unary_function qui permet des tests sur les élements d'un conteneur de T à partir d'un PARAM initial
 */
template <typename T, typename PARAM = T> class Comparator : std::unary_function<T, bool> {
public:
    typedef typename Select<is_pointer<PARAM>::value, typename type_trait<PARAM>::const_ptr, typename type_trait<PARAM>::const_ref>::type type_param;
protected:
    Comparator(type_param t): d_t(t) {
    }

    type_param get() const {
        return d_t;
    }
private:
    type_param d_t;
};


#endif // COMPARATOR_HPP
