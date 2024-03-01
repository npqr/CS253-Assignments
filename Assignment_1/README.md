<center><strong><h1>CaR-e-MaSys v1.0</h1></strong></center>

```
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::           _________ _________  ____ ___  ____ ________  _______          ::
::          / ___/ __ `/ ___/ _ \/ __ `__ \/ __ `/ ___/ / / / ___/          ::
::         / /__/ /_/ / /  /  __/ / / / / / /_/ (__  / /_/ (__  )           ::
::         \___/\__,_/_/   \___/_/ /_/ /_/\__,_/____/\__, /____/            ::
::                                                  /____/                  ::
::                                                                     v1.0 ::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
```

## Setup Instructions :

1. Clone this repo
2. If you are on a Linux machine, run the `bash` script `./run.sh`, while Windows users can run the `ps` script `.\run.ps1`, or alternatively

    ```
    g++ -o main main.cpp ./include/jsoncpp/jsoncpp.cpp
    ./main
    ```

    Note the difference between `/` and `\` in the paths. Also, Linux users may need to run `chmod +x run.sh` before running the script

3. After running `.\run` once, you can continue with `.\run 1` to run the program than compiling it again everytime.


## Structure

- The project is organised into following files housing the respective components :
    - `classes.hpp` : Contains the declarations for all the classes
    - `classes.cpp` : Contains the definitions for classes, functions and other methods included in `classes.hpp`
    - `dbf.hpp` : Contains the required functions for file-handling (the databased is encoded in JSON and then retrieved as well)
    - `global.hpp` :     Contains some essential functions and macros required
    - `help.hpp` : Houses few helper functions, mostly semantic purposes
    - `jsoncpp` : Houses the amalgamated library for parsing and interconversion of JSON Values (Source : [jsoncpp](https://github.com/open-source-parsers/jsoncpp))
    - `main.cpp` : It includes the above files and houses the core functionalities of the application

## Conventions

- Initially the system is equipped with 5 Cars, 5 Customers, 5 Employees and 1 Manager
- There are different databases (`static` maps of `Customers*`, `Employees*` and `Cars*`) for Customers, Employees and Cars. All of these are housed in a separated class `DBMgr`, which also contains various functions required for the overall functionality
- The `Customer`, `Employee` and `Manager` classes are derived from the `User` class
- A Registration-Login System is implemented. New Users (Customers/Employees) can register themselves too
- The Manager can also create accounts, if needed
- The Manager cannot be deleted, also, only one Manager is implemented by-default; although creation of another Manager can be done easily, but it is not deemed that beneficial
- A search mechanism based on substrings has been implemented
- A simple date-parsing mechanism has been applied (with another class dedicated for that) and thus, dates can be handled in the system
- It is expected that input is fed without spaces, and in case of multiple words, the words are separated by underscores
- The User is presented with a menu with various options to choose from, as well as a Dashboard is displayed too
- At various instances, ANSI Escape Sequences are used for colour manipulation in the CLI
- Credentials of the Manager are `ID : jarvis`, `password : jarvis`

## Few Assumptions and Concerns

- The maximum days for which a car can be rented is 15
- The maximum number of cars that can be rented by a customer at a time is by-default (RentLimit), which can be altered
- The database, as stored in a JSON file, is encoded in a specific manner, and thus, the file should not be tampered with manually. Othewise, the system may crash
- By-default, record of each Customer and Employee is initialised a `75.9` which is updated as and whem the user pays dues, returns the car, etc depending on the car condition and other factors
- It is assumed that the condition of car can not be more than what it was initially, except when updated by the Manager (simiulating repair)
- The login credentials are case-sensitive. Also, they can be accessed directly from the JSON file. A hashing mechanism can be implemented, though
- Note : Abrupt termination of the program may lead to loss of data, as the data is stored in a JSON file, and is updated as and when the program is run
- The system also detects your environment of operations and implements the platfrom-dependent functions accordingly e.g. for clearing screen and sleep function etc