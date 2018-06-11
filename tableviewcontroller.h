#ifndef TABLEVIEWCONTROLLER_H
#define TABLEVIEWCONTROLLER_H
#include <QtSql>
#include <QTableView>
#include "clientmodel.h"
#include "databasecontroller.h"
class TableViewController: public QObject
{
    Q_OBJECT
public:
    TableViewController(QTableView* tableView, DatabaseController* database);
    ~TableViewController();
    void hide();
    void show();
    void refresh();
    void addClient(const ClientModel &client);
    bool applyChanges();
    void slotDirty();
    bool isDirty();
    void revertAll();
    bool isSelected() const;

public slots:
    bool deleteRow();
private slots:
    void signalDirty(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void signalRowsSelectionChanged(QItemSelection,QItemSelection);
signals:
    void rowsSelectionChanged();
    void dirty();
private:
    QTableView* m_tableView;
    QSqlTableModel* m_model;
    DatabaseController* m_db;
    bool m_selected;
    QString m_backupAge;
};

#endif // TABLEDATACONTROLLER_H
