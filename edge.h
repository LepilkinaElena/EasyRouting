/*!\file edge.h
*\brief Файл с классом для описания дуги мультиграфа
*/

#include "cost.h"

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
    const T& from;

    /*!\var Edge::from
    *\brief вершина, в которую входит дуга
    */
    const T& to;

    /*!\var Edge::cost
    *\brief вес дуги
    */
    const Cost& cost;

public:
    /*!\fn Edge(int id)
    *\brief Конструктор дуги
    *\param [in] conditions - автомат, которому принадлежит состояние
    *\return переход
    */
    Edge(int id, const T& from, const T& to, const T& cost);

    /*!\fn Cost& getCost() const;
     *\brief Метод для получения веса дуги
     *\param [in] this - дуга
     *\return вес дуги
    */
    Cost& getCost() const;

    /*!\fn T& getTo() const();
    *\brief Метод для получения вершины, в которую ведет дуга
    *\param [in] this - дуга
    *\return вершина, в которую ведет дуга
    */
    T& getTo() const();
};

template <typename T>
Edge<T>::Edge(int id, const T& from, const T& to, const T& cost)
{
    this->id = id;
    this->cost = cost;
    this->from = from;
    this->to = to;
}

template <typename T>
Cost& Edge<T>::getCost() const
{
    return cost;
}

template <typename T>
T& Edge<T>::getTo() const()
{
    return to;
}

