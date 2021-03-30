.. currentmodule:: pyroborobo

WorldObserver
=============

Documentation
-------------

.. autoclass:: WorldObserver
    :members:

Template
--------

If you want to extend a WorldObserver, you can use this template:

.. code-block:: python

    class MyWorldObserver(WorldObserver):
        def __init__(self, world):
            super().__init__(world)

        def init_pre(self):
            super().init_pre()

        def init_post(self):
            super().init_post()

        def step_post(self):
            super().step_post()

        def step_pre(self):
            super().step_pre()
