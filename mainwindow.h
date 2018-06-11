#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasecontroller.h"
#include "tableviewcontroller.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionConnectToDatabase_triggered();

    void on_actionDisconnectFromDatabase_triggered();

    void on_actionAddNewClient_triggered();

    void on_actionApplyChanges_triggered();
    void tableViewDataDirty();
    void on_actionRollbackChanges_triggered();

    void on_actionDeleteSelectedRows_triggered();
    void rowsSelectionChanged();
    void on_actionClose_triggered();



    void on_actionInformation_triggered();

private:
    void disableEdit();
    Ui::MainWindow *ui;
    TableViewController* m_tableViewController;
    DatabaseController* m_databaseController;
    void enableEdit();
    void disableSaveRollback();
    void enableSaveRollback();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
