#ifndef SQLITE_MANAGER_H
#define SQLITE_MANAGER_H

#include <SQLite3/sqlite3.h>
#include <string>

class SQLiteManager
{
public:
	SQLiteManager();
	static SQLiteManager* getInstance();
	bool initWithDBPath(const std::string& path);
	~SQLiteManager();
protected:
	sqlite3* _db;
};

#endif
