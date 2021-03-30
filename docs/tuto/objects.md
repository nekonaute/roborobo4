# Object Creation

```eval_rst 
.. note::
    The source code for this tutorial can be found in ``pyRoborobo_examples/objects.py`` and ``pyRoborobo_examples/py_switch_example.py``.

```

It is possible to create custom objects with Pyroborobo. First of all, you must create a class that inherit from either `CircleObject` or `SquareObject`. Let's recreate the Gate and Switch object of the wanderer environment using python. An object must implement the reset and step function. The constructor receives a `data` dictionary containing all the information put in the configuration file. 

```python
from pyroborobo import SquareObject, CircleObject, Pyroborobo

class SwitchObject(CircleObject):
    def __init__(self, id, data):
        CircleObject.__init__(self, id)  # Do not forget to call super constructor
        self.regrow_time = data['regrowTimeMax']
        self.cur_regrow = 0
        self.triggered = False
        self.gate_id = data['sendMessageTo']
        self.rob = Pyroborobo.get() # Get pyroborobo singleton

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False

    def is_walked(self, id):
        print("I'm walked")
        self.triggered = True
        self.rob.objects[self.gate_id].open()
        self.cur_regrow = self.regrow_time
        self.hide()
        self.unregister()


class GateObject(SquareObject):
    def __init__(self, id, data):
        SquareObject.__init__(self, id)
        self.triggered = False
        self.regrow_time = data['regrowTimeMax']
        self.cur_regrow = 0

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False

    def open(self):
        self.triggered = True
        self.hide()
        self.unregister()
        self.cur_regrow = self.regrow_time
```

Now, we need to tell in our configuration file that we want to use the objects that we defined. To do so, let's update our config file. For instance, if we work on `pyRoborobo_examples/py_switch_example.py` we can see the difference between the two config files `pyRoborobo_examples/config/pywander.properties` and `pyRoborobo_examples/config/pywander_pyobj.properties`. The edits are as simple as :

```
  # Here we declare that we want a python object with the id "gate"
physicalObjects[0].pytype = gate
# And here a switch
physicalObjects[1].pytype = switch
physcialObjects[1].sendMessageTo = 0
```

Then, when we create our Pyroborobo object, we must pass a dictionary mapping the `pytype` key to our object classes. The Controller classes comes from the previous tutorial

```python
from pyroborobo import Pyroborobo, PyWorldModel
from controllers import SimpleController
from objects import GateObject, SwitchObject

rob = Pyroborobo.create("config/pywander_pyobj.properties",
                        controller_class=SimpleController,
                        world_model_class=PyWorldModel,
                        object_class_dict={'gate': GateObject, 'switch': SwitchObject})
rob.start()
rob.update(3000)
Pyroborobo.close()
```


We can also tell roborobo that we want objects without explicitly giving their pytype. To do so, we will overwrite the `gPhysicalObjectDefaultType` in the property file. This entry takes an id to a C++ Physical object class. To tell pyroborobo that we want python default object, we must set the value of this property to -1.

```
gPhysicalObjectDefaultType = -1
```

Then, we must give a class definition to the object_class_dict with the special key `_default`.

Let’s create a simple resource object that write a message when eaten, it looks a lot like a switch object

```python
from pyroborobo import Pyroborobo, CircleObject

class ResourceObject(CircleObject):
    def __init__(self, id_, data):
        CircleObject.__init__(self, id_)  # Do not forget to call super constructor
        self.regrow_time = 100
        self.cur_regrow = 0
        self.triggered = False
        self.rob = Pyroborobo.get()  # Get pyroborobo singleton

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False

    def is_walked(self, id):
        self.triggered = True
        self.cur_regrow = self.regrow_time
        self.hide()
        self.unregister()
```

Then we just have to edit our main. We change the simple controller for a hungry controller that seek resource objects.


```python
from pyroborobo import Pyroborobo, PyWorldModel

from objects import SwitchObject, GateObject, ResourceObject

if __name__ == "__main__":
    rob = Pyroborobo.create("config/pywander_pyobj_resource.properties",
                            controller_class=SimpleController,
                            world_model_class=PyWorldModel,
                            object_class_dict={'_default': ResourceObject, 'gate': GateObject, 'switch': SwitchObject})
    rob.start()
    rob.update(3000)
    Pyroborobo.close()

```

And that's it !