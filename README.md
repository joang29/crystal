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
cd crystal-FM/crystal
g++ * -o crystalfm -lstdc++fs
sudo install -Dm 775 crystalfm /usr/local/bin
```

# Usage
|               Keys               | Function                                                  |
|:--------------------------------:|-----------------------------------------------------------|
| `h` `j` `k` `l` / `w` `a` `s` `d`| Navigate                                                  |
|                `q`               | Open Settings                                             |
|                `e`               | Return to file manager                                    |
|                `r`               | Open search bar                                           |
|              `space`             | (Only available in settings) activate/deactivate settings |
|                `x`               | Close file manager                                        |
