# Troubleshooting

## Pyroborobo is not found

Be sure that you have activated your conda virtual env, like:

```bash
conda activate roborobo
```


## I have a lot of warning from pybind11 when I build pyroborobo

Ensure that you use the latest pybind11 version from conda forge, and not the one from brew or pip.

```bash
# run at your own risks
pip uninstall pybind11
brew uninstall pybind11
conda install -c conda-forge pybind11
```

## I have a segfault

Be sure that your object on the python side correspond to the right object on the c++ side. When implementing code on the c++ side with a python binding, always test if you don't return `null` or receive a `null` value. Raise exceptions when you have unwanted `null` values. This will give pybind11 clearer error and avoids segfaults.

Be sure to use shared_ptr in your python bindings if you write your own C++ code !!!

## pybind11 is not defined

Your pyroborobo specific code **must be** in a pyroborobo folder. Being in a folder named pyroborobo **prevents** your code from being included in the standalone version of ``roborobo``. Having pyroborobo specific code in a file which is not in a folder named ``pyroborobo`` will prevent your code from compiling.


## pyroborobo does not start, cannot find data or config

Be sure that you have a data folder and a config folder in the directory of your project. pyroborobo **does not use** roborobo's `config` and `data` directory. You must copy them in your project.

## pyroborobo does not compile

You should clear all Cmake cache to ensure that old cache is not blocking the compilation. You should also ensure that you have the latest version of pybind, sdl and all pyroborobo dependencies.

### Clearing cmake cache

You must remove cmake cache by deleting the following folders: 

- `build/`
- `dist/`
- `cmake-build-debug`

This can be done using the following command in bash

```bash
rm -rf build dist cmake-build-debug
# the f flag prevent failure if a directory does not exist
# to be sure :
python setup.py clean --all
```

### Installing/updating pyroborobo dependencies

#### Linux

run the following command:

```bash
sudo apt-get install cmake buildessentials
sudo apt-get install libsdl2-dev libsdl2-image-dev libboost-dev libeigen3-dev
sudo apt-get update
sudo apt-get upgrade  # Be careful that it updates only the packages that you want to be upgraded
```

```bash
conda install pybind11 numpy sphinx recommonmark sphinx_rtd_theme numpydoc  # install dependencies for the doc

conda update pybind11 numpy numpy sphinx recommonmark sphinx_rtd_theme numpydoc
```

#### MacOS

```bash
brew install sdl2
brew install sdl2_image
brew install boost
brew install cmake
brew update
```

```bash
conda install numpy pybind11 numpy sphinx recommonmark sphinx_rtd_theme numpydoc
conda update numpy pybind11 numpy sphinx recommonmark sphinx_rtd_theme numpydoc
```