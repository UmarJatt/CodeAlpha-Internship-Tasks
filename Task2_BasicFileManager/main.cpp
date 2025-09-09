#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>      // for system()
#include <cstring>      // for strerror()
#ifdef _WIN32
#include <direct.h>     // for _mkdir() on Windows
#else
#include <sys/stat.h>   // for mkdir() on Unix/Linux
#include <dirent.h>     // for directory operations
#endif

using namespace std;

// Create a directory
void createDirectory(const string& directoryName) {
#ifdef _WIN32
    if (_mkdir(directoryName.c_str()) == 0) {
        cout << "✅ Directory '" << directoryName << "' created successfully!\n";
    } else {
        cerr << "❌ Error creating directory: " << directoryName << endl;
    }
#else
    if (mkdir(directoryName.c_str(), 0777) == 0) {
        cout << "✅ Directory '" << directoryName << "' created successfully!\n";
    } else {
        cerr << "❌ Error creating directory: " << directoryName << endl;
    }
#endif
}

// Create a file with content
void createFile(const string& filePath, const string& content) {
    ofstream outfile(filePath);
    if (outfile.is_open()) {
        outfile << content << endl;
        outfile.close();
        cout << "✅ File created successfully!\n";
    } else {
        cerr << "❌ Error creating/opening file: " << filePath << endl;
    }
}

// View contents of a directory
void viewDirectoryContents(const string& directoryName) {
#ifdef _WIN32
    system(("dir " + directoryName).c_str());
#else
    DIR* dir = opendir(directoryName.c_str());
    if (dir == nullptr) {
        cerr << "❌ Could not open directory: " << directoryName << endl;
        return;
    }
    cout << "📂 Contents of directory '" << directoryName << "':\n";
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }
    closedir(dir);
#endif
}

// View contents of a file
void viewFileContents(const string& filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        cout << "📄 Content of file " << filename << ":\n";
        string line;
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    } else {
        cerr << "❌ Unable to open file: " << filename << endl;
    }
}

// Copy a file
void copyFile(const string& sourceFile, const string& destinationFile) {
    ifstream src(sourceFile, ios::binary);
    ofstream dest(destinationFile, ios::binary);
    if (!src) {
        cerr << "❌ Could not open source file: " << sourceFile << endl;
        return;
    }
    if (!dest) {
        cerr << "❌ Could not open destination file: " << destinationFile << endl;
        return;
    }
    dest << src.rdbuf();
    cout << "✅ File copied successfully!\n";
}

// Move a file
void moveFile(const string& sourceFile, const string& destinationFile) {
    if (rename(sourceFile.c_str(), destinationFile.c_str()) != 0) {
        cerr << "❌ Error moving file: " << strerror(errno) << endl;
        return;
    }
    cout << "✅ File moved successfully!\n";
}

int main() {
    system("color 03"); // Optional: Set console color on Windows
    string command, arg1, arg2;

    while (true) {
        cout << "\n\t🎛 Welcome to File Manager\n";
        cout << "1) Create Directory\t2) Create File\n";
        cout << "3) View Directory\t4) View File\n";
        cout << "5) Copy File\t\t6) Move File\n";
        cout << "0) Exit\nChoose here: ";
        getline(cin, command);

        if (command == "0") break;

        if (command == "1") {
            cout << "Enter directory name: ";
            getline(cin, arg1);
            system("cls");
            createDirectory(arg1);
        } else if (command == "2") {
            cout << "Enter file path: ";
            getline(cin, arg1);
            cout << "Enter file content: ";
            getline(cin, arg2);
            system("cls");
            createFile(arg1, arg2);
        } else if (command == "3") {
            cout << "Enter directory name: ";
            getline(cin, arg1);
            system("cls");
            viewDirectoryContents(arg1);
        } else if (command == "4") {
            cout << "Enter file path: ";
            getline(cin, arg1);
            system("cls");
            viewFileContents(arg1);
        } else if (command == "5") {
            cout << "Enter source file path: ";
            getline(cin, arg1);
            cout << "Enter destination file path: ";
            getline(cin, arg2);
            system("cls");
            copyFile(arg1, arg2);
        } else if (command == "6") {
            cout << "Enter source file path: ";
            getline(cin, arg1);
            cout << "Enter destination file path: ";
            getline(cin, arg2);
            system("cls");
            moveFile(arg1, arg2);
        } else {
            cout << "❌ Invalid command. Please enter a valid option.\n";
        }
    }

    cout << "👋 Exiting File Manager. Goodbye!\n";
    return 0;
}