Noah Billedo - CMPM 123
The following contents are an implementation of a Dear imGUI logging system, created on a Windows system.

This implementation of the logging system contains the ability to execute commands, and also provides buttons at the top of the window to execute these same commands.
Currently, the logging system displays information top-down from oldest to newest. It has the capability of inputting test logs, filtering out logs based on severity level, print current
visible logs to file, clear the console, and the ability to take command line input. Below are the files modified and details of modification.

Logger.h
Contains the implementation of the logger Class and it's functions called by the UI implemented in Application.cpp. Takes logs as a int level and char* message pair and pushes it onto a 
imGUI vector. These logs are then iteratively drawn on the console and can also be cleared or printed to logs.txt with the functions of the Logger Class. The Logger class also contains 
the Execute() function that matches strings from the command line to implemented functions.

Application.cpp
The file that holds the implementation of the Console Log Window UI. Uses imGUI button items to execute functions from Logger.h. Application.cpp also contains a separate filter window
that opens and closes upon clicking the filter button. This window contains the commands that allow the user to filter the logs by severity level. The implementation for taking user
input via the command line is also within this file.

Note: I hid the demo in Application.cpp by commenting it out.
