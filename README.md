<h1 align=center>crystalfm</h1>

![image](https://github.com/joang29/crystalfm/assets/85022759/2f559065-a17a-4a68-a333-2ce399b81d19)

# Why use crystalfm?

- Fast navigation ⚡
- Search files in the directory 🔎
- Tabs feature 🪟
- File operations (rename, move, delete, copy, paste, compress and decompress) ✅
- Create files and directories 🗃️
- Directory and file preview 📁
- Image preview (kitty or w3mimgdisplay) 🖼️
- Gif preview (only available with kitty) ▶️
- Custom keybindings ⌨️
- Custom themes 🟣 🔵 🟢 ⚪
- File icons 🔲 🔳

# Dependencies
- [Nerd Font](https://github.com/ryanoasis/nerd-fonts/tree/master/patched-fonts/Iosevka)
- **kitty** / **w3mimgdisplay**
- **xdg-utils**
- **unzip (optional)**

# Installation
Before installing crystalfm, please make sure you have all dependencies installed.

To install crystalfm run:
```
make install
```

# Configuration

To configure crystalfm you should edit the files, ``crystal.conf`` for general use and ``keys.conf`` to modify the keys to your liking (they are in the directory ``~/.config/crystal/``)

Check [this](https://github.com/joang29/crystalfm/tree/main/crystal/themes) out for custom themes.

# Usage
|               Keys               | Function                                                  |
|:--------------------------------:|-----------------------------------------------------------|
|          `h` `j` `k` `l`         | Navigate                                                  |
|                `a`               | Go to the bottom of the directory                         |
|                `A`               | Go to the top of the directory                            |
|                `v`               | Go to the middle of the directory                         |
|                `/`               | Type a path                                               |
|                `t`               | Open a new tab                                            |
|                `H`               | Move to the left tab                                      |
|                `J`               | Move to the right tab                                     |
|                `D`               | Delete the current tab                                    |
|                `d`               | Open search bar                                           |
|                `z`               | Select files                                              |
|                `c`               | Copy file                                                 |
|                `x`               | Move file                                                 |
|                `s`               | Create file                                               |
|                `S`               | Create dir                                                |
|                `f`               | Rename file                                               |
|                `g`               | Compress files                                            |
|                `G`               | Decompress file                                           |
|                `X`               | Delete file                                               |
|                `?`               | Help                                                      |
|                `q`               | Close file manager                                        |
