#include "stdafx.h"
#include "SQLiteManager.h"
#include <LXFileUtil/LXFileUtil.h>

static SQLiteManager* g_pSQLiteManager = nullptr;

SQLiteManager::SQLiteManager():
	_db(nullptr)
{
	if (_db) {
		sqlite3_close(_db);
	}
}

SQLiteManager * SQLiteManager::getInstance()
{
	if (g_pSQLiteManager == nullptr) {
		g_pSQLiteManager = new (std::nothrow) SQLiteManager();
	}
	return g_pSQLiteManager;
}

bool SQLiteManager::initWithDBPath(const std::string & path)
{
	std::string fullpath = LX_FU::getAbsolutePath(path).c_str();
	int rc = sqlite3_open(fullpath.c_str(), &_db);
	if (rc) {
		LX_LOG("Can't open database: %s\n", sqlite3_errmsg(_db));
		sqlite3_close(_db);
		return false;
	}
	else {
		LX_LOG("Create database with path: %s\n", fullpath.c_str());
		return true;
	}
}


SQLiteManager::~SQLiteManager()
{
}
