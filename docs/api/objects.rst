.. currentmodule:: pyroborobo

Objects
=======

SquareObject
------------

Documentation
*************

.. autoclass:: SquareObject
    :members:

Template
********

If you want to extend a SquareObject, you can start from this template:

.. code-block:: python

    class MySquareObject(SquareObject):

    def __init__(self):
        super().__init__()

    def step(self):
        super().step()

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)

    def is_touched(self, id_):
        super().is_touched(id_)

    def is_walked(self, id_):
        return super().is_walked(id_)

    def inspect(self, prefix=""):
        return f"[INFO] I'm the object #{self.id}"


CircleObject
------------

Documentation
*************

.. autoclass:: CircleObject
    :members:

Template
********

If you want to extend a CircleObject, you can start from this template:

.. code-block:: python

    class MySquareObject(SquareObject):

    def __init__(self):
        super().__init__()

    def step(self):
        super().step()

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)

    def is_touched(self, id_):
        super().is_touched(id_)

    def is_walked(self, id_):
        return super().is_walked(id_)



MovableObject
-------------

Documentation
*************

To use movable objects, do not forget to set ``gMovableObjects = true`` in your
properties file.

.. autoclass:: MovableObject
    :members:

Template
********

If you want to extend a MovableObject, you can start from this template:

.. code-block:: python

    class MyMovableObject(SquareObject):

    def __init__(self):
        super().__init__()

    def step(self):
        super().step()

    def is_pushed(self, id_, speed):
        # a call to the super method is *mandatory*
        super().is_pushed(id_, speed)

    def is_touched(self, id_):
        super().is_touched(id_)

    def is_walked(self, id_):
        return super().is_walked(id_)

    def inspect(self, prefix=""):
        return f"[INFO] I'm the object #{self.id}"


PhysicalObject
--------------

.. autoclass:: PhysicalObject
    :members:

You should *not* inherit directly from PhysicalObject.
