// FileWatcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include "IFileWatcherListener.h"
#include "CFileSystemWatcher.h"

#include <fstream>

using namespace std;

class FileWatcherListener : public IFileWatcherListener
{
public:
    ofstream out;

    FileWatcherListener()
    {
        out.open("log.txt");
    }

	~FileWatcherListener()
    {
        out.close();
    }

private:
    void WriteLogText(const string& text, const std::wstring& path)
    {
        string log;
    	
        log.append(text);
        log.append(std::string(path.begin(), path.end()));
    	
        if(out.is_open())
        {
            out << log << "\n";
        }
    }
	
    // Inherited via IFileWatcherListener
    virtual void OnFileChange(const std::wstring& path) override
    {
        cout << "\nOnFileChange: ";
        wcout << path << "\n";

        WriteLogText("OnFileChange: ", path);
    }

    // Inherited via IFileWatcherListener
    virtual void OnFileAdded(const std::wstring& path) override
    {
        cout << "\nOnFileAdded: ";
        wcout << path << "\n";

        WriteLogText("OnFileChange: ", path);
    }

    // Inherited via IFileWatcherListener
    virtual void OnFileRemoved(const std::wstring& path) override
    {
        cout << "\nOnFileRemoved: ";
        wcout << path << "\n";

        WriteLogText("OnFileChange: ", path);
    }

    // Inherited via IFileWatcherListener
    virtual void OnFileRenamed(const std::wstring& path) override
    {
        cout << "\nOnFileRenamed: ";
        wcout << path << "\n";

        WriteLogText("OnFileChange: ", path);
    }

};


int main()
{
    /**Get Path for Watching*/
    wstring watchPath = L"D:\\Log";

    cout << "Enter Direction/File Path for Watching: ";
    wcin >> watchPath;
	
    /*!
     * Creates watcher by passing the watch directory
     *
     */
    CFileSystemWatcher watcher(watchPath);
    /*!
     *
     * Creates Linstener
     */
    IFileWatcherListener* listener = new FileWatcherListener();

    //passes the listener to watcher
    watcher.AddFileChangeListener(listener);
    int choice;
    do
    {
        cout << "\n\nMENU";
        cout << "\n1. Start Directory Watcher";
        cout << "\n2. Stop Directory Watcher";
        cout << "\n3. Exit";
        cout << "\n\nEnter your choice 1-3 :";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (!watcher.Running())
                watcher.Start();
            else
                cout << "\nWatcher is already started ..";
        }
        break;
        case 2:
            watcher.Stop();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\nInvalid choice";
        }
    } while (choice != 3);

    delete listener;

    return 0;
}

