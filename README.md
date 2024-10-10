# Anterminal

Terminal emulator. Nothing too fancy.

## How to build

To build anterminal you will need some dependencies, so first install these packages in your system

> [!WARNING]
> This command may have to be changed depending on your actual linux distro

For a debian-based system you could try using this

```sh
sudo apt install libvte-2.91-dev libconfig-dev
```

and for arch-based

```sh 
sudo pacman -S vte3 libconfig
```

Then go ahead and clone the repository.

```sh
git clone https://github.com/antma-window-manager/anterminal.git anterminal
```

So now, you can go inside the source tree and type `sudo make install` to build and install
anterminal!

```sh
cd anterminal
sudo make install
```

> [!NOTE]
> By default anterminal will use the installation prefix `/usr/local` so you'll get
> `/usr/local/bin/anterminal` and `/usr/local/share/applications/anterminal.desktop`.

## Tips

### Cleaning the source tree

You can use:

```sh
sudo make clean
```

### Specifying an installation prefix

You can install anterminal in a specified prefix instead, so per example, you can do
something like this which is useful when, per example, packaging anterminal.

```
mkdir -pv ~/rootfs
sudo make clean
make clean
make PREFIX=$HOME/rootfs install
```

Which results in something like this:

```
$ tree ~/rootfs
/home/user/rootfs
├── bin
│  └── anterminal
└── share
   └── applications
      └── anterminal.desktop
```

And to uninstall from that ~/rootfs folder

```sh
make PREFIX=$HOME/rootfs uninstall
```

## Customizing

For customization, I (NameGoesThere) worked my ass off for 3 hours getting .conf support working. So here is how you do it. <br>
Go into your .config folder (~/.config), then make a file named anterminal.conf <br>
Once you have opened anterminal.conf with something like vim or nano, there are a lot of things you are able to change.

### Example conf
```
OPACITY = 0.8;

BACKGROUND = "#000000";
FOREGROUND = "#ffffff";

BLACK = "#000000";
RED = "#cd0000";
GREEN = "#00cd00";
YELLOW = "#cdcd00";
BLUE = "#0000ee";
MAGENTA = "#cd00cd";
CYAN = "#00cdcd";
WHITE = "#e5e5e5";
LIGHT_BLACK = "#7f7f7f";
LIGHT_RED = "#ff0000";
LIGHT_GREEN = "#00ff00";
LIGHT_YELLOW = "#ffff00";
LIGHT_BLUE = "#5c5cff";
LIGHT_MAGENTA = "#ff00ff";
LIGHT_CYAN = "#00ffff";
LIGHT_WHITE = "#ffffff";

FONT = "monospace";
FONT_SIZE = 12;
```

## Rebuilding
To rebuild the thing, u need to first clean the folder with

```sh
make clean
```

> Note that you may require to use sudo if you installed with `sudo make install`

and then properly build it with

```sh
make
```

and then install it using the `install` target again

```sh
sudo make install
```

## Screenshots

![2024-08-03_17-24](https://github.com/user-attachments/assets/cdb3ae81-6693-411f-8b46-41f18d681526)
![2024-08-05 02-17](https://i.imgur.com/po3TSox.png)

## Thanks to

- [RationalTerm](https://rationalstudios.org/): Which is the original terminal used here.
