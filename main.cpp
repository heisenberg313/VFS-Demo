#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>  //for removing files
#include <cstdlib> //for system commands (like del /Q for rm -R)

using namespace std;

const string BASE_PATH = "D:\\CLionProjects\\VFS_Demo\\CRUD Files\\";

//checks if a file exists on the disk
bool fileExists(string filename) {
    ifstream infile(BASE_PATH + filename);
    return infile.good();
}


//TOUCH (Create)
void runTouch() {
    string filename;
    cout << "  [touch] Enter filename: ";
    cin >> filename;

    if (fileExists(filename)) {
        cout << "  Error: File '" << filename << "' already exists." << endl;
    } else {
        ofstream outfile(BASE_PATH + filename);
        if (outfile.is_open()) {
            outfile.close();
            cout << "  Success: Created '" << filename << "'" << endl;
        } else {
            cout << "  Error: Could not create file. (Check if folder exists)" << endl;
        }
    }
}

//----------ABDULLAH ZAHOOR----------

//----------SARIM MAQBOOL----------

//RM (Delete Single)
void runRm() {
    string filename;
    cin >> filename;

    //SPECIAL CASE: DELETE ALL FILES
    if (filename == "-R") {
        cout << "  [Warning] Deleting ALL files in: " << BASE_PATH << endl;
        //construct Windows command: del /Q "Path\*.*"
        string command = "del /Q \"" + BASE_PATH + "*\"";
        system(command.c_str());
        cout << "  Success: All files deleted." << endl;
    }
    //NORMAL CASE: DELETE ONE FILE
    else {
        if (!fileExists(filename)) {
            cout << "  Error: File '" << filename << "' not found." << endl;
        } else {
            string fullPath = BASE_PATH + filename;
            if (remove(fullPath.c_str()) == 0) {
                cout << "  Success: Removed '" << filename << "'" << endl;
            } else {
                cout << "  Error: Could not remove file." << endl;
            }
        }
    }
}

//LS (List Files - Optional Helper)
void runLs() {
    cout << "\nDirectory: " << BASE_PATH << endl;
    //windows command to list files simply
    string command = "dir /b \"" + BASE_PATH + "\"";
    system(command.c_str());
}


int main() {
    string command;

    cout << "============================================" << endl;
    cout << "      LOCAL FILE SYSTEM (CRUD DEMO)         " << endl;
    cout << "============================================" << endl;
    cout << "Current Path: " << BASE_PATH << endl;
    cout << "Commands: touch, echo, cat, rm (or rm -R), exit" << endl;

    //ensure the directory exists (Simple Windows command to make dir if missing)
    string mkdirCmd = "mkdir \"" + BASE_PATH + "\" 2> NUL";
    system(mkdirCmd.c_str());

    while (true) {
        cout << "\nMyOS> ";
        cin >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "touch") {
            runTouch();
        }
        else if (command == "echo") {
            runEcho();
        }
        else if (command == "cat") {
            runCat();
        }
        else if (command == "rm") {
            //note: runRm handles the filename input internally
            //because it needs to check if you typed "-R"
            runRm();
        }
        else if (command == "ls") {
            runLs();
        }
        else {
            cout << "  Unknown command." << endl;
        }
    }

    return 0;
}