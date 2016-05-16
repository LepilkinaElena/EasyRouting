#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QDebug>
#include <QWebElement>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <QtWebKitWidgets/QWebFrame>
#include <ERModel/citymap.h>
#include "Controller/searchparameters.h"
#include "ERModel/routecost.h"

enum MapState { VIEW, PLACE, ROUTE_BEGIN, ROUTE_END, REMOVE };

/*!\class MapView
*\brief Класс виджета карты
*\ref MapView
*/
class MapView : public QWebView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);

    /*!\fn drawMark(double x, double y, std::string img, int placeId, std::string placeName);
    *\brief Рисование отметки на карте
    *\param [in] x - координата x
    *\param [in] y - координата y
    *\param [in] img - путь к файлу с иконкой
    *\param [in] placeId - идентификатор соответствующего места
    *\param [in] placeName - название соответствующего места
    */
    void drawMark(double x, double y, std::string img, int placeId, std::string placeName);

    /*!\fn drawLine(double x1, double y1, double x2, double y2, int id);
    *\brief Рисование линии на карте
    *\param [in] x1 - координата x источника
    *\param [in] y1 - координата y источника
    *\param [in] x2 - координата x назначения
    *\param [in] y2 - координата y назначения
    */
    void drawLine(double x1, double y1, double x2, double y2, int id);

    /*!\fn removeMark(int id);
    *\brief Удаление отметки с карты по идентификатору
    *\param [in] id - идентификатор
    */
    void removeMark(int id);

    /*!\fn removeLine(int id);
    *\brief Удаление линии с карты по идентификатору
    *\param [in] id - идентификатор
    */
    void removeLine(int id);

    /*!\fn getState() const;
    *\brief Возвращает статус карты
    *\return статус
    */
    MapState getState() const;

    /*!\fn getPlaceById(unsigned int id);
    *\brief Возвращает место без связей по идентификатору
    *\param [in] id - идентификатор
    *\return место
    */
    Place getPlaceById(unsigned int id);

    /*!\fn isSinglePlace(unsigned int id);
    *\brief Возвращает true если место с таким идентфикатором не имеет связей
    *\param [in] id - идентификатор
    *\return статус
    */
    bool isSinglePlace(unsigned int id);

    /*!\fn addSinglePlace(Place & ref);
    *\brief Добавляет место в список мест без связей
    *\param [in] ref - место
    */
    void addSinglePlace(Place & ref);

    /*!\fn removeSinglePlace(unsigned int id);
    *\brief Удаляет место из списка мест без связей
    *\param [in] id - идентификатор
    */
    void removeSinglePlace(unsigned int id);

    /*!\fn redrawMap(bool drawLines);
    *\brief Перерисовывает маркеры и линии на карте
    *\param [in] drawLines - рисовать линии
    */
    void redrawMap(bool drawLines);

    /*!\fn drawPath(std::vector<SearchParameters> ref);
    *\brief Рисует маршрут на карте
    *\param [in] ref - маршрут
    */
    void drawPath(std::vector<SearchParameters> ref);

    /*!\fn drawPath(std::vector<Path> & ref);
    *\brief Рисует маршрут на карте
    *\param [in] ref - маршрут
    */
    void drawPath(std::vector<Path> & ref);
    /*!\fn clearDrawed();
     * @brief Очищает всё, что нарисовали на карте
     */
    void clearDrawed();

    /*!\fn resetMode();
    *\brief Отмена режима выбора мест
    */
    void resetMode();

    /*!\fn hasSinglePlaces();
    *\brief Проверяет есть ли не связанные места
    *\return статус
    */
    bool hasSinglePlaces();

    void clearSinglePlaces();

signals:
    void mapReady();
    void placeCreated(double x, double y);
    void routeCreated(int begin, int end);
    void firstPlaceSelected();
    void secondPlaceSelected();
    void elementRemoved();
public slots:
    void createPlace();
    void createRoute();
    void removeElement();
    void onMapLoaded();
    void onMapClicked(double geoCoordX, double geoCoordY);
    void onPlaceClicked(int placeId);
    void onLineClicked(int lineId);
    void loadingFinished();
private:
    std::vector<Place> singlePlaces;
    bool mapLoaded;
    int beginPlaceId;
    MapState state;
};

#endif // MAPVIEW_H
