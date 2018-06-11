#ifndef CONNECTDATABASEDIALOG_H
#define CONNECTDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDatabaseDialog;
}

class ConnectDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDatabaseDialog(QWidget *parent = 0);
    ~ConnectDatabaseDialog();

    bool isOk() const;
    QString result() const;

private slots:
    void on_buttons_accepted();

    void on_buttons_rejected();

private:
    Ui::ConnectDatabaseDialog *ui;
    QString m_result;
    bool m_isOk;
};

#endif // CONNECTDATABASEDIALOG_H
