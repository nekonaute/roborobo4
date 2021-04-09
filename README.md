# Roborobo.4


**Roborobo** is a fast and simple 2D mobile robot simulator loosely based on low-cost mobile robots such as khepera or epuck models. It is targeted for fast single and multi-robots simulation for evolutionary robotics and machine learning in multi-agent systems, collective and swarm robotics .

**Roborobo** combines speed of development _and_ speed of execution. Roborobo can be programmed with python 3.x, with all the core functions written in C++ for super fast execution.

## Version

Roborobo version 4 is currently the __only__ supported version. Current official release is (from: *roborobo.cpp*):
 * *gVersion = 20210321*
 * *gCurrentBuildInfo = Shangri-La build*

## Contributors

__Main contributors__

 * Nicolas Bredeche: main roborobo developper and project initiator (since 2009)
 * http://pages.isir.upmc.fr/~bredeche/
 * contact: nicolas.bredeche(at)sorbonne-universite.fr

 * Paul Ecoffet: pyRoborobo, the python interface to Roborobo (2020-2021)
 * Evert Haasdijk: properties management library (2010-2012)

__Other contributors__

 * Jean-Marc Montanier, Berend Weel, Amine Boumaza, Andreas Steyven, Leo Cazenille, Theotime Grohens, and a few others!

## How to cite Roborobo in your work

If you use __Roborobo__ in your work, __please cite the following paper__:

*N. Bredeche, J.-M. Montanier, B. Weel, and E. Haasdijk. Roborobo! a fast robot simulator for swarm and collective robotics. CoRR, abs/1304.2888, 2013.*

Link to the paper on Arxiv: http://arxiv.org/abs/1304.2888 

_Scientific papers that cite Roborobo_: https://scholar.google.fr/scholar?cites=7785979290259259170

___
# INSTALLATION

Roborobo basic dependencies are: 
* a C++ compiler (GCC or CLANG)
* Python 3.x

Supported platforms:
 * Linux-based
 * MacOS X

Linux and MacOS installation instructions are described below. Other platforms are not officially supported, but Roborobo was previously shown to run on: MS Windows, Raspbian and Pandora.

_Remark: if you get a lot of warnings during compilation, this is probably due to already installed pip packages shadowing the newly installed conda packages (e.g. with pybind). Work around for pyBind that may work: conda install -c conda-forge "pybind11>2.6". However the best way is to delete the pip packages and make a clean install of roborobo again__


## Linux

Create a conda environment:

```bash
conda create --name roborobo numpy pybind11 
conda activate roborobo
```

Install Python dependencies for Roborobo (numpy, pybind11, sphinx, ...) 

```bash
conda install numpy setuptools
conda install -c conda-forge pybind11
conda install sphinx recommonmark sphinx_rtd_theme numpydoc

# or if you prefer to use pip instead of Conda: 
# pip install -U pybind11
# pip install -U numpy
# pip install -U sphinx
```

Install C++ dependencies for Roborobo (Cmake, SDL2, boost and eigen):

```bash
sudo apt install git build-essential cmake 
sudo apt-get install libsdl2-dev libsdl2-image-dev libboost-dev libeigen3-dev
```

Get your local copy of Roborobo:

```bash
git clone https://github.com/nekonaute/roborobo4.git
```

Compile and install Roborobo:

```bash
# conda activate roborobo (if not already activated)
cd roborobo4
python setup.py install --force
```

Check the QUICK START section below for running a Roborobo example.

## Mac OS

Create a conda environment:

```bash
conda create --name roborobo numpy pybind11 
conda activate roborobo
```

Install Python dependencies for Roborobo (numpy, pybind11, sphinx, ...) 

```bash
conda install numpy setuptools
conda install -c conda-forge pybind11
conda install sphinx recommonmark sphinx_rtd_theme numpydoc

# or if you prefer to use pip instead of Conda: 
# pip install -U pybind11
# pip install -U numpy
# pip install -U sphinx
```

Install C++ dependencies for Roborobo (Cmake, SDL2, boost and eigen):

```bash
brew install cmake 
brew install sdl2
brew install sdl2_image
brew install boost
brew install eigen
```

Get your local copy of Roborobo:

```bash
git clone https://github.com/nekonaute/roborobo4.git
```

Compile and install Roborobo:

```bash
# conda activate roborobo (if not already activated)
cd roborobo4
python setup.py install --force
```

Check the QUICK START section below for running a Roborobo example.
___
# QUICK START

It is highly suggested to use the __python__ interface to Roborobo, which we refer to as __pyRoborobo__. If you prefer to develop your project in C++, it also possible (check below). pyRoborobo is built as an interface to Roborobo, and though there is of course a cost to use Python instead of pure C++, we empirically consider it worth the ease of development in the context of academic research. For example, the Boids example runs at ~400 fps (pure C++) and ~200 fps (pyRoborobo) on a Macbook pro 13 (early 2019 model).

Roborobo (C++) and pyRoborobo (Python) both uses three important directories, that should be accessible from where your code (C++ binary or python script) is run. 
* **_data_** contains image and resources for setting a roborobo environment
* **_config_** contains configuration files for running a roborobo environment 
* **_logs_** will contain log files generated during a roborobo run

While running an example, type "h" when the focus is on the Roborobo window. Help tips will be displayed in the console.

## Running a Python example

Activate conda environment (if not done already):
```bash
conda activate roborobo
```

Compile and install Roborobo (if not done already):
```bash
cd <your_roborobo_folder>
# python setup.py clean --all -- only if want to rebuild all from scratch
python setup.py install --force 
```

Run a pyRoborobo example:

```bash
cd <your_roborobo_folder>/pyRoborobo_dev/examples/
python tutorial.py
```

Many other examples are available in the __pyRoborobo_dev/examples__ folder.

## Build the pyRoborobo API documentation

Build Roborobo's python API documentation:
```bash
# conda activate roborobo (if not already activated)
python setup.py build_sphinx
```

The pyRoborobo API documentation is now in _build/sphinx/html/index.html_


## Running a C++ example

If you installed Roborobo for the first time, setup the directory structure for running Roborobo: 

Setup the directory structure for both C++ and Python development (done only once):

```bash
# Roborobo C++ code
cd <your_roborobo_folder>/build
ln -s ../data
ln -s ../config
ln -s ../logs
```

Activate conda environment (if not done already):
```bash
conda activate roborobo
```

Compile and install Roborobo (to be done everytime you modify the C++ code:
```bash
cd <your_roborobo_folder>
# python setup.py clean --all -- only if want to rebuild all from scratch
python setup.py install --force 
```

Run a roborobo example:

```bash
cd <your_roborobo_folder>/build
./roborobo -l config/Tutorial.properties
```

Roborobo (C++) examples can be found in the <your_roborobo_folder>/prj directory. Note that project selection is achieved from the configuration file (config/filename.properties)

## What next?

 * Check _OVERVIEW.TXT for a __quick introduction__.
 * Check _FAQ.TXT for __trouble shooting__ and __frequently asked questions__.
 * Check the examples, and learn by doing.
___

_Thank you for using Roborobo!_
