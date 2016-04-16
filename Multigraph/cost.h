/*!\file cost.h
*\brief Файл с классом для описания веса дуги мультиграфа
*/

namespace Multigraph {
    /*!\class Cost
    *\brief Класс веса дуги мультиграфа
    *\ref Cost
    */
    class Cost
    {
    public:
        Cost();

        /*!\fn Cost& operator+(Cost& other);
         *\brief Метод сложения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - прибавляемый вес дуги
         *\return вес, являющийся результатом сложения
        */
        virtual Cost& operator+(Cost& other);

        /*!\fn Cost& operator-(Cost& other);
         *\brief Метод разности двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - вычитаемый вес дуги
         *\return вес, являющийся результатом разности
        */
        virtual Cost& operator-(Cost& other);

        /*!\fn bool operator<(Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги меньше переданного
        */
        virtual bool operator<(Cost& other);

        /*!\fn bool operator>(Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги больше переданного
        */
        virtual bool operator>(Cost& other);

        /*!\fn bool operator==(Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, равен ли данный вес дуги переданному
        */
        virtual bool operator==(Cost& other);

        /*!\fn bool operator>=(Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги больше или равен переданному
        */
        virtual bool operator>=(Cost& other);

        /*!\fn bool operator<=(Cost& other);
         *\brief Метод сранения двух весов дуг
         *\param [in] this - текущий вес дуги
         *\param [in] other - сравниваемый вес дуги
         *\return признак, является ли данный вес дуги меньше или равен переданному
        */
        virtual bool operator<=(Cost& other);
    };
}
