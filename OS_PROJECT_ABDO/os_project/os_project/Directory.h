#pragma once
#include "DirectoryEntry.h"
#include <vector>
using namespace std;

class Directory : public Directory_Entry {
public:

    vector<Directory_Entry> DirOrFiles; // Children
    Directory* parent;                  // Parent directory

    Directory(string name, char dir_attr, int dir_firstCluster, Directory* pa);

    Directory_Entry GetDirectory_Entry();
    int getMySizeOnDisk();
    bool canAddEntry(Directory_Entry d);
    void emptyMyClusters();
    void writeDirectory();
    void readDirectory();
    void addEntry(Directory_Entry d);
    void removeEntry(Directory_Entry d);
    void deleteDirectory();
    void updateContent(Directory_Entry OLD, Directory_Entry NEW);
    int searchDirectory(string name);
};
