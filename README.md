
# Table of Contents

1.  [Disclaimer](#orgc8dd95b)
2.  [Install instructions](#org537c188)
    1.  [Windows](#org568d29e)
    2.  [Linux](#org7a50f64)

A project that aims to be a GUI frontend to select files and then use then as arguments of a shell command.


<a id="orgc8dd95b"></a>

# Disclaimer

The program is still in development and so you may see a lot of `printf()` and `g_print` for debugging. I'm also just starting to learn C and is my first experience with GTK and so the code isn't very efficient as you can imagine&#x2026;


<a id="org537c188"></a>

# Install instructions


<a id="org568d29e"></a>

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


<a id="org7a50f64"></a>

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

Don't forget to add to path if you want to execute it globally!

