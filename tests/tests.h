#pragma once
#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QtTest>
#include "Multigraph/multigraph.h"
#include "ERModel/place.h"
#include "ERModel/routecost.h"

class Tests : public QObject
{
    Q_OBJECT

private:
    Multigraph::Multigraph<Place> getGraph();

private slots:
    // Тесты для алгоритма
    void no_route();
    void one_route();
    void several_routes();
    void cycle_route();
    void one_suitable_route();
    void no_physical_route();

    // Тесты на работу итераторов
    void iterator_work();
    void iter_cycle();

    // Тест на удаление вершины
    void remove_vertex_test();

    void graph_equals();
};

#endif // TESTS_H
