/*!\file multigraphiterator.h
*\brief Файл с классом для описания итератора мультиграфа
*/
#ifndef MULTIGRAPHITERATOR_H
#define MULTIGRAPHITERATOR_H

#include <iterator>
#include <initializer_list>
#include <map>
#include "edge.h"
#include "multigraphallocator.h"

namespace Multigraph {
    template <class T, class Alloc = MultigraphAllocator<std::pair<const T,  Edge<T>* > > >
    class Multigraph;

    /*!\class MultigraphIterator
    *\brief Класс итератора мультиграфа
    *\ref MultigraphIterator
    */
    template<typename ValueType>
    class MultigraphIterator: public std::iterator<std::input_iterator_tag, std::pair<const ValueType, Edge<ValueType>* >>
    {
        friend class Multigraph<ValueType>;
    private:
        typedef typename std::multimap<ValueType, Edge<ValueType>* >::iterator MapIterator;

        /*!\var MultigraphIterator::mapIterator
        *\brief итератор на элемент в карте
        */
        MapIterator mapIterator;

        MultigraphIterator(MapIterator mapIterator);
    public:
        MultigraphIterator(const MultigraphIterator &it);

        /*!\fn  operator!=(MultigraphIterator const& other) const;
        *\brief Проверка итераторов на неравенство
        *\param [in] other - другой итератор
        *\return признак, не равен ли текущий итератор другому
        */
        bool operator!=(MultigraphIterator const& other) const;

        /*!\fn  operator==(MultigraphIterator const& other) const;
        *\brief Проверка итераторов на равенство
        *\param [in] other - другой итератор
        *\return признак, равен ли текущий итератор другому
        */
        bool operator==(MultigraphIterator const& other) const;

        /*!\fn  operator*() const;
        *\brief Получение значения по итератору
        *\return значение элемента, на который указывает итератор
        */
        typename MultigraphIterator::reference operator*() const;

        /*!\fn  operator++();
        *\brief Получение итератора на следующий элемент
        *\return итератор на следующий элемент
        */
        MultigraphIterator& operator++();

        /*!\fn  operator--();
        *\brief Получение итератора на предыдущий элемент
        *\return итератор на предыдущий элемент
        */
        MultigraphIterator& operator--();
    };

    template<typename ValueType>
    MultigraphIterator<ValueType>::MultigraphIterator(MapIterator mapIterator) :
        mapIterator(mapIterator)    {}

    template<typename ValueType>
    MultigraphIterator<ValueType>::MultigraphIterator(const MultigraphIterator& it) :
        mapIterator(it.mapIterator) {}

    template<typename ValueType>
    bool MultigraphIterator<ValueType>::operator!=(MultigraphIterator const& other) const
    {
        return mapIterator != other.mapIterator;
    }

    template<typename ValueType>
    bool MultigraphIterator<ValueType>::operator==(MultigraphIterator const& other) const
    {
        return mapIterator == other.mapIterator;
    }

    template<typename ValueType>
    typename MultigraphIterator<ValueType>::reference MultigraphIterator<ValueType>::operator*() const
    {
        return *mapIterator;
    }

    template<typename ValueType>
    MultigraphIterator<ValueType> &MultigraphIterator<ValueType>::operator++()
    {
        ++mapIterator;
        return *this;
    }

    template<typename ValueType>
    MultigraphIterator<ValueType> &MultigraphIterator<ValueType>::operator--()
    {
        --mapIterator;
        return *this;
    }
}

#endif // MULTIGRAPHITERATOR_H
