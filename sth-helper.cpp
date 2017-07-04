#include <iostream>
#include "boost/filesystem.hpp"

/*
A simple CLI utility for GNU/Linux systems* that automates subberthehut's
search & download process by running it recursively inside a directory 
containing multiple video files

*Tested under Arch Linux (Antergos)

[Dependencies]
-subberthehut (https://github.com/mus65/subberthehut)
-Boost library (http://www.boost.org/)

[Credits]
-saojeda (author)
-vivithemage (majority of the filesystem code)
(https:gist.github.com/vivithemage/9517678)
*/

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[]) {
    // list all files in current directory.
    path p(".");
    directory_iterator end_itr;
    string current_file, command;

    // cycle through the directory
    for (directory_iterator itr(p); itr != end_itr; itr++) {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            current_file = itr->path().string();
            // Check if the file is a supported video file, you can also add extra conditions for extra filenames
            if (current_file.find(".mkv") != string::npos
              || current_file.find(".mp4") != string::npos
              || current_file.find(".m4v") != string::npos
              || current_file.find(".avi") != string::npos
              || current_file.find(".ogg") != string::npos) {
              // Erase "spawn" characters in front of the filename
              current_file.erase(0,2);
              // Prepare command with the current filename
              command = "subberthehut \"" + current_file + "\" --same-name --quiet";
              cout << "[Processing file]: " << current_file << endl;
              // Convert string to char in order for system() function to accept it as argument
              const char *cmd = command.c_str();
              system(cmd);
              cout << endl;
            }
        }
    }
    cout << "Finished.\n";
    return 0;
}
