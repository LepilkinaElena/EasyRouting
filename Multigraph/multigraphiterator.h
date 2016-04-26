#ifndef MULTIGRAPHITERATOR_H
#define MULTIGRAPHITERATOR_H

#include <iterator>
#include <initializer_list>
#include <map>
#include "edge.h"

namespace Multigraph {
    template <class T>
    class Multigraph;

    template<typename ValueType>
    class MultigraphIterator: public std::iterator<std::input_iterator_tag, std::pair<const ValueType, Edge<ValueType> > >
    {
        friend class Multigraph<ValueType>;
    private:
        typedef typename std::multimap<ValueType, Edge<ValueType> >::iterator MapIterator;
        MapIterator mapIterator;

        MultigraphIterator(MapIterator mapIterator);
    public:
        MultigraphIterator(const MultigraphIterator &it);

        bool operator!=(MultigraphIterator const& other) const;
        bool operator==(MultigraphIterator const& other) const;
        typename MultigraphIterator::reference operator*() const;
        MultigraphIterator& operator++();
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
}

#endif // MULTIGRAPHITERATOR_H
