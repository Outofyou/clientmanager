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
    ConnectDatabaseDialog(QWidget *parent = 0, QString path = "");
    ~ConnectDatabaseDialog();

    bool isOk() const;
    QString result() const;

    void setError();
private slots:
    void on_buttons_accepted();

    void on_buttons_rejected();

private:
    Ui::ConnectDatabaseDialog *ui;
    QString m_result;
    bool m_isOk;
};

#endif // CONNECTDATABASEDIALOG_H
