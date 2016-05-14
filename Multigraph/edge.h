/*!\file edge.h
*\brief Файл с классом для описания дуги мультиграфа
*/

#include "cost.h"
#include <algorithm>
#include <iostream>

namespace Multigraph {
    /*!\class Edge
    *\brief Класс дуги мультиграфа
    *\ref Edge
    */
    template <class T>
    class Edge
    {
    private:
        /*!\var Edge::id
        *\brief уникальный идентификатор дуги
        */
        const int id;

        /*!\var Edge::from
         *\brief вершина, из которой исходит дуга
        */
        const T from;

        /*!\var Edge::from
        *\brief вершина, в которую входит дуга
        */
        const T to;

        /*!\var Edge::cost
        *\brief вес дуги
        */
        Cost* cost;

    public:
        /*!\fn Edge(int id, const T& from, const T& to, const T& cost);
        *\brief Конструктор дуги
        *\param [in] id - идентификатор дуги
        *\param [in] from - вершина, из которой выходит дуга
        *\param [in] to - вершина, в которую входит дуга
        *\param [in] cost - вес дуги
        *\return дуга
        */
        Edge(int id, const T& from, const T& to, Cost* cost);
        ~Edge();

        /*!\fn Cost& getCost() const;
         *\brief Метод для получения веса дуги
         *\param [in] this - дуга
         *\return вес дуги
        */
        Cost* getCost() const;

        /*!\fn T& getTo() const();
        *\brief Метод для получения вершины, в которую ведет дуга
        *\param [in] this - дуга
        *\return вершина, в которую ведет дуга
        */
        const T &getTo() const;

        /*!\fn T& getFrom() const();
        *\brief Метод для получения вершины, из которой ведет дуга
        *\param [in] this - дуга
        *\return вершина, из которой ведет дуга
        */
        const T &getFrom() const;
        int getId() const;

        template <typename _T>
        friend std::ostream& operator<< (std::ostream& output, const Edge<_T>& object);
    };

    template <typename T>
    int Edge<T>::getId() const
    {
        return id;
    }

    template <typename T>
    Edge<T>::~Edge()
    {
        delete cost;
    }

    template <typename T>
    Edge<T>::Edge(int id, const T& from, const T& to, Cost *cost):
        id(id), from(from), to(to), cost(cost) {
    }

    template <typename T>
    Cost *Edge<T>::getCost() const
    {
        return cost;
    }

    template <typename T>
    const T& Edge<T>::getTo() const
    {
        return to;
    }

    template <typename T>
    const T& Edge<T>::getFrom() const
    {
        return from;
    }

    template <typename _T>
    std::ostream& operator<< (std::ostream& output, const Edge<_T>& object) {
        int id = object.id;
        _T from = object.from;
        _T to = object.to;
        Cost* cost = object.cost;

        output.write((char*) &id, sizeof(id));
        output << from;
        output << to;
        output << *cost;

        return output;
    }
}
