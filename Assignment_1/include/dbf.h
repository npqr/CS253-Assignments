#ifndef DBF_H
#define DBF_H

//// Database Functions         //////////////////////////////////////

#include "classes.h"
#include "sqlite/sqlite3.h"

int executeQuery(sqlite3* db, const char* sql) {
    char* errMsg;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

bool databaseExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

void createDatabase(const string& filename) {
    sqlite3* db;
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "Error creating SQLite database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    const char* createUsers = "CREATE TABLE Users (Name TEXT NOT NULL, ID TEXT NOT NULL PRIMARY KEY, Password TEXT NOT NULL, MemberType TEXT NOT NULL, Record REAL, Fine REAL, RentLimit INTEGER, RentedCars TEXT)";
    if (executeQuery(db, createUsers) != SQLITE_OK) { 
        cerr << "Error creating Users table." << endl;
        sqlite3_close(db);
        exit(1);
    }

    
    const char* createCars = "CREATE TABLE Cars (Model TEXT, RegistrationNo TEXT PRIMARY KEY, Condition TEXT, isRented INTEGER, RenterID TEXT, RenterName TEXT, RenterType TEXT, DueDate TEXT)";
    if (executeQuery(db, createCars) != SQLITE_OK) { 
        cerr << "Error creating Car table." << endl;
        sqlite3_close(db);
        exit(1);
    }

    cout << "SQLite database and tables created successfully." << endl;
    sqlite3_close(db);
}



#endif // DBF_H