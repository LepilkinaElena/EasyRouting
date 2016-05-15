/*!\file searchparameter.h
*\brief Файл с классом параметров путей
*/
#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include<QTime>
#include"ERModel/routecost.h"

/*!\class SearchParameters
*\brief Класс параметров путей
*\ref SearchParameters
*/
class SearchParameters
{
private:
    /*!\var SearchParameters::start
    *\brief место начала пути
    */
    int start;
    /*!\var SearchParameters::finish
    *\brief место конца пути
    */
    int finish;
    /*!\var SearchParameters::travellersNumber
    *\brief кол-во путешественников
    */
    int travellersNumber;
    /*!\var SearchParameters::time
    *\brief время на путь
    */
    QTime time;
    /*!\var SearchParameters::money
    *\brief бюджет на путь
    */
    int money;
    /*!\var SearchParameters::transport
    *\brief транспорт для передвижения
    */
    std::set<Transport> transport;
    /*!\var SearchParameters::interests
    *\brief интересы для посещения мест
    */
    std::set<Interest> interests;

public:
    SearchParameters();
    /*!\fn setStart(int start);
    *\brief Метод задания начала пути
    *\param [in] start - начало пути
    */
    void setStart(int start);
    /*!\fn setFinish(int finish);
    *\brief Метод задания конца пути
    *\param [in] finish - конец пути
    */
    void setFinish(int finish);
    /*!\fn setTravellersNumber(int number);
    *\brief Метод задания кол-ва путешественников
    *\param [in] number - кол-во путешественников
    */
    void setTravellersNumber(int number);
    /*!\fn setTime(QTime time);
    *\brief Метод задания времени
    *\param [in] time - время
    */
    void setTime(QTime time);
    /*!\fn setTime(QTime time);
    *\brief Метод задания времени
    *\param [in] time - время
    */
    void setMoney(int money);
    /*!\fn addTransport(Transport transport);
    *\brief Метод добавления транспорта
    *\param [in] transport - вид транспорта
    */
    void addTransport(Transport transport);
    /*!\fn addInterest(Interest interest);
    *\brief Метод добавления интересов
    *\param [in] interest - вид интереса
    */
    void addInterest(Interest interest);

    /*!\fn getMoney();
    *\brief Метод получения бюджета
    *\return бюджет
    */
    int getMoney();

    /*!\fn getTime();
    *\brief Метод получения времени
    *\return время
    */
    QTime getTime();

    /*!\fn getStart();
    *\brief Метод получения начала
    *\return начало
    */
    int getStart();

    /*!\fn getStart();
    *\brief Метод получения конечной точки
    *\return конечная точка
    */
    int getFinish();

    /*!\fn getTravellersNumber();
    *\brief Метод получения кол-ва путешественников
    *\return кол-во путешественников
    */
    int getTravellersNumber();

    /*!\fn toRouteCost();
    *\brief Метод преобразования к стоимости пути
    *\return стоимость пути
    */
    RouteCost toRouteCost();
};

#endif // SEARCHPARAMETERS_H
