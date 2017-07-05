#include <iostream>
#include <csignal>
#include <boost/filesystem.hpp>

/*
-------------------------------------
subberthehut helper (sth-helper)
https://github.com/saojeda/sth-helper
-------------------------------------
A simple CLI utility for GNU/Linux systems* that automates subberthehut's search & download
process by running it recursively inside a directory containing multiple video files

*Tested under Arch Linux (Antergos)

[Dependencies]
-subberthehut (https://github.com/mus65/subberthehut)
-Boost C++ library (http://www.boost.org/)

[Installation]
$ g++ sth-helper.cpp -o sth-helper -lboost_filesystem -lboost_system (compile)
$ sudo mv sth-helper /usr/bin (move to /usr/bin in order to allow it to execute everywhere)

[Usage]
$ sth-helper (note: execute inside the desired directory containing video files)

MIT License

Copyright (c) 2017 Sun Arthur Ojeda

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

*/

using namespace std;
using namespace boost::filesystem;

// Handler function for handling cancel event
void handler(int signum) {
  cout << endl << "+ Task terminated." << endl;
  exit(signum);
}

int main(int argc, char* argv[]) {
  path p(".");
  string command, filename;
  int i = 0;

  cout << "+ Task started. Press ctrl-c within 3 seconds to cancel" << endl;
  // Install signal to handle cancel event
  signal(SIGINT, handler);
  // Wait for 3 seconds
  sleep(3);
  // Ignore subsequent cancel events
  signal(SIGINT, SIG_IGN);

  // Recursively explore the directory
  for (directory_entry& x : recursive_directory_iterator(p)) {
    filename = x.path().string();

    // Check for possible video files,
    if (filename.find(".mp4") != string::npos
        || filename.find(".mkv") != string::npos
        || filename.find(".m4v") != string::npos
        || filename.find(".avi") != string::npos
        || filename.find(".ogg") != string::npos
        || filename.find(".flv") != string::npos
        || filename.find(".webm") != string::npos) {
        cout << "+ Processing: " << filename << endl;
        // Prepare command with the given file name
        command = "subberthehut \"" + filename + "\" --same-name --quiet";
        system(command.c_str());
        i++;
    }
  }

  if (i > 0) cout << "+ Finished. Processed " << i << " files." << endl;
  else cout << "+ Finished. No video files found!" << endl;

  return 0;
}
