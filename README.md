# WARNING
After some weird issues with GTK I've decided to rewrite the project using other libraries and so this repository is only here for achival purposes. The new project can be found [here](https://github.com/arturfabriciohahaedgy/file-parameter-selector-REDUX.git);

# Table of Contents

1.  [Disclaimer](#disclaimer-link)
2.  [Install instructions](#install-instructions-link)
    1.  [Windows](#windows-link)
    2.  [Linux](#linux-link)

A project that aims to be a GUI frontend to select files and then use then as arguments of a shell command.

<a id="disclaimer-link"></a>

# Disclaimer

The program is still in development and so you may see a lot of `printf()` and `g_print` for debugging. I'm also just starting to learn C and is my first experience with GTK and so the code isn't very efficient as you can imagine.

<a id="install-instructions-link"></a>

# Install instructions

<a id="windows-link"></a>

## Windows

-   Install [MSYS2](https://www.msys2.org/)
-   Open the MSYS2 MINGW64 shell (the one with the blue icon)
-   Install the following packages using pacman:

``` shell
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gtk3
```

-   Clone this repository somewhere:

``` shell
git clone https://github.com/arturfabriciohahaedgy/file-parameter-selector.git
```

-   Run the `configure` script

``` shell
cd file-parameter-selector
./configure
```

-   Use make inside directory:

``` shell
cd file-parameter-selector
make windows # don't forget to write windows after make!
```

- Add `FPS.exe` to PATH if you want.
    
<a id="linux-link"></a>

## Linux

Make sure to have the following dependencies installed:

-   GTK 3
-   GTK 4
-   A C compiler (project has only been tested with GCC)
-   Git

Then clone this repository:

``` shell
git clone https://github.com/arturfabriciohahaedgy/file-parameter-selector.git
```

Run the `configure` script

``` shell
cd file-parameter-selector
./configure
```

Use make:

``` shell
make
```

Don't forget to add to path if you want to execute it globally!
