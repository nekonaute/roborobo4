from pyroborobo import Pyroborobo, Controller, CircleObject


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
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        if (self.get_distance_at(1) < 0.8  # if we see something on our left
                or self.get_distance_at(2) < 0.8):  # or in front of us
            self.set_rotation(0.5)  # turn right
        elif self.get_distance_at(3) < 0.8:  # Otherwise, if we see something on our right
            self.set_rotation(-0.5)  # turn left
        for i in range(self.nb_sensors):
            obj = self.get_object_instance_at(i)
            if obj:
                print(obj.id)
                obj.set_color(233, 0, 0)

class SimpleDisk(CircleObject):
    def __init__(self, id = -1, data=None):
        super().__init__(-1)
        self.set_color(0, 0, 255)
        self.radius = 10
        self.footprint_radius = 20
        self.relocate()
        self.show()

    def step(self):
        pass

    def reset(self):
        self.register()

    def inspect(self, prefix):
        return f"Working as always boys, #{self.id}"

if __name__ == "__main__":
    rob = Pyroborobo.create("config/empty_arena.properties",
                            controller_class=SimpleController,
                            override_conf_dict={"gInitialNumberOfRobots": 1,
                                                "gNbOfPhysicalObjects": 1})
    rob.start()
    for i in range(100):
        quit = rob.update(100)
        obj = rob.add_object(SimpleDisk())
        if quit: break
    rob.close()
