# How to use pyroborobo

```eval_rst
.. note::
    The source code for this tutorial can be found in pyRoborobo_examples/controllers.py and pyRoborobo_examples/simple.py
```

Let's make a new directory containing our pyroborobo project.

```bash
cd ~/Documents/
mkdir pyrob_proj
cd pyrob_proj
```

We must then import the roborobo configs and data that we intend to use.

```bash
cp ~/path/to/roborobo/roborobo3/roborobo3/data data
cp ~/path/to/roborobo//roborobo3/roborobo3/config config
```

Then create a python file (for instance `main.py`) which will contain our python code.

The roborobo simulator is contained in a `Pyroborobo` singleton. `Pyroborobo.create()` creates
the Pyrororobo object. It takes as a first argument the configuration file for pyrobobo. 
`Pyroborobo.create()` can take more arguments that we will discuss later on. 

In `main.py`:
```python
from pyroborobo import Pyroborobo
rob = Pyroborobo.create("config/template_wander_smallrobots.properties")
```

Then, roborobo must be started with the `start` method. Simulation time steps are triggered with
the `update(nb_updates)` method. Finally, roborobo must be closed to free its memory.

```python
#main.py
from pyroborobo import Pyroborobo
rob = Pyroborobo.create("config/template_wander_smallrobots.properties")
rob.start()
rob.update(1000)
Pyroborobo.close()

```

Here, roborobo uses the Controllers, WorldModels, WorldObserver, PhysicalObjects and AgentObservers from the C++ Configuration Loader given in the configuration file. We can override these classes by python classes.

To do so, we must create a class that codes the new behaviour and provide it to the `Pyroborobo.create` method. The class that we use must inherit from the *Py* variant of the base class. Let's say we want to code a new Controller, to do so we create a new class `SimpleController` that inherits from `Controller`. Like in roborobo, we must provide a `step` method and a `reset` method to this controller. Let's add this to our `main.py` document before creating the `Pyroborobo` object.

```python
from pyroborobo import Controller

class SimpleController(Controller):
    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(world_model) 
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")
    
    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)  # and do not turn
```

Then, let's edit our code to tell roborobo to use our new controller.

```python
rob = Pyroborobo.create("config/template_wander_smallrobots.properties",
                        controller_class=SimpleController)
```

This is what `main.py` should look like : 
```python
from pyroborobo import Controller, Pyroborobo, PyWorldModel

class SimpleController(Controller):
    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(self, world_model) 
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")
    
    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)  # and do not turn

rob = Pyroborobo.create("config/template_wander_smallrobots.properties",
                        controller_class=SimpleController)
rob.start()
rob.update(1000)
Pyroborobo.close()
```

The controller has a world_model object to access and manipulate the robot behaviour. By default, the world_model object is a binding to the `RobotWorldModel` object and the available methods and fields are limited. Even if you have extended in cpp the `RobotWorldModel`, only the `RobotWorldModel` fields and methods are accessible.

It is also possible to override RobotWorldModel to extend its functionalities. pyroborobo provides the class `PyWorldModel` which already add many functionalities like the access to the camera sensors. We must tell that we want to use `PyWorldModel` to our `Pyroborobo` object.
Let's create a very simple obstacle avoidance controller.

```python
from pyroborobo import Pyroborobo, Controller

class SimpleController(Controller):

    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")

    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        if (self.get_distance_at(1) < 1 # if we see something on our left
                or self.get_distance_at(2) < 1): # or in front of us
            self.set_rotation(0.5) # turn right
        elif self.get_distance_at(3) < 1: # Otherwise, if we see something on our right
            self.set_rotation(-0.5) # turn left

rob = Pyroborobo.create("config/template_wander_smallrobots.properties",
                        controller_class=SimpleController,
                        world_model_class=PyWorldModel)
rob.start()
rob.update(1000)
Pyroborobo.close()
```

Controller also provides `get_object_at` giving the reference of the object seen if any  (otherwise None) and many other
helper methods.

All camera output are `numpy.view` on the raw memory from roborobo, any modification on these value triggers a numpy
copy that can impact the fps of roborobo by *a lot*. Avoid copy the most to avoid performance issues.
