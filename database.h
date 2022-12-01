#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSettings>
#include <QMessageBox>

#include <mysql/jdbc.h>

#include <time.h>
#include <string.h>
#include <unistd.h>

using namespace sql;
using namespace std;

typedef struct {
    int sid;
    string name;
    int times;
} student;

typedef struct {
    int id;
    string name;
    int sid;
    tm time;
} attendance;

class Database
{
public:
    Database();
    ~Database();
    int newStudent(student student);
    void incrTimes(int sid);
private:
    Connection *conn;
};

#endif // DATABASE_H
