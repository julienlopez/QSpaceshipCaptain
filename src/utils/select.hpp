#ifndef SELECT_HPP
#define SELECT_HPP

/*
* class template Select
* Selectionne un des deux type en fonction d'une valeur booléenne constante
* Utilisation: Select<flag, T, U>::type
* où:
* FLAG est un booléen constant lors de la compilation
* T et U sont des types
* type vaut T si flag vaut true, U sinon.
*/
template<bool flag, typename T, typename U> struct Select
{
    typedef T type;
};

template<typename T, typename U> struct Select<false, T, U>
{
    typedef U type;
};

#endif // SELECT_HPP
