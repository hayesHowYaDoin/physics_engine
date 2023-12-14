# C++ Library Template

This repository hosts a template to be used as a starting point for creating 
standard C++ libraries. The layout is inspired by the 
[Pitchfork Layout (PFL)][1], and uses a Docker Dev Container with VSCode. The 
included example code provides an example of how to utilize the layout in 
order to create a split between private and public headers using the 
[pImpl pattern][2].

## Prerequisites

The following instructions assume that Docker, VSCode and Git are installed on 
the host computer. The VSCode extension Remote Development 
(ms-vscode-remote.vscode-remote-extensionpack) is required to open the project 
in a Dev Container. 

## Setting Up The Development Environment

1) Clone the repository onto the host computer with the following command:
   ```
    git clone https://github.com/hayesHowYaDoin/header_template.git
   ```
2) Open the folder in VSCode. In the Command Palette (Ctrl+Shift+P), execute 
the command "Dev Containers: Open Folder In Container..."

And... that's it!

[1]: https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs
[2]: https://en.cppreference.com/w/cpp/language/pimpl
