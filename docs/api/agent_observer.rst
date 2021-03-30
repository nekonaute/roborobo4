.. currentmodule:: pyroborobo

AgentObserver
=============

Documentation
-------------

.. autoclass:: AgentObserver
    :members:

Template
--------

If you want to override an AgentObserver, you can use this template:

.. code-block:: python

    class MyAgentObserver(AgentObserver):
        def __init__(self, wm):
            super().__init__(wm)

        def reset(self):
            super().reset()

        def step_post(self):
            super().step_post()

        def step_pre(self):
            return super().step_pre()

