#include "selectionitem.h"

SelectionItem::SelectionItem(QString text) : QStandardItem(text)
{
    this->setCheckable( true );
    this->setCheckState( Qt::Checked );
}
