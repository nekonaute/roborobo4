# Test me by running `SDL_VIDEODRIVER=dummy python simple_batchmode_example.py`

from pyroborobo import Pyroborobo, Controller, AgentObserver
from csv import DictWriter
import gzip

class SimpleController(Controller):
    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        assert self.nb_sensors == 8, "SimpleController only works with 8 sensors"
        self.writer = None

    def reset(self):
        print("I'm initialised")

    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        if (self.get_distance_at(1) < 1  # if we see something on our left
                or self.get_distance_at(2) < 1):  # or in front of us
            self.set_rotation(0.5)  # turn right
        elif self.get_distance_at(3) < 1:  # Otherwise, if we see something on our right
            self.set_rotation(-0.5)  # turn left


class LogAgentObserver(AgentObserver):
    def __init__(self, wm):
        super().__init__(wm)
        self.writer = None
        self.rob = Pyroborobo.get()

    def reset(self):
        pass

    def receive_writer(self, writer):
        self.writer = writer

    def step_post(self):
        if self.writer:
            writer.writerow({"it": self.rob.iterations,
                             "id": self.controller.id,
                             "x": self.controller.absolute_position[0],
                             "y": self.controller.absolute_position[1]})

if __name__ == "__main__":
    import os
    rob = Pyroborobo.create("config/pywander.properties",
                            controller_class=SimpleController,
                            agent_observer_class=LogAgentObserver,
                            override_conf_dict={"gBatchMode": True, "gDisplayMode": 2})
    rob.start()
    sdl_driver = os.getenv("SDL_VIDEODRIVER")
    if sdl_driver != "dummy":
        print("WARNING: You should set SDL_VIDEODRIVER=dummy to run me on a cluster")
        print("SDL_VIDEODRIVER=dummy python simple_batchmode_example.py")
    with open("logs/simple_pos_log.txt", "w") as f:
        writer = DictWriter(f, ["it", "id", "x", "y"])
        writer.writeheader()
        for agobs in rob.agent_observers:
            agobs.receive_writer(writer)
        rob.update(1000)
    # and now with a gzip file
    with gzip.open("logs/simple_pos_log2.txt.gz", "wt") as f:  # write a gzip file in text mode, see doc of gzip
        writer = DictWriter(f, ["it", "id", "x", "y"])
        writer.writeheader()
        for agobs in rob.agent_observers:
            agobs.receive_writer(writer)
        rob.update(1000)
    rob.close()
