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

```diff
! DISCLAIMER : This software was compiled on g++ version 6.3 and might break on later versions.
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
    - [`classes.hpp`](include/classes.hpp) : Contains the declarations for all the classes
    - [`classes.cpp`](include/classes.cpp) : Contains the definitions for classes, functions and other methods included in `classes.hpp`
    - [`dbf.hpp`](include/dbf.hpp) : Contains the required functions for file-handling (the databased is encoded in JSON and then retrieved as well)
    - [`global.hpp`](include/global.hpp) :     Contains some essential functions and macros required
    - [`help.hpp`](include/help.hpp) : Houses few helper functions, mostly semantic purposes
    - [`jsoncpp`](include/jsoncpp/) : Houses the amalgamated library for parsing and interconversion of JSON Values (Source : [jsoncpp](https://github.com/open-source-parsers/jsoncpp))
    - [`main.cpp`](main.cpp) : It includes the above files and houses the core functionalities of the application

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
- The maximum number of cars that can be rented by a customer at a time is by-default (RentLimit), which can be altered, and it also gets updated as and when the customer returns the car, depending on the customer record
- The database, as stored in a JSON file, is encoded in a specific manner, and thus, the file should not be tampered with manually. Othewise, the system may crash
- By-default, record of each Customer and Employee is initialised a `75.0` which is updated as and whem the user pays dues, returns the car, etc depending on the car condition and other factors
- It is assumed that the condition of car can not be more than what it was initially, except when updated by the Manager (simiulating repair)
- The login credentials are case-sensitive. Also, they can be accessed directly from the JSON file. A hashing mechanism can be implemented, though
- Note : Abrupt termination of the program may lead to loss of data, as the data is stored in a JSON file, and is updated as and when the program is run
- Also, in most cases, the input is sanitised, but the system may crash sometimes if the input is unexpected (e.g. a <kbd>Ctrl + Z</kbd> key-stroke)
- The system also detects your environment of operations and implements the platfrom-dependent functions accordingly e.g. for clearing screen and sleep function etc
- We have assumed that the default date for non-rented cars is `1/1/2001` and for rented cars, it is the date of rent


## Sample (initial) DB

### CarsDB

|condition|dailyRent|expectedDays|isRented|model|regNo|rentDate|renterID|
|-|-|-|-|-|-|-|-|
|74.0|2500.0|5|TRUE|Lightning McQueen|MCQRCR|12/2/2023|gotham|
|60.0|2000.0|5|FALSE|Tow Mater|TOWM8R|1/1/2001||
|86.0|3500.0|5|FALSE|Batmobile|BATMAN|1/1/2001||
|43.0|1500.0|5|FALSE|Optimus Prime|OPTIMUS|1/1/2001||
|72.0|4000.0|5|FALSE|Bumblebee|BBBEE|1/1/2001||


### CustomersDB

|ID|due|memberType|name|password|record|rentLimit|rentedCars|
|-|-|-|-|-|-|-|-|
|sheldont|0.0|Customer|Sheldon Cooper|bazinga|71.6|5| |
|breakingbad|0.0|Customer|Walter White|wizwhite|75.0|5| |
|dp|0.0|Customer|Deadpool|regenerate|71.0|3| |
|captain|0.0|Customer|Jack Sparrow|blackpearl|75.0|5| |
|spidey|0.0|Customer|Peter Parker|mjw|75.0|5| |


### EmployeesDB

|ID|due|memberType|name|password|record|rentLimit|rentedCars| | | | | | | |
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
| | | | | | | |condition|dailyRent|expectedDays|isRented|model|regNo|rentDate|renterID|
|007|0.0|Employee|James Bond|bond007|75.0|5| | | | | | | | |
|mindpalace|0.0|Employee|Sherlock Holmes|elementary|75.0|5| | | | | | | | |
|apple|0.0|Employee|Isaac Newton|gravity|75.0|5| | | | | | | | |
|gotham|12500.0|Employee|Bruce Wayne|batman|60.3|5|74.0|2500.0|5|TRUE|Lightning McQueen|MCQRCR|12/2/2023|gotham|
|ron302|0.0|Employee|Hermione Granger|leviosa|75.0|5| | | | | | | | |
|jarvis|0.0|Manager|Tony Stark|jarvis|75.0|5| | | | | | | | |
