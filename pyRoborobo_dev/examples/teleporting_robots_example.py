# DEMO 8

from pyroborobo import Pyroborobo, Controller
import numpy as np
import pyroborobo


class TeleportingController(Controller):

    def __init__(self, wm):
        super().__init__(wm)
        self.arena_size = Pyroborobo.get().arena_size

    def reset(self):
        pass

    def step(self):
        x, y = self.absolute_position
        success = True
        if x < 20:
            success = self.set_position(self.arena_size[0] - 2*x, y)
            # handle the registration by yourself
            # self.robot.unregister()
            # success = self.robot.set_position(self.arena_size[0] - 2 * x, y, register=False)
            # self.robot.register()
            # Force position even if collision:
            # success = self.robot.set_position(self.arena_size[0] - 2 * x, y, force=True)
        elif x > self.arena_size[0] - 20:
            new_x = self.arena_size[0]-x
            success = self.set_position(2 * new_x, y)
        if not success:
            print(self.id, "cannot be teleported. Something is in the way.")
        self.set_translation(1)
        self.set_rotation(np.clip(np.random.normal(0, 0.5), -1, 1))


def main():
    print(pyroborobo.__file__)

    pyrob = Pyroborobo.create("config/boids.properties",
                              controller_class=TeleportingController,
                              override_conf_dict={"gInitialNumberOfRobots": "2"})
    pyrob.start()
    pyrob.update(1000)
    pyrob.close()


if __name__ == "__main__":
    main()
