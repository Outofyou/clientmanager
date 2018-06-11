#include "databasecontroller.h"

#include <QFileInfo>
DatabaseController::DatabaseController()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");



    /*qDebug()<<query.lastError()<<endl;
    query.exec("INSERT INTO person (id,firstname,lastname,age) VALUES (1,'Rafal','Oleksy',13)");
    qDebug()<<query.lastError()<<endl;*/
}

DatabaseController::~DatabaseController()
{
    if(m_database.isOpen())
        m_database.close();
}

void DatabaseController::connectTo(const QString& path)
{
    if(m_database.isOpen())
        m_database.close();
    m_database.setDatabaseName(path);
    m_database.open();
    QSqlQuery query;
    query.exec("create table IF NOT EXISTS person "
                  "(id INTEGER PRIMARY KEY, "
                  "firstname varchar(20), "
                  "lastname varchar(30), "
                  "age integer)");
}

void DatabaseController::disconnect()
{
    if(m_database.isOpen())
        m_database.close();
}

bool DatabaseController::transaction()
{
    return m_database.transaction();
}
bool DatabaseController::rollback()
{
    return m_database.rollback();
}

bool DatabaseController::commit()
{
    return m_database.commit();
}
