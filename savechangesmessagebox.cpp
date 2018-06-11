#include "savechangesmessagebox.h"
#include <QIcon>

SaveChangesMessageBox::SaveChangesMessageBox()
{
    this->setWindowTitle("Menadżer Klientów");
    this->setWindowIcon(QPixmap(":/app/icons/res/Locked.png"));
    this->setText("Baza danych została zmodyfikowana.");
    this->setInformativeText("Czy chcesz zapisać zmiany?");

    this->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    this->setDefaultButton(QMessageBox::Save);
    this->setButtonText(QMessageBox::Save, "Zapisz");
    this->setButtonText(QMessageBox::Discard, "Nie zapisuj");
    this->setButtonText(QMessageBox::Cancel, "Anuluj");
}
