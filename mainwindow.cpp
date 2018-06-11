#include <QCloseEvent>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectdatabasedialog.h"
#include "addclientdialog.h"
#include "savechangesmessagebox.h"
#include "infodialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_databaseController = new DatabaseController();
    m_tableViewController =  new TableViewController(ui->tableView,m_databaseController);
    this->disableEdit();
    connect(m_tableViewController, SIGNAL(dirty()), this, SLOT(tableViewDataDirty()));
    connect(m_tableViewController, SIGNAL(rowsSelectionChanged()), this, SLOT(rowsSelectionChanged()));
}

MainWindow::~MainWindow()
{
    delete m_tableViewController;
    delete m_databaseController;
    delete ui;
}

void MainWindow::on_actionConnectToDatabase_triggered()
{

    int res = QMessageBox::Discard;
    if(m_tableViewController->isDirty())
    {
        res = SaveChangesMessageBox().exec();
    }
    switch(res){
    case QMessageBox::Cancel:
        return;
    case QMessageBox::Save:
        m_tableViewController->applyChanges();
        break;
    default:
        break;
    }
    ConnectDatabaseDialog dialog(this);
    dialog.exec();
    if(dialog.isOk())
    {
        m_databaseController->connectTo(dialog.result());
        m_tableViewController->show();
        this->setWindowTitle("Menadżer Klientów - " + dialog.result());
        this->enableEdit();
    }


}

void MainWindow::on_actionDisconnectFromDatabase_triggered()
{
    int res = QMessageBox::Discard;
    if(m_tableViewController->isDirty())
    {
        res = SaveChangesMessageBox().exec();
    }
    switch(res){
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Save:
        m_tableViewController->applyChanges();
    case QMessageBox::Discard:
        m_databaseController->disconnect();
        m_tableViewController->hide();
        this->disableEdit();
        this->setWindowTitle("Menadżer Klientów");
        m_tableViewController->revertAll();
        break;
    default:
        break;
    }


}


void MainWindow::on_actionAddNewClient_triggered()
{
    AddClientDialog dialog(this);
    dialog.exec();
    if(dialog.isOk())
    {
        m_tableViewController->addClient(dialog.result());

    }

}


void MainWindow::on_actionApplyChanges_triggered()
{
    m_tableViewController->applyChanges();
    disableSaveRollback();
}

void MainWindow::disableSaveRollback()
{
    ui->actionApplyChanges->setDisabled(true);
     ui->actionRollbackChanges->setDisabled(true);
}

void MainWindow::enableSaveRollback()
{
    ui->actionApplyChanges->setDisabled(false);
    ui->actionRollbackChanges->setDisabled(false);
}

void MainWindow::tableViewDataDirty()
{
    enableSaveRollback();
}

void MainWindow::disableEdit()
{
    ui->actionAddNewClient->setDisabled(true);
    ui->actionDisconnectFromDatabase->setDisabled(true);
    ui->actionDeleteSelectedRows->setDisabled(true);
    disableSaveRollback();
}

void MainWindow::enableEdit()
{
    ui->actionAddNewClient->setDisabled(false);

    ui->actionDisconnectFromDatabase->setDisabled(false);

}

void MainWindow::on_actionRollbackChanges_triggered()
{
    m_tableViewController->revertAll();
    disableSaveRollback();
}

void MainWindow::on_actionDeleteSelectedRows_triggered()
{
    m_tableViewController->deleteRow();
}

void MainWindow::rowsSelectionChanged()
{
    if(m_tableViewController->isSelected())
        ui->actionDeleteSelectedRows->setDisabled(false);
    else
        ui->actionDeleteSelectedRows->setDisabled(true);
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}



void MainWindow::closeEvent (QCloseEvent *event)
{
    int res = QMessageBox::Discard;
    if(m_tableViewController->isDirty())
    {
        res = SaveChangesMessageBox().exec();
    }
    switch(res){
    case QMessageBox::Cancel:
        event->ignore();
        return;
    case QMessageBox::Save:
        m_tableViewController->applyChanges();
    case QMessageBox::Discard:
        m_databaseController->disconnect();
        m_tableViewController->hide();
        this->disableEdit();
        this->setWindowTitle("Menadżer Klientów");
        break;
    default:
        break;
    }
    event->accept();
}

void MainWindow::on_actionInformation_triggered()
{
    InfoDialog().exec();
}
