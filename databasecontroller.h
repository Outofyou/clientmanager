#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QtSql>
class DatabaseController
{
public:
    DatabaseController();
    ~DatabaseController();
    void connectTo(const QString& path);
    void disconnect();
    bool transaction();
    bool rollback();
    bool commit();
private:
    QSqlDatabase m_database;
};

#endif // DATABASECONTROLLER_H
