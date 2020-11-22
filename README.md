# S-Expression parser and printer

This program is heavely inspired by https://github.com/benthepoet/c-sexpr-parser/ and rework some logic to fit our needs and add a nested fashion printing option.

The dataset used for the unit test is stored in the [dataset/exemple.sexp](dataset/exemple.sexp) path.

##  How to build
To build the program please use the Makefile provided by invoking the make command:
```bash
make
```
The Makefile support the **cross-compilation**, to build the program for an other architecture please fill the **$CROSS_COMPILATION** environment variable with the prefix of your toolchain (e.g: `arm-linux-gnueabihf-` only, if you are using the `arm-linux-gnueabihf` GCC, LD, etc.
Your toolchain should be available in your **$PATH**:
```bash
CROSS_COMPILATION=arm-linux-gnueabihf- && make
```

## How to use
This program comes with some options, please at least use the **-p** for printing or **-t** for testing the dataset respectively:
```bash
./sexpr -h
Usage : sexpr [options]
Options:
        -h      print this help message
        -p      print the output of the sexpression dataset in a nested fashion format
        -t      run test on the dataset, only work with the default dataset (exemple.sexp)
        -d      specify the dataset path to use
```

## Full cross-compile exemple for ARM with Qemu
First you need to install **qemu-arm**, it depends on your Linux distribution.

Then download an arm toolchain, i'm using the bootlin toolchain for armv6 available here:
https://toolchains.bootlin.com/downloads/releases/toolchains/armv6-eabihf/tarballs/armv6-eabihf--glibc--stable-2020.08-1.tar.bz2

Extract the toolchain, then before compiling the project, do the following:
```bash
ARCH=arm
PATH=/path_to_your_extracted_toolchain/armv6-eabihf--glibc--stable-2020.08-1/bin/:$PATH
CROSS_COMPILE=arm-linux-
LD_LIBRARY_PATH=/path_to_your_extracted_toolchain/armv6-eabihf--glibc--stable-2020.08-1/arm-buildroot-linux-gnueabihf/sysroot/
```

You can now invoked the program with the following command:
```bash
qemu-arm -L $LD_LIBRARY_PATH ./sexpr
```
