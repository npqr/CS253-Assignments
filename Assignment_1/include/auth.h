#ifndef AUTH_H
#define AUTH_H

//// Auth Functions               //////////////////////////////////////

void registerUser(sqlite3* db, const User& user) {
    string Name = user.getName();
    string ID = user.getID();
    string password = user.getPassword();

    string query = "INSERT INTO Users (Name, ID, Password) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, Name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, ID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        cout << "Hi! " << Name << ", You have registered successfully with ID : " << ID << endl;
    } else {
        cerr << "Error registering user." << endl;
    }

    sqlite3_finalize(stmt);
}

bool loginUser(sqlite3* db, const string& ID, const string& password) {
    bool auth = false;
    string query = "SELECT COUNT(*), Name FROM Users WHERE ID = ? AND Password = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);

    if (count == 1) {
        string Name = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        cout << "Hi, " << Name << "! Welcome Back :)\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        auth = true;
    } else {
        cerr << "Sorry, Invalid ID or password. Please try again!" << endl;
    }

    sqlite3_finalize(stmt);
    return auth;
}

#endif // AUTH_H