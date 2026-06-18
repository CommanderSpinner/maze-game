#pragma once

#include <sqlite3.h>
#include <iostream>
#include "Entity.hpp"
#include "Global.hpp"
#include "EntityType.hpp"
#include "Record.hpp"

class Database {
private:
    sqlite3* db = nullptr;
    sqlite3_stmt *stmt;
    const std::string DB_STRUCTURE = R"(
    CREATE TABLE data(
        id INTEGER PRIMARY KEY,
        x REAL NOT NULL,
        y REAL NOT NULL,
        health INT NOT NULL,
        type TEXT NOT NULL
        )
)";

    bool tableIsCreated() {

        const char *sql =
            "SELECT 1 FROM sqlite_master WHERE type='table' AND name=?;"; // prepared statment for potentially other tables as well in the future

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            return false; // error
        }

        sqlite3_bind_text(stmt, 1, "data", -1, SQLITE_STATIC);

        bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

        sqlite3_finalize(stmt);

        return exists;
    }

    void createDB() {
        char *errMsg = 0;

        if (sqlite3_exec(db, DB_STRUCTURE.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Table created successfully\n");
        }
    }
public:
    Database() {
        int rc = sqlite3_open(Global::dataBasePath.c_str(), &db);

        if (rc) {
            std::fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        } else {
            std::printf("DB opened successfully\n");
        }

        if(!tableIsCreated()) {
            createDB();
            std::printf("creating db\n");
        } else {
            std::printf("db already created\n");
        }
    }

    void insert(record& rec) {
        stmt = nullptr;

        const char *sql = "INSERT INTO data(id, x, y, health, type) VALUES (?, ?, ?, ?, ?)";

        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Insert failed: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt, 1, rec.id);
        sqlite3_bind_double(stmt, 2, rec.x);
        sqlite3_bind_double(stmt, 3, rec.y);
        sqlite3_bind_int(stmt, 4, rec.health);
        sqlite3_bind_text(stmt, 5, rec.type.c_str(), -1, SQLITE_STATIC);

        sqlite3_finalize(stmt);
    }

    std::unique_ptr<record> read(size_t id) {
        stmt = nullptr;
        std::unique_ptr<record> rec = std::make_unique<record>();


        const char *sql =
            "SELECT id, x, y, health, type FROM data WHERE id = ?;";

        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            std::fprintf(stderr,
                        "Prepare failed: %s\n",
                        sqlite3_errmsg(db));
            return rec;
        }

        rc = sqlite3_bind_int64(stmt, 1, static_cast<sqlite3_int64>(id));

        if (rc != SQLITE_OK) {
            std::fprintf(stderr,
                        "Bind failed: %s\n",
                        sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return rec;
        }

        rc = sqlite3_step(stmt);

        if (rc == SQLITE_ROW) {
            rec->id = static_cast<size_t>(sqlite3_column_int64(stmt, 0));
            rec->x = static_cast<float>(sqlite3_column_double(stmt, 1));
            rec->y = static_cast<float>(sqlite3_column_double(stmt, 2));
            rec->health = sqlite3_column_int(stmt, 3);

            const unsigned char *typeText = sqlite3_column_text(stmt, 4);

            if (typeText) {
                std::string typeStr(
                    reinterpret_cast<const char *>(typeText)
                );

                rec->type = typeStr;
            }
        }
        else if (rc == SQLITE_DONE) {
            std::fprintf(stderr, "No record found with id %zu\n", id);
        }
        else {
            std::fprintf(stderr, "Step failed: %s\n",sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);

        return rec;
    }

    ~Database() {
        sqlite3_close(db);
    }
};