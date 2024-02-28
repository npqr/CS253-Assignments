#ifndef DBF_H
#define DBF_H

//// Database Functions         //////////////////////////////////////

#include "classes.h"
#include "jsoncpp/json/json.h"
#include "jsoncpp/json/json-forwards.h"
#include "global.h"

void God::importData() {

    Json::Value root;
    ifstream file("db/data.json");
    // ifstream file("db/sampledata.json");
    file >> root;
    file.close();

    for (auto user : root["users"]) {
        User newUser(
        (std::string) user["name"].asString(),
        (std::string) user["ID"].asString(), 
        (std::string) user["password"].asString());
        newUser.rentLimit = user["rentLimit"].asInt();
        newUser.memberType = user["memberType"].asString();
        newUser.record = user["record"].asDouble();
        newUser.fine = user["fine"].asDouble();
        Users[newUser.getID()] = newUser;
    }

    for (auto car : root["cars"]) {
        Car newCar((std::string) car["model"].asString(),
        (std::string) car["regNo"].asString(),
        (float) car["condition"].asFloat(),
        (bool) car["isRented"].asBool(),
        (std::string) car["renterID"].asString(),
        (std::string) car["dueDate"].asString());
        Cars[newCar.getRegNo()] = newCar;
    }
}

void God::exportData() {

    //use file handling to convert the data present in god class to convert to json file

    Json::Value root;
    Json::Value users;
    Json::Value cars;

    for (auto user : Users) {
        Json::Value userNode;
        userNode["name"] = user.se.getName();
        userNode["ID"] = user.se.getID();
        userNode["password"] = user.se.getPassword();
        userNode["record"] = user.se.getRecord();
        userNode["fine"] = user.se.getFine();
        userNode["rentLimit"] = user.se.rentLimit;
        userNode["memberType"] = user.se.memberType;

        users.append(userNode);
    }

    for (auto car : Cars) {
        Json::Value carNode;

        carNode["regNo"] = car.se.getRegNo();
        carNode["model"] = car.se.getModel();
        carNode["condition"] = car.se.getCondition();
        carNode["isRented"] = car.se.getisRented();
        carNode["renterID"] = car.se.getRenterID();
        carNode["dueDate"] = car.se.getdueDate();

        cars.append(carNode);
    }

    root["users"] = users;
    root["cars"] = cars;

    ofstream file("db/data.json");
    // ofstream file("db/sampledata.json");
    
    file << root;
    file.close();

}


#endif // DBF_H