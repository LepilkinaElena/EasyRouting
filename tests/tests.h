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
    void test1();
};

#endif // TESTS_H
