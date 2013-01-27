#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<class T> class Singleton {
public:
    static T& instance() {
        static T i;
        return i;
    }

private:
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);

protected:
    Singleton() {}
};

#endif // SINGLETON_HPP
