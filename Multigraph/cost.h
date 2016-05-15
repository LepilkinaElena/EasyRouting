/*!\file cost.h
*\brief Файл с классом для описания веса дуги мультиграфа
*/
#ifndef COST_H
#define COST_H
#include <iostream>

namespace Multigraph {
    /*!\class Cost
    *\brief Класс веса дуги мультиграфа
    *\ref Cost
    */
    class Cost
    {
    public:
        Cost();
        virtual ~Cost();

        /*!\fn Cost operator+(const Cost& other);
         *\brief Метод сложения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - прибавляемый вес дуги
         *\return вес, являющийся результатом сложения
        */
        virtual Cost* operator+(const Cost& other) const;

        /*!\fn Cost operator-(const Cost& other);
         *\brief Метод разности двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - вычитаемый вес дуги
         *\return вес, являющийся результатом разности
        */
        virtual Cost operator-(const Cost& other) const;

        /*!\fn bool operator<(const Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги меньше переданного
        */
        virtual bool operator<=(const Cost& other) const;

        /*!\fn bool operator>(const Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги больше переданного
        */
        virtual bool operator>(const Cost& other) const;

        /*!\fn bool operator==(const Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, равен ли данный вес дуги переданному
        */
        virtual bool operator==(const Cost& other) const;

        /*!\fn bool operator>=(const Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги больше или равен переданному
        */
        virtual bool operator>=(const Cost& other) const;

        /*!\fn bool operator<(const Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги меньше или равен переданному
        */
        virtual bool operator<(const Cost& other) const;

        virtual std::ostream& save(std::ostream& output) const;
        friend std::ostream& operator<< (std::ostream& output, const Cost& object)
        {
            object.save(output);
            return output;
        }

        virtual std::istream& load(std::istream& input);
        friend std::istream& operator>> (std::istream& input, Cost& object)
        {
            object.load(input);
            return input;
        }


    };
}

#endif
