<h1 align=center>crystal-FM</h1>

![image](https://github.com/joang29/crystal/assets/85022759/444826d8-cfba-406e-b507-f52b53d1f32c)

# Dependencies 🗃:
- [Nerd Font](https://github.com/ryanoasis/nerd-fonts/tree/master/patched-fonts/Iosevka)
- **kitty** / **w3mimgdisplay** 

# Installation
Before installing crystal-fm, please make sure you have all dependencies installed.

To install crystal-fm run:
```
git clone https://github.com/joang29/crystal-FM
g++ crystal-FM/crystal/* -o crystalfm -lstdc++fs
sudo install -Dm 775 crystalfm /usr/local/bin
rm crystalfm
```

# Usage
|               Keys               | Function                                                  |
|:--------------------------------:|-----------------------------------------------------------|
|          `h` `j` `k` `l`         | Navigate                                                  |
|                `y`               | Open Settings                                             |
|              `space`             | (Only available in settings) activate/deactivate settings |
|                `u`               | Return to file manager                                    |
|                `d`               | Open search bar                                           |
|                `a`               | Create file                                               |
|                `x`               | Create dir                                                |
|                `f`               | Rename file                                               |
|                `z`               | Delete file                                               |
|                `q`               | Close file manager                                        |
