# Demo 3
# each agent count the unique partners they met

from pyroborobo import Pyroborobo, Controller, WorldObserver


class SimpleController(Controller):


    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        assert self.nb_sensors == 8, "SimpleController only works with 8 sensors"
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")

    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        if (self.get_distance_at(1) < 1  # if we see something on our left
                or self.get_distance_at(2) < 1):  # or in front of us
            self.set_rotation(0.5)  # turn right
        elif self.get_distance_at(3) < 1:  # Otherwise, if we see something on our right
            self.set_rotation(-0.5)  # turn left



class CounterController(SimpleController):
    def __init__(self, wm):
        super().__init__(wm)
        self.agents_met = set()

    def step(self):
        super().step()
        for i in range(self.nb_sensors):
            rob = self.get_robot_id_at(i)
            if rob > 0:
                self.agents_met.add(rob)

    def inspect(self, prefix=""):
        return f"I'm {self.id}, and I met {len(self.agents_met)}.\n" \
               f"They are {self.agents_met}.\n"


class CounterWorldObserver(WorldObserver):
    def __init__(self, world):
        super().__init__(world)
        self.rob = Pyroborobo.get()

    def step_post(self):
        super().step_pre()
        for ctlrob in self.rob.controllers:
            print(ctlrob.inspect())


def main():
    rob = Pyroborobo.create(
        "config/unique_meet.properties",
        controller_class=CounterController,
        world_observer_class=CounterWorldObserver,
        override_conf_dict={"gInitialNumberOfRobots": 30}
    )
    rob.start()
    rob.update(3000)
    rob.close()

if __name__ == "__main__":
    main()