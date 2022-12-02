#include "database.h"

Database *Database::instance;

Database::Database()
{
    if (access("db.ini", F_OK) != 0) {
        throw std::runtime_error("db.ini not found!");
        exit(-1);
    }
    QSettings *dbSettings = new QSettings("db.ini", QSettings::IniFormat);
    const string host = dbSettings->value("DB/Host").toString().toStdString();
    const string username = dbSettings->value("DB/Username").toString().toStdString();
    const string password = dbSettings->value("DB/Password").toString().toStdString();
    const string database = dbSettings->value("DB/Database").toString().toStdString();
    Driver *driver = mysql::get_driver_instance();
    this->conn = driver->connect(host, username, password);
    this->conn->setSchema(database);
    delete dbSettings;
}

void Database::incrTimes(int sid) {
    unique_ptr<PreparedStatement> stmt(this->conn->prepareStatement("update student set times=times+1 where id=?"));
    stmt->setInt(1, sid);
    stmt->executeUpdate();
    unique_ptr<PreparedStatement> stmt2(this->conn->prepareStatement("insert into attendance(name, sid, time) values((select name from student where id=?), ?, ?)"));
    stmt2->setInt(1, sid);
    stmt2->setInt(2, sid);
    time_t curtime = 0;
    time(&curtime);
    char timeStr[100];
    strftime(timeStr, 100, "%Y-%m-%d %H:%M:%S", localtime(&curtime));
    stmt2->setDateTime(3, timeStr);
    stmt2->executeUpdate();
}

int Database::newStudent(student student) {
    unique_ptr<PreparedStatement> stmt(this->conn->prepareStatement("select count(id) as c from student where id=?"));
    unique_ptr<PreparedStatement> stmt2(this->conn->prepareStatement("insert into student(id, name) values(?,?)"));
    stmt->setInt(1, student.sid);
    unique_ptr<ResultSet> res(stmt->executeQuery());
    if (res->getInt("c") > 0) {
        return -1;
    }
    stmt2->setInt(1, student.sid);
    stmt2->setString(2, student.name);
    stmt2->execute();
    return 0;
}

Database::~Database() {
    this->conn->close();
    delete conn;
}

Database* Database::getInstace() {
    if (Database::instance == nullptr) {
        Database::instance = new Database();
    }
    return Database::instance;
}
