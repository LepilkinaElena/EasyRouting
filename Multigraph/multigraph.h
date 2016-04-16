/*!\file multigraph.h
*\brief Файл с классом для описания мультиграфа
*/

#include "edge.h"
#include <map>

namespace Multigraph {

    /*!\class Multigraph
    *\brief Класс мультиграфа
    *\ref Multigraph
    */
    template <class T>
    class Multigraph
    {
    private:
        /*!\var Multigraph::idCounter
        *\brief счетчик идентификаторов дуг
        */
        int idCounter;

        /*!\var Multigraph::edges
        *\brief матрица инцендентности мультиграфа
        */
        std::multimap<T, Edge<T>> edges;
    public:
        Multigraph();

        /*!\fn void addEdge(const T& from, const T& to, const Cost& cost);
        *\brief Метод для добавления дуги в мультиграф
        *\param [in] from - вершина, из которой выходит дуга
        *\param [in] to - вершина, в которую входит дуга
        *\param [in] cost - вес дуги
        *\return добавленная дуга
        */
        Edge<T>& addEdge(const T& from, const T& to, const Cost& cost) const;

        /*!\fn removeEdge(int id);
        *\brief Метод удаления дуги из мультиграфа
        *\param [in] id - идентификатор дуги
        */
        void removeEdge(int id);

        /*!\fn removeEdge(const T& edge);
        *\brief Метод удаления дуги из мультиграфа
        *\param [in] edge - удаляемая дуга
        */
        void removeEdge(const Edge<T>& edge);

        /*!\fn getEdgeById(int id);
        *\brief Метод получения дуги по идентификатору
        *\param [in] id - идентификатор дуга
        *\return дуга
        */
        Edge<T>& getEdgeById(int id);
    };
}

using namespace Multigraph;

template <typename T>
Multigraph<T>::Multigraph()
{
    edges = std::multimap();
    idCounter = 0;
}

template <typename T>
Edge<T>& Multigraph<T>::addEdge(const T& from, const T& to, const Cost& cost) const
{
    Edge<T> edge = Edge<T>(idCounter, from, to, cost);
    edges.emplace(from, edge);
    idCounter++;
    return edge;
}

template <typename T>
void Multigraph<T>::removeEdge(int id)
{
    Edge<T> edge = getEdgeById(id);
    if (edge)
    {
        removeEdge(edge);
    }
}

template <typename T>
void Multigraph<T>::removeEdge(const Edge<T>& edge)
{
    edges.erase(edge.from);
}

template <typename T>
Edge<T>& Multigraph<T>::getEdgeById(int id)
{
    for (auto& element: edges)
    {
        if (element.second.id == id)
        {
            return element;
        }
    }
    return nullptr;
}
