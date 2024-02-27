#include "classes.h"

//// User Class Functions      //////////////////////////////////////

void User::fetchDB(sqlite3* db, string ID) {

    string sql = "SELECT * FROM Users WHERE ID = ?;"; // Fetch the user data by ID
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        this->name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        this->ID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        this->memberType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        this->record = sqlite3_column_double(stmt, 4);
        this->fine = sqlite3_column_double(stmt, 5);
        this->rentLimit = sqlite3_column_int(stmt, 6);
        // Parse rented cars
        // string rentedCarsStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        // // Assuming rentedCarsStr is comma-separated list of car IDs
        // size_t pos = 0;
        // while ((pos = rentedCarsStr.find(',')) != string::npos) {
        //     rentedCars.push_back(rentedCarsStr.substr(0, pos));
        //     rentedCarsStr.erase(0, pos + 1);
        // }
        // rentedCars.push_back(rentedCarsStr); // Add the last car ID
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void User::updateDB(sqlite3* db, string ID) {

    // Update the user data in the database
    string sql = "UPDATE Users SET Name = ?, Password = ?, MemberType = ?, Record = ?, Fine = ?, RentLimit = ? WHERE ID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, memberType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, record);
    sqlite3_bind_double(stmt, 5, fine);
    sqlite3_bind_int(stmt, 6, rentLimit);

    // Prepare rented cars string
    // string rentedCarsStr;
    // for (const auto& carID : rentedCars) {
    //     rentedCarsStr += carID + ",";
    // }
    // rentedCarsStr.pop_back(); // Remove the last comma

    // sqlite3_bind_text(stmt, 7, rentedCarsStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, ID.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void User::showAllCars(sqlite3* db) {
    cout << "All cars in the system: " << endl;

    string sql = "SELECT * FROM Cars;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW) {
        cout << "Model: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)) << endl;
        cout << "Registration No: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)) << endl;
        cout << "Condition: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) << endl;
        cout << "Rented: " << (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) == "0" ? "Yes" : "No") << endl;
        cout << "----------------------------------------------\n";
        rc = sqlite3_step(stmt);
    }

    // Fetch all cars from the database
    // for (const auto& car : cars) {
    //     car.getDetails();
    // }
}

void User::rentCar(Car &car) {
    if (rentedCars.size() >= rentLimit) {
        cout << "You have reached your rent limit." << endl;
    } else {
        car.rentRequest(*this);
        rentedCars.push_back(car);
    }
}

//// Manager Class Functions      //////////////////////////////////////

void Manager::addCar(sqlite3* db, Car &car) {

    string sql = "INSERT INTO Cars (Model, RegistrationNo, Condition, isRented, RenterID, RenterName, RenterType, DueDate) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "1 SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, car.model.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, car.regNo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, car.condition);
    sqlite3_bind_int(stmt, 4, (car.isRented ? 1 : 0));
    sqlite3_bind_text(stmt, 5, car.renterID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, car.renterName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, car.renterType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, car.dueDate.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Manager::removeCar(sqlite3* db, Car &car) {

    string sql = "DELETE FROM Cars WHERE RegistrationNo = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, car.regNo.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Manager::updateCar(sqlite3* db, Car &car) {
    car.updateDB(db);
}

void Manager::addUser(sqlite3* db, User &user) {
    // Add user to the database

    string sql = "INSERT INTO Users (Name, ID, Password, MemberType, Record, Fine, RentLimit) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.ID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.memberType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, user.record);
    sqlite3_bind_double(stmt, 6, user.fine);
    sqlite3_bind_int(stmt, 7, user.rentLimit);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        cout << "Hi Manager!, You have successfully registered a/an " << user.memberType << " ( " << user.name << " ) with ID : " << ID << endl;
    } else {
        cerr << "Error registering user." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);


}

void Manager::removeUser(sqlite3* db, User &user) {
    // Remove user from the database

    string sql = "DELETE FROM Users WHERE ID = ? AND NAME = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user.ID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Manager::updateUser(sqlite3* db, User &user) {
    user.updateDB(db, user.ID);
}

//// Car Class Functions         //////////////////////////////////////

void Car::fetchDB(sqlite3* db) {
    // Fetch the car data from the database

    string sql = "SELECT * FROM Cars WHERE RegistrationNo = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, regNo.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        this->model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        this->regNo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        this->condition = sqlite3_column_double(stmt, 2);
        this->isRented = (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) == "0" ? false : true);
        this->renterID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        this->dueDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

}

void Car::updateDB(sqlite3* db) {

    string sql = "UPDATE Cars SET Model = ?, Condition = ?, isRented = ?, RenterID = ?, RenterName = ?, RenterType = ?, DueDate = ? WHERE RegistrationNo = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, model.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, condition);
    sqlite3_bind_text(stmt, 3, (isRented ? "TRUE" : "FALSE"), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, renterID.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, renterName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, renterType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, dueDate.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
