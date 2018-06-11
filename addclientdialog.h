#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>
#include "clientmodel.h"
namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:

    explicit AddClientDialog(QWidget *parent = 0);
    ~AddClientDialog();

    bool isOk() const;

    ClientModel result() const;

private slots:
    void on_buttons_accepted();

    void on_buttons_rejected();

private:
    Ui::AddClientDialog *ui;
    ClientModel m_result;
    bool m_isOk;
};

#endif // ADDCLIENTDIALOG_H
