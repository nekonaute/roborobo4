Custom C++ Bindings
===================

You can add custom C++ bindings to your pyroborobo installation. To do
so, you must declare your C++ classes in the pybind11 pyroborobo module.

You should definitely read the `pybind11 tutorial and
documentation <https://pybind11.readthedocs.io/en/stable/>`_ before
trying to write your own bindings.

Looking at the source of the module definitions in
``contrib/pyroborobo/moduledefinitions`` give you nice examples of how
to write custom c++ to python bindings.

As an example, let's pretend that we want to create a new controller
subclass ``DistAwareController`` that adds the method
``distance_to_robot(int id)`` in pyroborobo. The function
``distanceToRobot`` is written in C++.

Let’s create a new project in roborobo. To do so, let’s clone the
roborobo’s ``Tutorial`` project.

.. code:: bash

   # Let's assume you are in the roborobo directory
   cd prj
   python2 clone_project.py Tutorial DistAware

There is now a folder ``DistAware`` in our ``prj`` folder. Let’s add the
method ``DistanceToRobot(int id)`` that compute the Euclidian distance
between the robot and the other robot of id ``id``. Let’s add its
signature in ``prj/DistAware/include/DistAwareController.h``

.. code:: cpp

   class DistAwareController : public Controller
   {
   public:
       DistAwareController(std::shared_ptr<RobotWorldModel> _wm);

       ~DistAwareController();

       void reset();

       void step();
       
       float distanceToRobot(int id);
   };

And let’s define this method in
``prj/DistAware/src/DistAwareController.cpp``

.. code:: cpp

   float DistAwareController::distanceToRobot(int id)
   {
       auto other = gWorld->getRobot(id)->getController(); // return shared_ptr<Controller>
       auto opos = other->getPosition();
       auto pos = getPosition();
       float dist = sqrt(pow(opos.x - pos.x, 2) + pow(opos.y - pos.y, 2));
       return dist;
   }

Now that we have created our new controller, let’s create its python
bindings.

Create a new file called ``DistAwarePythonBindings.cpp`` in
``prj/DistAware/src/pyroborobo`` and a file called ``DistAwarePythonBindings.h`` in
``prj/DistAware/include/pyroborobo``.

.. warning::

    Your pyroborobo specific code **must be** in a pyroborobo folder. Being in a folder named pyroborobo **prevents** your code from being included in the standalone version of ``roborobo``. Having pyroborobo specific cod in a file which is not in a folder named ``pyroborobo`` will prevent your code from compiling.

We will write the special python bindings in these files. To add a new
python binding in pyroborobo, we must create a function that receives as
an argument a reference to a ``pybind11::module``.

.. code:: cpp

    // DistAwarePythonBindings.h
    #ifndef ROBOROBO3_DISTAWAREPYTHONBINDINGS_H
    #define ROBOROBO3_DISTAWAREPYTHONBINDINGS_H

    #include <pybind11/pybind11.h>

    void addDistAwareBindings(pybind11::module &m);

    #endif //ROBOROBO3_DISTAWAREPYTHONBINDINGS_H



.. code:: cpp

    // DistAwarePythonBindings.cpp
    #include "DistAware/include/DistAwarePythonBindings.h"
    #include "DistAware/include/DistAwareController.h"
    #include "WorldModels/RobotWorldModel.h"
    #include "contrib/pyroborobo/ControllerTrampoline.h"
    #include <pybind11/pybind11.h>

    namespace py = pybind11;
    using namespace pybind11::literals;  // allow string literals like "argument"_a

    void addDistAwareBindings(py::module& m)
    {

    }

Now, we have to tell pybind11 that we want to add new bindings for our controller. Let's write ``addDistAwareBindings``.

First we must declare our new class, using ``pybind11::class_``. In code, the `pybind11` namespace is shorten with ``py``.

.. code:: cpp

    void addDistAwareBindings(py::module& m)
    {
    auto distcont = py::class_<DistAwareController, Controller, PyController<DistAwareController>, std::shared_ptr<DistAwareController> >(m, "DistAwareController", R"doc(doc string)doc");

    }

The usage of ``pybind11::class_`` is complex. You should definitely look at its documentation. To be short, the first argument of the template is the class that we want to bind, the second argument is the class from which our class inherits. It allows `pybind11` to know that we want to access all the methods written in Controller. The third argument link to a *Trampoline* class. Trampoline class write special code that allow pybind to override c++ function with python functions in the subclasses. ``PyController`` is a special template class that will work with any controller that you write. It is included in ``contrib/pyroborobo/ControllerTrampoline.h``. The fourth argument is the way we want pybind11 to handle reference counts. Here we use the cpp shared pointer, used everywhere in roborobo. It prevents segfault when the python interpreter stops. The first argument of the constructor is our module ``m`` that we received in argument. It is the ``pyroborobo`` module where we want to attach our class. The second argument is the name of the python Class for ``pyroborobo``. The third argument is the docstring of our class.

.. warning::

    Writing something wrong in this class definition **will result** in segfault or in unexpected behaviour in your code.
    Always check that you provide : The parent class of your new c++ class, the Trampoline class (using a template), and
    the way to handle memory (in pyroborobo, it's always a shared_ptr).

.. note::

    Pyroborobo provide Trampoline template for AgentObserver, WorldModel, WorldObserver and the differents Object. You will find them in the header files of pyroborobo (``include/contrib/pyroborobo/``).


We **must** declare a python constructor for our new class. To add a new method to our class, we use the ``def`` method.

.. code:: cpp

    void addDistAwareBindings(py::module& m)
    {
        auto distcont = py::class_<DistAwareController, Controller, PyController<DistAwareController>, std::shared_ptr<DistAwareController> >(m, "DistAwareController");
        distcont.def(py::init<std::shared_ptr<RobotWorldModel>>(), "robot_world_model"_a, R"doc(our custom Controller Init function)doc");
    }

We add the special method ``__init__`` with ``py::init``. The init template takes as argument the type of the constructor arguments, here a shared pointer to a ``RobotWorldModel``.

.. warning::

    Not using ``std::shared_pointer`` here will cause segfaults!!!

Finally, we add the binding to our function with another call to ``def``.

.. code:: cpp

    void addDistAwareBindings(py::module& m)
    {
            auto distcont = py::class_<DistAwareController, Controller, PyController<DistAwareController>, std::shared_ptr<DistAwareController> >(m, "DistAwareController");
        distcont.def(py::init<std::shared_ptr<RobotWorldModel>>(), "world_model"_a, "");
        distcont.def("get_distance_to_robot", &DistAwareController::distanceToRobot, "id"_a, R"doc(float: The distance to the robot of id ``id``.)doc");
    }

We call def on our python class definition and give it its python name, the pointer to the method we want to call, and we provide the name of the arguments as well as a docstring.


Now, we just have to add our python bindings function to the module. To do so, we must edit the file ``src/contrib/pyroborobo/customModuleDefinitions.cpp`` and add a call to our function in ``addCustomBindings`` and an include of our header file.

.. code:: cpp

    #include <pybind11/pybind11.h>
    #include "contrib/pyroborobo/customModuleDefinitions.h"
    #include "DistAware/include/pyroborobo/DistAwarePythonBindings.h"

    void dummyCustomBindings(pybind11::module& m)
    {

    }

    void addCustomBindings(pybind11::module &m)
    {
        /* append your custom bindings in this function
         * dummyCustomBindings is given as an exemple
         */
        dummyCustomBindings(m);
        addDistAwareBindings(m);
    }

Let's now compile pyroborobo by running

.. code:: bash

    python setup.py install --force


The class DistAwareController is now available in pyroborobo.


It is only a very simple introduction to adding bindings for pyroborobo. Writing bindings can get complex really quickly. Please read carefully the pybind11 documentation as well as the already implemented bindings. They are all in ``src/contrib/pyroborobo/moduledefinitions/``.

Using our bindings in python
----------------------------

Now that we have compiled our new ``pyroborobo`` with our custom C++ controller, we can use our new controller and our new method.

Let's write a new test in the folder ``pyRoborobo_examples`` (this folder already contains the pyroborobo data as well as default config files).


.. code:: python

    from pyroborobo import DistAwareController, Pyroborobo, PyWorldModel

    class MyCustomDistAwareController(DistAwareController):

        def __init__(self, world_model):
            # Obligatory call to super.__init__ to avoid segfault
            DistAwareController.__init__(self, world_model)
            print("Hello, I'm a custom DistAwareController")
            self.rob = Pyroborobo.get()

        def step(self):
            self.set_translation(1)
            self.set_rotation(0.01)
            nbrob = len(self.rob.robots)

            next_id = (self.id + 1) % nbrob
            dist = self.get_distance_to_robot(next_id)  # here is our new method
            print(f"I am {dist} pixel from {next_id}")


    if __name__ == "__main__":
        rob = Pyroborobo.create("config/pywander_12sensors.properties",
                                controller_class=MyCustomDistAwareController,
                                world_model_class=PyWorldModel)
        rob.start()
        rob.update(1000)
        Pyroborobo.close()


When we run this program, the distance in pixel between robots is given. We have used our c++ method in our python
program !