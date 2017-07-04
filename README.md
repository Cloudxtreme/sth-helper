# **subberthehut helper (sth-helper)**

A simple CLI utility for GNU/Linux systems* that automates subberthehut's 
search & download process by running it recursively inside a directory containing multiple video files

*Tested under Arch Linux (Antergos)

**[Credits]**
-saojeda (author)
-vivithemage (majority of the filesystem code)
(https:gist.github.com/vivithemage/9517678)

**[Dependencies]**  
-subberthehut (https://github.com/mus65/subberthehut)  
-Boost library (http://www.boost.org/)

**[Installation]**  
`$ g++ sth-helper.cpp -o sth-helper -lboost_filesystem -lboost_system` (compile)  
`$ sudo mv sth-helper /usr/bin` (move to /usr/bin in order to allow it to execute everywhere)   

**[Usage]**   
`$ sth-helper` (note: execute inside the desired directory containing video files)  
