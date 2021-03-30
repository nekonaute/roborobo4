from pyroborobo import Pyroborobo, Controller
import numpy as np

class GatherController(Controller):

    def __init__(self, world_model):
        self.rot_speed = 0.5
        # It is *mandatory* to call the super constructor before any other operation to
        # link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        self.rob = Pyroborobo.get()
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")

    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        camera_dist = self.get_all_distances()
        camera_rob_id = self.get_all_robot_ids()
        if camera_dist[1] < 1:  # if we see something on our right
            if camera_rob_id[1] != -1:  # and it's a robot
                self.set_rotation(-self.rot_speed)  # go hug it
            else:  # if it's an object
                self.set_rotation(self.rot_speed)  # turn left
        elif camera_dist[2] < 1:  # or in front of us
            if camera_rob_id[2] != -1:  # and it's a robot
                self.set_rotation(0)  # go hug it
            else:  # if object
                self.set_rotation(self.rot_speed)  # avoid it
        elif camera_dist[3] < 1:  # Otherwise, if we see something on our left
            if camera_rob_id[3] != -1:  # and it's a robot
                self.set_rotation(self.rot_speed)  # go hug the robot
            else:
                self.set_rotation(-self.rot_speed)  # avoid it (turn right)


if __name__ == "__main__":
    rob = Pyroborobo.create("config/simple.properties",
                            controller_class=GatherController)
    rob.start()
    rob.update(10000)
    rob.close()
