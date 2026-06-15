#pragma once

#include <sqlite3.h>
#include <iostream>
#include "Entity.hpp"


struct record {
    size_t id;
    float x, y;
    int health;
    entityType type;
};

class Database {
private:
    sqlite3* db = nullptr;
    const std::string DB_STRUCTURE= "
    CREATE TABLE data(
        id INTEGER PRIMARY KEY,
        x REAL NOT NULL,
        y REAL NOT NULL,
        health INT NOT NULL,
        type TEXT NOT NULL
        )
    ";

    bool checkTable() {
        
    }

    void callback() {

    }
public:
    Database() {
        int rc = sqlite3_open(dataBasePath, &db);

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