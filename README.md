<!--
SPDX-FileCopyrightText: 2025 thorium1256

SPDX-License-Identifier: GPL-3.0-or-later
-->

# Minesweeper... in the terminal!

Minesweeper is a classic puzzle game where the objective is to clear a rectangular board without detonating any hidden mines.

## How to Play

The board consists of hidden cells, some containing mines. Uncover a cell by selecting its coordinates. If it's a mine, you lose. If it's safe, a number appears indicating how many mines are adjacent to that cell.
**Use logic to deduce mine locations and mark them with flags.**
Marking all mines with flags isn't necessary, but helps.

### Clear all non-mine cells to win!

## Controls

Arrows to move.  
Z to reveal.  
X to flag.  
C to chord.  
R to restart.  
P to pause.  
Q to quit.

You can't chord if the number isn't equal to the number of flags it's near.
You can't see the board if you're paused to (help) prevent cheating.
You can't flag already revealed cells.

## Compilation

### Windows

For compiling on Windows, you need MSYS2 and MinGW-w64.
If you want, you can compile on MSVC (if you get it to work), I don't care.

The prerequisites are _ncurses_. Only that.

The DLLs are not included in this repository, you should go get 'em yourself, and put them in the `lib` folder.

Rename the `Makefile.win` file, make, and you got Minesweeper.

But I have to mention something if it says something about no libraries found. MSYS2, for some reason, has been including dynamic libraries really weirdly in their packages. They only add the static libraries and don't get the dynamic ones. And that makes me angry. I don't know why they did this, but it's confusing. Please just put the DLLs in mingw64/lib and not in mingw64/bin.

Anyway, if it says something about that, just patch the Makefile with **normal** LDFLAGS and try again.

### Unix/Linux

Every normal Unix/Linux system has ncurses, but not always the development headers needed for compilation.
Installation for these:

**Debian/Ubuntu**:

```sh
sudo apt install libncurses-dev
```

**Arch**:

```sh
sudo pacman -S ncurses
```

**Fedora**:

```sh
sudo dnf install ncurses-devel
```

**Other distros**:  
Search engines are your best friend.

Then rename `Makefile.unix`, press the make button, and a moment later, you got it.
