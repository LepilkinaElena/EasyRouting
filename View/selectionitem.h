#ifndef SELECTIONITEM_H
#define SELECTIONITEM_H

#include <QStandardItem>

/*!\class SelectionItem
*\brief Класс элемента списка с CheckBox
*\ref SelectionItem
*/
class SelectionItem : public QStandardItem
{
public:
    explicit SelectionItem(QString text);


};

#endif // SELECTIONITEM_H
