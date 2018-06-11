#include "addclientdialog.h"
#include "ui_addclientdialog.h"
#include <QRegExpValidator>
AddClientDialog::AddClientDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::AddClientDialog),
    m_isOk(false)
{
    ui->setupUi(this);
    ui->age->setValidator( new  QRegExpValidator(QRegExp("[0-9]{1,3}")) );
}

AddClientDialog::~AddClientDialog()
{
    delete ui;
}


void AddClientDialog::on_buttons_accepted()
{
    m_result.setFirstName(ui->firstName->text());
    m_result.setLastName(ui->lastName->text());
    m_result.setAge(ui->age->text());
    m_isOk = true;
    this->close();
}

ClientModel AddClientDialog::result() const
{
    return m_result;
}

bool AddClientDialog::isOk() const
{
    return m_isOk;
}




void AddClientDialog::on_buttons_rejected()
{
    m_isOk = false;
    this->close();
}
