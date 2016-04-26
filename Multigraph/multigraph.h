/*!\file multigraph.h
*\brief Файл с классом для описания мультиграфа
*/

#include <map>
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
        typedef MultigraphIterator<T > const_iterator;
    private:
        class waveStep
        {
            int stepId;
            Cost& currentCost;
            std::vector<std::vector<int> > routes;
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

        iterator begin();
        iterator end();

        const_iterator cbegin() const;
        const_iterator cend() const;

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
    typename Multigraph<T>::const_iterator Multigraph<T>::cbegin() const
    {
        return const_iterator(edges.begin());
    }

    template <typename T>
    typename Multigraph<T>::const_iterator Multigraph<T>::cend() const
    {
        return const_iterator(edges.end());
    }

    template <typename T>
    std::vector<std::vector<int>> Multigraph<T>::waveAlgorithm(const T& start, const T& finish,
                                                               const Cost& limits)
    {
        std::vector<std::vector<int>> result;
        /*std::vector<T> oldFront;
        std::vector<T> newFront;
        std::map<T, waveStep> currentStepState;
        int step = 0;
        std::set<T> keys = std::set<T>();
        std::pair <std::multimap<T,Edge<T> >::iterator, std::multimap<T,Edge<T> >::iterator> values;
        // Получить все вершины графа
        for (auto const& element: edges)
        {
            keys.insert(element.first);
        }

        for (auto const& key: keys)
        {
            currentStepState[key] =
        }

        oldFront.emplace_back(start);
        for (auto const& state: oldFront)
        {
            // Получить все дуги, выходящие из вершины
            values = edges.equal_range(state);
            for (std::multimap<T,Edge<T> >::iterator it = values.first; it != values.second; ++it)
            {
                Edge<T> edge = it->second;

            }
        }*/
        return result;
    }

}
