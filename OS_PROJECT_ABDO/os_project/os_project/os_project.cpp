// os_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Directory.h"
#include "virtual_disk.h"
#include "Mini_FAT.h"
#include "Converter.h"


using namespace std;
int main()
{
    // Step 1: Initialize the virtual disk and Mini_FAT
    string diskName = "virtual_disk.dat";
    Mini_FAT::initialize_Or_Open_FileSystem(diskName);
    cout << "Virtual disk and FAT system initialized." << endl;


    // Step 2: Create the root directory
    Directory root("root", 'D', 0, nullptr); // Root directory: name "root", type 'D', starts at cluster 0
    cout << "Root directory created." << endl;


    // Step 3: Add entries (files or directories) to the root directory
    Directory_Entry file1("file1.txt", 'F', Mini_FAT::getAvailableCluster());
    file1.dir_fileSize = 512; // Example size of 512 bytes
    root.addEntry(file1);
    cout << "Added file: " << file1.dir_name << endl;
    Directory_Entry file2("file2.txt", 'F', Mini_FAT::getAvailableCluster());
    file2.dir_fileSize = 1024; // Example size of 1024 bytes
    root.addEntry(file2);
    cout << "Added file: " << file2.dir_name << endl;


    // Step 4: Display directory contents
    cout << "\nCurrent directory contents:" << endl;
    for (const auto& entry : root.DirOrFiles) {
        cout << "Name: " << entry.dir_name
            << ", Size: " << entry.dir_fileSize
            << ", First Cluster: " << entry.dir_firstCluster << endl;
    }

    // Step 5: Search for a file in the directory
    string searchName = "file1.txt";
    int index = root.searchDirectory(searchName);
    if (index != -1) {
        cout << "\nFile " << searchName << " found in the directory at index " << index << "." << endl;
    }
    else {
        cout << "\nFile " << searchName << " not found in the directory." << endl;
    }

    // Step 6: Remove a file from the directory
    root.removeEntry(file1);
    cout << "\nRemoved file: " << file1.dir_name << endl;

    // Step 7: Display updated directory contents
    cout << "\nUpdated directory contents:" << endl;
    for (const auto& entry : root.DirOrFiles) {
        cout << "Name: " << entry.dir_name
            << ", Size: " << entry.dir_fileSize
            << ", First Cluster: " << entry.dir_firstCluster << endl;
    }

    // Step 8: Write the directory to the virtual disk
    root.writeDirectory();
    cout << "\nDirectory written to the virtual disk." << endl;

    // Step 9: Read the directory back from the disk
    root.readDirectory();
    cout << "\nDirectory read from the virtual disk. Contents:" << endl;
    for (const auto& entry : root.DirOrFiles) {
        cout << "Name: " << entry.dir_name
            << ", Size: " << entry.dir_fileSize
            << ", First Cluster: " << entry.dir_firstCluster << endl;
    }

    // Step 10: Print the FAT for verification
    cout << "\nFile Allocation Table (FAT):" << endl;
    Mini_FAT::printFAT();

    // Step 11: Close the system
    Mini_FAT::CloseTheSystem();

    cout << "\nSystem safely closed." << endl;

    return 0;
}

