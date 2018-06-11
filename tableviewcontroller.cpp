#include <mainwindow.h>
#include "tableviewcontroller.h"
#include <QKeyEvent>
#include <QShortcut>
#include <QIntValidator>
TableViewController::TableViewController(QTableView* tableView, DatabaseController* database)
    :m_tableView(tableView),
      m_db(database),
      m_selected(false)
{
    hide();
    m_model = new QSqlTableModel();
    m_tableView->setModel(m_model);
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(signalDirty(const QModelIndex, const QModelIndex)));
    connect(m_tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this, SLOT(signalRowsSelectionChanged(QItemSelection,QItemSelection)));
}

TableViewController::~TableViewController()
{
    delete m_model;
}

void TableViewController::hide()
{
    m_tableView->hide();
}

void TableViewController::show()
{
    refresh();
    m_tableView->show();

}

void TableViewController::refresh()
{

    m_model->setTable("person");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();
    m_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Imię"));
    m_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwisko"));
    m_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Wiek"));


    m_tableView->hideColumn(0);
    m_tableView->show();
}

void TableViewController::addClient(const ClientModel &client)
{

    QSqlRecord record = m_model->record();
    record.remove(record.indexOf("id"));
    record.setValue("firstname", client.getFirstName());
    record.setValue("lastname", client.getLastName());
    record.setValue("age", client.getAge());
    if(m_model->insertRecord(-1, record)){
    if(m_model->submit()){

    }
    else{
            m_db->rollback();
    }
    }
    emit dirty();

}

bool TableViewController::applyChanges()
{
    m_db->transaction();
    if(m_model->submitAll())
    {
        return m_db->commit();
    }
    else
    {
        m_db->rollback();
        return false;
    }
}

bool TableViewController::deleteRow()
{
    const QModelIndexList selectedRows = m_tableView->selectionModel()->selectedRows();
    for(int i = selectedRows.count()-1; i>=0 ; i--)
    {
        QModelIndex index = selectedRows.at(i);
        m_model->removeRow(index.row());

    }
    m_model->submit();
    emit dirty();
    return true;
}

void TableViewController::signalDirty(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    if(topLeft.column() ==3 && bottomRight.column()==3){
        bool isOk = false;
        m_model->record(topLeft.row()).value("age").toInt(&isOk);
        if(!isOk)
        {
            QSqlRecord r = m_model->record(topLeft.row());
            r.setValue("age", m_backupAge);
            m_model->setRecord(topLeft.row(), r);
            m_model->submit();
            return;
        }
        else
            m_backupAge = m_model->record(topLeft.row()).value("age").toString();
    }

    emit dirty();
}

void TableViewController::signalRowsSelectionChanged(QItemSelection a,QItemSelection b)
{
    const QModelIndexList selectedRows = m_tableView->selectionModel()->selectedRows();
    if(selectedRows.count() >0 && m_selected == false)
    {
        m_selected = true;
        emit rowsSelectionChanged();
    }
    else if(selectedRows.count() == 0 && m_selected)
    {
        m_selected = false;
        emit rowsSelectionChanged();
    }
    const QModelIndexList selectedItems = m_tableView->selectionModel()->selectedIndexes();
    if(selectedItems.count() == 1)
    {
       for(auto x : selectedItems)
       {
           if(x.column()==3)
               m_backupAge = m_model->record(x.row()).value("age").toString();
       }
    }
}

bool TableViewController::isSelected() const
{
    return m_selected;
}

bool TableViewController::isDirty()
{
    return m_model->isDirty();
}

void TableViewController::revertAll()
{
    m_model->revertAll();
    refresh();
}



