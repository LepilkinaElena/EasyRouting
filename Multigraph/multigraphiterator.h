#ifndef MULTIGRAPHITERATOR_H
#define MULTIGRAPHITERATOR_H

#include <iterator>
#include <initializer_list>

namespace Multigraph {
    template <class T>
    class Multigraph;

    template<typename ValueType>
    class MultigraphIterator: public std::iterator<std::input_iterator_tag, ValueType>
    {
        friend class Multigraph<ValueType>;
    private:
        MultigraphIterator(ValueType* value);
        ValueType* value;
    public:
        MultigraphIterator(const MultigraphIterator &it);

        bool operator!=(MultigraphIterator const& other) const;
        bool operator==(MultigraphIterator const& other) const;
        typename MultigraphIterator::reference operator*() const;
        MultigraphIterator& operator++();
    };

    template<typename ValueType>
    MultigraphIterator<ValueType>::MultigraphIterator(ValueType *value) :
        value(value)    {}

    template<typename ValueType>
    MultigraphIterator<ValueType>::MultigraphIterator(const MultigraphIterator& it) :
        value(it.value) {}

    template<typename ValueType>
    bool MultigraphIterator<ValueType>::operator!=(MultigraphIterator const& other) const
    {
        return value != other.value;
    }

    template<typename ValueType>
    bool MultigraphIterator<ValueType>::operator==(MultigraphIterator const& other) const
    {
        return value == other.value;
    }

    template<typename ValueType>
    typename MultigraphIterator<ValueType>::reference MultigraphIterator<ValueType>::operator*() const
    {
        return *value;
    }

    template<typename ValueType>
    MultigraphIterator<ValueType> &MultigraphIterator<ValueType>::operator++()
    {
        ++value;
        return *this;
    }
}

#endif // MULTIGRAPHITERATOR_H
