# Anterminal

Anterminal is a customized Open-Source terminal based on the `RationalTerm` terminal.

## How to build

To build anterminal you will need some dependencies, so first install these packages in your system

> [!WARNING]
> This command may have to be changed depending on your actual linux distro

For an ubuntu-based system you could try using this

```sh
sudo apt install libvte-2.91-dev
```

Then go ahead and clone the repository.

```sh
git clone https://github.com/fdiskzlez/anterminal.git anterminal
```

So now, you can go inside the source tree and type `make` to build a binary!

```sh
cd anterminal
make
```

After building, you would have to be able to install the binary and run it like every other program

```sh
sudo install -Dvm755 ./anterminal /bin/anterminal
anterminal
```

> [!TIP]
> To clean the object files and the binary from the source tree, you may've to run `make clean`

## Screenshots

![2024-08-03_17-24](https://github.com/user-attachments/assets/cdb3ae81-6693-411f-8b46-41f18d681526)

## Thanks to

- [RationalTerm](https://rationalstudios.org/): Which is the original terminal used here.
