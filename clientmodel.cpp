#include "clientmodel.h"

ClientModel::ClientModel()
{

}

ClientModel::ClientModel(const QString &firstName, const QString &lastName, const QString & age)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
}

QString ClientModel::getFirstName() const
{
    return firstName;
}

void ClientModel::setFirstName(const QString &value)
{
    firstName = value;
}

QString ClientModel::getLastName() const
{
    return lastName;
}

void ClientModel::setLastName(const QString &value)
{
    lastName = value;
}

QString ClientModel::getAge() const
{
    return age;
}

void ClientModel::setAge(const QString &value)
{
    age = value;
}
