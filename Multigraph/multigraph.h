/*!\file multigraph.h
*\brief Файл с классом для описания мультиграфа
*/

#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include <map>
#include <vector>
#include <set>
#include <cassert>
#include "multigraphiterator.h"
#include "Exceptions/nullpointerexception.h"
#include "Exceptions/edgeabsencemultigraphexception.h"
#include "Exceptions/vertexabsencemultigraphexception.h"
#include <ERModel/place.h>
#include "ERModel/citymap.h"

namespace Multigraph {

    /*!\class Multigraph
    *\brief Класс мультиграфа
    *\ref Multigraph
    */
    template <class T, class Alloc>
    class Multigraph
    {
    public:
        typedef MultigraphIterator<T > iterator;
        template <typename _T, typename _Alloc>
        friend std::ostream& operator<< (std::ostream& output, const Multigraph<_T,_Alloc>& object);
        template <typename _T, typename _Alloc>
        friend std::istream& operator>> (std::istream& input, Multigraph<_T,_Alloc>& object);

    private:
        typedef std::multimap<T, Edge<T>*, std::less<T>, Alloc > MultigraphMultiMap;
        struct waveStep
        {
            std::vector<Cost*> costs;
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
        MultigraphMultiMap edges;

    protected:
        /*!\fn getEdgeById(int id);
        *\brief Метод получения дуги по идентификатору
        *\param [in] id - идентификатор дуга
        *\return дуга
        */
        Edge<T>* getEdgeById(int id) throw (EdgeAbsenceMultigraphException);

    public:

        Multigraph();
        Multigraph(const Multigraph& other);
        ~Multigraph();

        /*!\fn checkMultigraph() const;
        *\brief Проверить мультиграф на корректность - инвариант предсусловия
        *\return корректен ли мультиграф
        */
        bool checkMultigraph() const;

        /*!\fn void addEdge(const T& from, const T& to, const Cost& cost);
        *\brief Метод для добавления дуги в мультиграф
        *\param [in] from - вершина, из которой выходит дуга
        *\param [in] to - вершина, в которую входит дуга
        *\param [in] cost - вес дуги
        *\return добавленная дуга
        */
        int addEdge(const T& from, const T& to, Cost *cost) throw (NullPointerException);

        /*!\fn removeEdge(int id);
        *\brief Метод удаления дуги из мультиграфа
        *\param [in] id - идентификатор дуги
        */
        void removeEdge(int id);

        /*!\fn removeEdge(const T& edge);
        *\brief Метод удаления дуги из мультиграфа
        *\param [in] edge - удаляемая дуга
        */
        void removeEdge(const Edge<T> *edge) throw (NullPointerException);

        /*!\fn removeVertex(const T& vertex);
        *\brief Метод удаления вершины из мультиграфа
        *\param [in] vertex - удаляемая вершина
        */
        void removeVertex(const T& vertex);

        /*!\fn searchRoutesWithLimits(const T &start, const T &finish, const Cost& limits);
        *\brief Метод поиска пути в графе по волновому алгоритму
        *\param [in] start - начальная точка пути
        *\param [in] finish - конечная точка пути
        *\param [in] limits - ограниение на выбираемые пути
        *\return вектор путей, представленных веткором идентификаторов дуг
        */
        std::vector<std::vector<int> > searchRoutesWithLimits(const T &start, const T &finish,
                                                     const Cost& limits) throw(VertexAbsenceMultigraphException);
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

        /*!\fn T& getTo() const();
        *\brief Метод для получения вершины, в которую ведет дуга
        *\param [in] this - дуга
        *\return вершина, в которую ведет дуга
        */
        const T &getTo(int edgeId);

        /*!\fn T& getFrom() const();
        *\brief Метод для получения вершины, из которой ведет дуга
        *\param [in] this - дуга
        *\return вершина, из которой ведет дуга
        */
        const T &getFrom(int edgeId);

        /*!\fn Cost& getCost() const;
         *\brief Метод для получения веса дуги
         *\param [in] this - дуга
         *\return вес дуги
        */
        Cost* getCost(int edgeId);

        /*!\fn end();
         *\brief Метод получения итератора на последний элемент в мультиграфе
         *\return итератор на последний элемент в мультиграфе
         */
        iterator end();

        /*!\fn end();
         *\brief Метод получения всех вершин
         *\return все вершины
         */
        std::vector<T> getAllVertexes() const;

        /*!\fn end();
         *\brief Метод получения всех дуг
         *\return все дуги
         */
        std::vector<int> getAllEdges();

        /*!\fn bool operator==(Multigraph& other);
         *\brief Метод сранения двух графов
         *\param [in] this - текущий мультиграф
         *\param [in] other - сравниваемый мультиграф
         *\return признак, равен ли данный мультиграф переданному
        */
        bool operator==(Multigraph& other);

        /*!\fn checkAddingEdgeToMultigraph(int oldId, int oldEdgesNumber);
         *\brief Метод проверки добавления дуги - инвариант постусловия
         *\param [in] oldId - старое значение счетчика идентификаторов
         *\param [in] oldEdgesNumber - старое значение кол-ва дуг
         *\return признак, добавилась ли дуга успешно
        */
        bool checkAddingEdgeToMultigraph(int oldId, int oldEdgesNumber);

        /*!\fn checkRemovingEdgeFromMultigraph(int oldEdgesNumber);
         *\brief Метод проверки удаления дуги - инвариант постусловия
         *\param [in] oldEdgesNumber - старое значение кол-ва дуг
         *\return признак, удалилась ли дуга успешно
        */
        bool checkRemovingEdgeFromMultigraph(int oldEdgesNumber);

        /*!\fn checkAddingVertexToMultigraph(const T& vertex);
         *\brief Метод проверки добавления вершины - инвариант постусловия
         *\param [in] vertex - добавляемая вершина
         *\return признак, добавилась ли вершина успешно
        */
        bool checkAddingVertexToMultigraph(const T& vertex);

        /*!\fn checkRemovingVertexFromMultigraph(const T& vertex);
         *\brief Метод проверки удаления вершины - инвариант постусловия
         *\param [in] vertex - удаляемая вершина
         *\return признак, удалилась ли вершина успешно
        */
        bool checkRemovingVertexFromMultigraph(const T& vertex);
    };

    template <typename T, typename Alloc>
    const T& Multigraph<T, Alloc>::getTo(int edgeId)
    {
        try
        {
            return getEdgeById(edgeId)->getTo();
        }
        catch (EdgeAbsenceMultigraphException e)
        {
            std::cerr << e.what();
        }
    }

    template <typename T, typename Alloc>
    const T& Multigraph<T, Alloc>::getFrom(int edgeId)
    {
        try
        {
            return getEdgeById(edgeId)->getFrom();
        }
        catch (EdgeAbsenceMultigraphException e)
        {
            std::cerr << e.what();
        }
    }

    template <typename T, typename Alloc>
    Cost* Multigraph<T, Alloc>::getCost(int edgeId)
    {
        try
        {
            return getEdgeById(edgeId)->getCost();
        }
        catch (EdgeAbsenceMultigraphException e)
        {
            std::cerr << e.what();
        }
    }


    template <typename T, typename Alloc>
    Multigraph<T, Alloc>::Multigraph()
    {
        edges = MultigraphMultiMap();
        idCounter = 0;
    }

    template <typename T, typename Alloc>
    Multigraph<T, Alloc>::Multigraph(const Multigraph &other)
    {
        idCounter = 0;
        for (auto const& element:other.edges)
        {
            addEdge(element.first, element.second->getTo(), element.second->getCost());
        }
    }

    template <typename T, typename Alloc>
    Multigraph<T, Alloc>::~Multigraph()
    {
        for (typename std::multimap<T,Edge<T>* >::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            Edge<T>* edge = (*it).second;
            if (edge != NULL)
            {
                delete edge;
                edge = NULL;
            }
        }
        edges.clear();
    }

    template <typename T, typename Alloc>
    int Multigraph<T, Alloc>::addEdge(const T& from, const T& to, Cost* cost) throw (NullPointerException)
    {
        assert(checkMultigraph());
        int oldId = idCounter;
        int size = edges.size();

        if (cost == NULL)
        {
            throw (NullPointerException("Указатель на стоимость дуги при добавлении дуги."));
        }
        Edge<T>* edge = new Edge<T>(idCounter, from, to, cost);
        edges.emplace(from, edge);
        idCounter++;

        assert(checkAddingEdgeToMultigraph(oldId, size));

        return edge->getId();
    }

    template <typename T, typename Alloc>
    void Multigraph<T, Alloc>::removeEdge(int id)
    {
        try {
            Edge<T>* edge = getEdgeById(id);
            removeEdge(edge);
        } catch (EdgeAbsenceMultigraphException e) {
            std::cerr << e.what();
        }
    }

    template <typename T, typename Alloc>
    void Multigraph<T, Alloc>::removeEdge(const Edge<T>* edge) throw (NullPointerException)
    {
        int size = edges.size();

        if (edge == NULL)
        {
            throw (NullPointerException("Указатель на дугу при попытке ее удалить нулевой."));
        }
        for (typename std::multimap<T,Edge<T>* >::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            Edge<T>* curEdge = (*it).second;
            if (edge == curEdge)
            {
                edges.erase(it);
                break;
            }
        }

        delete edge;
        assert(checkRemovingEdgeFromMultigraph(size));
    }

    template <typename T, typename Alloc>
    void Multigraph<T, Alloc>::removeVertex(const T& vertex)
    {
        std::vector<int> edgesToRemove;
        edges.erase(vertex);
        for (typename std::multimap<T,Edge<T>* >::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            Edge<T>* edge = (*it).second;
            if (edge->getTo() == vertex)
            {
                edgesToRemove.emplace_back(edge->getId());
            }
        }
        for (std::vector<int>::iterator it = edgesToRemove.begin(); it != edgesToRemove.end(); ++it)
        {
            removeEdge(*it);
        }
        assert(checkRemovingVertexFromMultigraph(vertex));
    }

    template <typename T, typename Alloc>
    Edge<T> *Multigraph<T, Alloc>::getEdgeById(int id) throw (EdgeAbsenceMultigraphException)
    {
        for (auto& element: edges)
        {
            if (element.second->getId() == id)
            {
                return element.second;
            }
        }
        throw EdgeAbsenceMultigraphException("Нет дуги с идентификатором " + std::to_string(id));
    }

    template <typename T, typename Alloc>
    typename Multigraph<T, Alloc>::iterator Multigraph<T, Alloc>::begin()
    {
        return iterator(edges.begin());
    }

    template <typename T, typename Alloc>
    typename Multigraph<T, Alloc>::iterator Multigraph<T, Alloc>::end()
    {
        return iterator(edges.end());
    }

    template <typename T, typename Alloc>
    std::vector<T> Multigraph<T, Alloc>::getAllVertexes() const
    {
        std::set<T> vertexes;
        std::vector<T> result;

        assert(checkMultigraph());

        for (auto const& element: edges)
        {
            vertexes.insert(element.first);
            vertexes.insert(element.second->getTo());
        }
        std::copy(vertexes.begin(), vertexes.end(), std::back_inserter(result));
        return result;
    }

    template <typename T, typename Alloc>
    std::vector<int> Multigraph<T, Alloc>::getAllEdges()
    {
        std::vector<int> result;

        assert(checkMultigraph());

        for (auto const& element: edges)
        {
            int edgeid = element.second->getId();
            result.push_back(edgeid);
        }
        return result;
    }

    template <typename T, typename Alloc>
    std::vector<std::vector<int>> Multigraph<T, Alloc>::searchRoutesWithLimits(const T& start, const T& finish,
                                                               const Cost& limits) throw (VertexAbsenceMultigraphException)
    {
        std::vector<std::vector<int>> result;
        std::set<T> oldFront;
        std::set<T> newFront;
        std::vector<int> newRoute;
        std::vector<T> newVertexes;
        std::map<T, waveStep> currentStepState;
        std::set<T> keys;
        std::pair <typename std::multimap<T,Edge<T>* >::iterator, typename std::multimap<T,Edge<T>* >::iterator> values;

        assert(checkMultigraph());

        if (!checkVertexExistence(start))
        {
            throw (VertexAbsenceMultigraphException("Отсутствует вершина, откуда ищутся пути."));
        }
        if (!checkVertexExistence(finish))
        {
            throw (VertexAbsenceMultigraphException("Отсутствует вершина, куда ищутся пути."));
        }
        // Получить все вершины графа
        for (auto const& element: edges)
        {
            keys.insert(element.first);
        }

        for (typename std::set<T>::iterator it = keys.begin(); it != keys.end(); ++it)
        {
            waveStep step = waveStep();
            currentStepState[*it] = step;
        }

        oldFront.insert(start);
        while (!oldFront.empty())
        {
            for (typename std::set<T>::iterator it = oldFront.begin(); it != oldFront.end(); ++it)
            {
                T state = *it;
                waveStep curStepState = currentStepState[state];
                // Получить все дуги, выходящие из вершины
                values = edges.equal_range(state);
                for (typename std::multimap<T,Edge<T>* >::iterator it = values.first; it != values.second; ++it)
                {
                    Edge<T>* edge = it->second;
                    T to = edge->getTo();
                    waveStep toStep = currentStepState[to];


                    // Создать новые пути и установить их стоимости
                    if (curStepState.routes.empty())
                    {
                        newVertexes.clear();
                        newRoute.clear();
                        newVertexes.emplace_back(edge->getFrom());
                        newVertexes.emplace_back(edge->getTo());
                        const Cost* newCost = edge->getCost();
                        if (newCost->operator <= (limits) && edge->getFrom() != edge->getTo())
                        {
                            newRoute.emplace_back(edge->getId());
                            toStep.routes.emplace_back(newRoute);
                            toStep.costs.emplace_back(edge->getCost());
                            toStep.vertexes.emplace_back(newVertexes);
                            currentStepState[to] = toStep;
                            // Добавить в новый фронт волны
                            if (to != finish && oldFront.find(to) == oldFront.end())
                            {
                                newFront.insert(to);
                            }
                        }
                    }
                    else
                    {
                        std::vector<std::vector<int> >::iterator routeIter;
                        std::vector<Cost*>::iterator costIter;
                        typename std::vector<std::vector<T> >::iterator vertexesIter;
                        for (routeIter = curStepState.routes.begin(),
                             costIter = curStepState.costs.begin(),
                             vertexesIter = curStepState.vertexes.begin();
                             routeIter != curStepState.routes.end();
                             ++routeIter, ++costIter, ++ vertexesIter)
                        {
                            std::vector<int> route = *routeIter;
                            newRoute = std::vector<int>(route);
                            Cost* oldCost = *costIter;
                            Cost* newCost = edge->getCost()->operator +(*oldCost) ;
                            std::vector<T> vertexes = *vertexesIter;
                            newVertexes = std::vector<T >(vertexes);

                            if (newCost->operator <= (limits)  &&
                                std::find(vertexes.begin(), vertexes.end(), to) == vertexes.end())
                            {
                                newRoute.emplace_back(edge->getId());
                                toStep.routes.emplace_back(newRoute);
                                toStep.costs.emplace_back(newCost);
                                newVertexes.emplace_back(to);
                                toStep.vertexes.emplace_back(newVertexes);
                                currentStepState[to] = toStep;
                                // Добавить в новый фронт волны
                                if (to != finish && oldFront.find(to) == oldFront.end())
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

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkVertexExistence(const T& vertex) const
    {
        for (auto const& element: edges)
        {
            if (element.first == vertex || element.second->getTo() == vertex)
            {
                return true;
            }
        }
        return false;
    }

    template <typename _T, typename _Alloc>
    std::ostream& operator<< (std::ostream& output, const Multigraph<_T, _Alloc>& object)
    {
        unsigned int count = (unsigned int) object.edges.size();
        output.write(reinterpret_cast<const char*>(&count), sizeof(count));
        for (auto const& element: object.edges)
        {
            std::cout << "Place" << std::endl;
            output << element.first;
            std::cout << "Edge" << std::endl;
            output << *(element.second);
        }
        return output;
    }

    template <typename _T, typename _Alloc>
    std::istream& operator>> (std::istream& input, Multigraph<_T,_Alloc>& object)
    {
//        if (fileLength < sizeof(unsigned int)) {
//            throw NullPointerException();
//        }
//        fileLength -= sizeof(unsigned int);
        unsigned int count;
        char buf[sizeof(unsigned int)];
        memset(buf, 0 , sizeof(unsigned int));
        input.read(buf, sizeof(unsigned int));
        count = *(reinterpret_cast<unsigned int*>(buf));
        object.edges.clear();

        if (count > 1000) {
            throw NullPointerException();
        }

        for (int i = 0; i < count; i++) {
            _T first = _T();
            Edge<_T> second = Edge<_T>();
            std::cout << "Place" << std::endl;
            input >> first;
            std::cout << "Edge" << std::endl;
            input >> second;

            object.addEdge(first, second.getTo(), second.getCost());
        }

        return input;
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::operator==(Multigraph& other)
    {
        bool result = edges.size() == other.edges.size();
        typename std::multimap<T,Edge<T>* >::iterator iter;
        typename std::multimap<T,Edge<T>* >::iterator otherIter;
        for (iter = edges.begin(), otherIter = other.edges.begin(); iter != edges.end(); ++iter, ++otherIter)
        {
            result = result && (*iter).first == (*otherIter).first &&
                    (*iter).second->operator ==(*((*otherIter).second));
        }

        return result;
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkMultigraph() const
    {
        return edges.size() >= 0 && idCounter >=0;
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkAddingEdgeToMultigraph(int oldId, int oldEdgesNumber)
    {
        return edges.size() - oldEdgesNumber == 1 && idCounter - oldId == 1;
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkRemovingEdgeFromMultigraph(int oldEdgesNumber)
    {
        return oldEdgesNumber - edges.size() == 1;
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkAddingVertexToMultigraph(const T& vertex)
    {
        return checkVertexExistence(vertex);
    }

    template <typename T, typename Alloc>
    bool Multigraph<T, Alloc>::checkRemovingVertexFromMultigraph(const T& vertex)
    {
        return !checkVertexExistence(vertex);
    }
}
#endif
