<h1 align=center>crystal-FM</h1>

![image](https://github.com/joang29/crystal/assets/85022759/444826d8-cfba-406e-b507-f52b53d1f32c)

# Dependencies 🗃:
- [Nerd Font](https://github.com/ryanoasis/nerd-fonts/tree/master/patched-fonts/Iosevka)
- **kitty** / **w3mimgdisplay** 

# Installation
Before installing crystal-fm, please make sure you have all dependencies installed.

To install crystal-fm run:
```
make install
```

# Configuration

To configure crystalfm you should edit the files, ``config.h`` for general use and ``keys.h`` to modify the keys to your liking (if you have previously installed crystalfm they will be located in ``~/.config/crystal/`` but if not they will be inside the ``crystal-FM/crystal/`` directory), when you finish configuring in the crystal-FM directory run:
```
make config
```

# Usage
|               Keys               | Function                                                  |
|:--------------------------------:|-----------------------------------------------------------|
|          `h` `j` `k` `l`         | Navigate                                                  |
|                `d`               | Open search bar                                           |
|                `z`               | Select files                                              |
|                `c`               | Copy file                                                 |
|                `x`               | Move file                                                 |
|                `s`               | Create file                                               |
|                `S`               | Create dir                                                |
|                `f`               | Rename file                                               |
|                `X`               | Delete file                                               |
|                `q`               | Close file manager                                        |
