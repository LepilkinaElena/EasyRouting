/*!\file multigraph.h
*\brief Файл с классом для описания мультиграфа
*/

#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include <map>
#include <vector>
#include <set>
#include "multigraphiterator.h"

namespace Multigraph {

    /*!\class Multigraph
    *\brief Класс мультиграфа
    *\ref Multigraph
    */
    template <class T>
    class Multigraph
    {
    public:
        typedef MultigraphIterator<T > iterator;
    private:
        struct waveStep
        {
            std::vector<Cost> costs;
            std::vector<std::vector<int> > routes;
            std::vector<std::vector<T> > vertexes;
        };

        /*!\var Multigraph::idCounter
        *\brief счетчик идентификаторов дуг
        */
        int idCounter;

        /*!\var Multigraph::edges
        *\brief матрица инцендентности мультиграфа
        */
        std::multimap<T, Edge<T> > edges;
    public:

        Multigraph();

        /*!\fn void addEdge(const T& from, const T& to, const Cost& cost);
        *\brief Метод для добавления дуги в мультиграф
        *\param [in] from - вершина, из которой выходит дуга
        *\param [in] to - вершина, в которую входит дуга
        *\param [in] cost - вес дуги
        *\return добавленная дуга
        */
        Edge<T> addEdge(const T& from, const T& to, const Cost& cost);

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

        /*!\fn waveAlgorithm(const Multigraph::T &start, const Multigraph::T &finish, const Cost& limits);
        *\brief Метод поиска пути в графе по волновому алгоритму
        *\param [in] start - начальная точка пути
        *\param [in] finish - конечная точка пути
        *\param [in] limits - ограниение на выбираемые пути
        *\return вектор путей, представленных веткором идентификаторов дуг
        */
        std::vector<std::vector<int> > waveAlgorithm(const T &start, const T &finish,
                                                     const Cost& limits);
        /*!\fn checkKeyExistence(const T key) const;
        *\brief Метод проверки наличия вершины в мультиграфе
        *\param [in] vertex - искомая вершина
        *\return признак наличия искомой вершины в мультиграфе
        */
        bool checkVertexExistence(const T& vertex) const;

        /*!\fn begin();
         *\brief Метод получения итератора на первый элемент в мультиграфе
         *\return итератор на первый элемент в мультиграфе
         */
        iterator begin();

        /*!\fn end();
         *\brief Метод получения итератора на последний элемент в мультиграфе
         *\return итератор на последний элемент в мультиграфе
         */
        iterator end();

    };


    template <typename T>
    Multigraph<T>::Multigraph()
    {
        edges = std::multimap<T, Edge<T> >();
        idCounter = 0;
    }

    template <typename T>
    Edge<T> Multigraph<T>::addEdge(const T& from, const T& to, const Cost& cost)
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

    template <typename T>
    typename Multigraph<T>::iterator Multigraph<T>::begin()
    {
        return iterator(edges.begin());
    }

    template <typename T>
    typename Multigraph<T>::iterator Multigraph<T>::end()
    {
        return iterator(edges.end());
    }

    template <typename T>
    std::vector<std::vector<int>> Multigraph<T>::waveAlgorithm(const T& start, const T& finish,
                                                               const Cost& limits)
    {
        std::vector<std::vector<int>> result;
        std::set<T> oldFront;
        std::set<T> newFront;
        std::map<T, waveStep> currentStepState;
        std::set<T> keys = std::set<T>();
        std::pair <typename std::multimap<T,Edge<T> >::iterator, typename std::multimap<T,Edge<T> >::iterator> values;
        // Получить все вершины графа
        for (auto const& element: edges)
        {
            keys.insert(element.first);
        }

        for (auto const& key: keys)
        {
            waveStep step = waveStep();
            currentStepState[key] = step;
        }

        oldFront.insert(start);
        while (!oldFront.empty())
        {
            for (auto const& state: oldFront)
            {
                waveStep curStepState = currentStepState[state];
                // Получить все дуги, выходящие из вершины
                values = edges.equal_range(state);
                for (typename std::multimap<T,Edge<T> >::iterator it = values.first; it != values.second; ++it)
                {
                    Edge<T> edge = it->second;
                    T to = edge.getTo();
                    waveStep toStep = currentStepState[to];


                    // Создать новые пути и установить их стоимости
                    if (curStepState.routes.empty())
                    {
                        std::vector<int> newRoute;
                        std::vector<T> newVertexes;
                        newVertexes.emplace_back(edge.getFrom());
                        newVertexes.emplace_back(edge.getTo());
                        Cost newCost = edge.getCost();
                        if (newCost < limits && edge.getFrom() != edge.getTo())
                        {
                            newRoute.emplace_back(edge.getId());
                            toStep.routes.emplace_back(newRoute);
                            toStep.costs.emplace_back(edge.getCost());
                            toStep.vertexes.emplace_back(newVertexes);
                            // Добавить в новый фронт волны
                            if (to != finish)
                            {
                                newFront.insert(to);
                            }
                        }
                    }
                    else
                    {
                        std::vector<std::vector<int> >::iterator routeIter;
                        std::vector<Cost>::iterator costIter;
                        typename std::vector<std::vector<T> >::iterator vertexesIter;
                        for (routeIter = curStepState.routes.begin(),
                             costIter = curStepState.costs.begin(),
                             vertexesIter = curStepState.vertexes.begin();
                             routeIter != curStepState.routes.end();
                             ++routeIter, ++costIter, ++ vertexesIter)
                        {
                            std::vector<int> route = *routeIter;
                            std::vector<int> newRoute = std::vector<int>(route);
                            Cost oldCost = *costIter;
                            Cost newCost = edge.getCost() + oldCost;
                            std::vector<T> vertexes = *vertexesIter;
                            std::vector<T> newVertexes = std::vector<T >(vertexes);

                            if (newCost < limits &&
                                std::find(vertexes.begin(), vertexes.end(), to) == vertexes.end())
                            {
                                newRoute.emplace_back(edge.getId());
                                toStep.routes.emplace_back(newRoute);
                                toStep.costs.emplace_back(newCost);
                                newVertexes.emplace_back(to);
                                toStep.vertexes.emplace_back(newVertexes);
                                // Добавить в новый фронт волны
                                if (to != finish)
                                {
                                    newFront.insert(to);
                                }
                            }
                        }
                    }
                }

            }
            // Старый фронт - новый фронт
            oldFront = std::set<T>(newFront);
            newFront.clear();
        }
        result = currentStepState[finish].routes;
        return result;
    }

    template <typename T>
    bool Multigraph<T>::checkVertexExistence(const T& vertex) const
    {
        return edges.count(vertex);
    }
}
#endif
