#pragma once

#include <sqlite3.h>
#include <iostream>

class Database {
private:
    sqlite3* db = nullptr;
    const std::string DBSQL= "";
public:
    Database() {
        int rc = sqlite3_open("mydatabase.db", &db);

        if (rc) {
            std::fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        } else {
            std::printf("DB opened successfully");
        }
    }

    ~Database() {
        sqlite3_close(db);
    }
};