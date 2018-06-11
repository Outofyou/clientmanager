#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QString>



class ClientModel
{
public:
    ClientModel();
    ClientModel(const QString &firstName, const QString &lastName, const QString &age);
    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getAge() const;
    void setAge(const QString &value);

private:
    QString firstName;
    QString lastName;
    QString age;
};

#endif // CLIENTMODEL_H
