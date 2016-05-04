/*!\file multigraphallocator.h
*\brief Файл с классом для аллокатора мультиграфа
*/
#ifndef MULTIGRAPHALLOCATOR_H
#define MULTIGRAPHALLOCATOR_H

#include <limits>
#include <iostream>

namespace Multigraph {
    /*!\class MultigraphAllocator
    *\brief Класс аллокатора мультиграфа
    *\ref MultigraphAllocator
    */
    template <class T>
    class MultigraphAllocator
    {
    public:
        typedef T        value_type;
        typedef T*       pointer;
        typedef const T* const_pointer;
        typedef T&       reference;
        typedef const T& const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        template <class U>
        struct rebind
        {
            typedef Multigraph<U> other;
        };

        MultigraphAllocator() {}
        MultigraphAllocator(const MultigraphAllocator&){}

        template <typename U>
        MultigraphAllocator(const MultigraphAllocator<U>&){}

        ~MultigraphAllocator(){}

        /*!\fn  address (reference value) const;
        *\brief Возвращает адрес значения
        *\param [in] value - значение
        *\return адрес значения
        */
        pointer address (reference value) const;

        /*!\fn  address (const_reference value) const;
        *\brief Возвращает адрес значения
        *\param [in] value - значение
        *\return адрес значения
        */
        const_pointer address (const_reference value) const;

        /*!\fn  max_size () const;
        *\brief Возвращает максимальное число элементов, под которые может быть выделена память
        *\return максимальное число элементов, под которые может быть выделена память
        */
        size_type max_size () const;

        /*!\fn  operator!=(const MultigraphAllocator& other) const;
        *\brief Проверка аллокаторов на неравенство
        *\param [in] other - аллокатор для сравнения
        *\return всегда возвращает ложь для аллокаторов без состояния
        */
        bool operator!=(const MultigraphAllocator& other) const;

        /*!\fn  operator==(const MultigraphAllocator& other) const;
        *\brief Проверка аллокаторов на равенство
        *\param [in] other - аллокатор для сравнения
        *\return всегда возвращает правду для аллокаторов без состояния
        */
        bool operator==(const Mallocator& other) const;

        /*!\fn  construct(pointer p, const T& value) const;
        *\brief Инициализирует элементы в выделнном хранилище значением
        *\param [in] p - выделенное хранилище
        *\param [in] value - значение
        */
        void construct(pointer p, const T& value) const;

        /*!\fn  destroy(pointer p) const;
        *\brief Разрушает элементы в выделенном хранилище
        *\param [in] p - выделенное хранилище
        */
        void destroy(pointer p) const;

        /*!\fn  allocate (size_type num);
        *\brief Выделяет память под несколько элементов
        *\param [in] num - количество элементов
        *\return указатель на выделенную память
        */
        pointer allocate (size_type num);

        /*!\fn  deallocate(pointer  p, const size_t n) const;
        *\brief Очищает память под несколько элементов
        *\param [in] p - указатель на выделенную память
        *\param [in] num - количество элементов
        *\return указатель на выделенную память
        */
        void deallocate(pointer  p, const size_t num) const;
    };

    template <typename T>
    pointer MultigraphAllocator<T>::address (reference value) const
    {
        return &value;
    }

    template <typename T>
    const_pointer MultigraphAllocator<T>::address (const_reference value) const
    {
        return &value;
    }

    template <typename T>
    size_type MultigraphAllocator<T>::max_size () const
    {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    template <typename T>
    bool MultigraphAllocator<T>::operator!=(const MultigraphAllocator& other) const
    {
        return !(*this == other);
    }

    template <typename T>
    bool MultigraphAllocator<T>::operator==(const Mallocator& other) const
    {
        return true;
    }

    template <typename T>
    void MultigraphAllocator<T>::construct(pointer p, const T& value) const
    {
        new((void*)p)T(value);
    }

    template <typename T>
    void MultigraphAllocator<T>::destroy(pointer p) const
    {
        p->~T();
    }

    template <typename T>
    pointer MultigraphAllocator<T>::allocate (size_type num)
    {
        if (n == 0)
        {
            return NULL;
        }

        if (n > max_size())
        {
            throw std::length_error("MultigraphAllocator<T>::allocate() – Integer overflow.");
        }

        void* const pv = malloc(n * sizeof(T));
        if (pv == NULL)
        {
            throw std::bad_alloc();
        }
        return static_cast<pointer>(pv);
    }

    template <typename T>
    void MultigraphAllocator<T>::deallocate(pointer  p, const size_t num) const
    {
        free(p);
    }
}

#endif // MULTIGRAPHALLOCATOR_H
