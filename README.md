
# Table of Contents

1.  [Install instructions](#org2bda01e)
    1.  [Windows](#orgb316134)
    2.  [Linux](#org2b61af0)

A project that aims to be a GUI frontend to select files and then use then as arguments of a shell command.


<a id="org2bda01e"></a>

# Install instructions


<a id="orgb316134"></a>

## Windows

-   Install [MSYS2](https://www.msys2.org/)
-   Open the MSYS2 MINGW64 shell (the one with the blue icon)
-   Install the following packages using pacman:
    
        pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gtk3
-   Clone this repository somewhere:
    
        git clone https://github.com/arturfabriciohahaedgy/file-parameter-selector.git
-   Use make inside directory:
    
        cd file-parameter-selector
        make windows #don't forget to write windows after make!


<a id="org2b61af0"></a>

## Linux

Make sure to have the following dependencies installed:

-   GTK 3
-   GTK 4
-   A C compiler (project has only been tested with GCC)
-   Git

Then clone this repository:

    git clone https://github.com/arturfabriciohahaedgy/file-parameter-selector.git

Use make:

    cd file-parameter-selector
    make

