#include "connectdatabasedialog.h"
#include "ui_connectdatabasedialog.h"

ConnectDatabaseDialog::ConnectDatabaseDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::ConnectDatabaseDialog),
    m_isOk(false)
{

    ui->setupUi(this);


}

ConnectDatabaseDialog::~ConnectDatabaseDialog()
{
    delete ui;
}

void ConnectDatabaseDialog::on_buttons_accepted()
{
    m_result = ui->databaseNameBox->text();
    m_isOk = true;
    this->close();
}

QString ConnectDatabaseDialog::result() const
{
    return m_result;
}

bool ConnectDatabaseDialog::isOk() const
{
    return m_isOk;
}

void ConnectDatabaseDialog::on_buttons_rejected()
{
    this->close();
}
