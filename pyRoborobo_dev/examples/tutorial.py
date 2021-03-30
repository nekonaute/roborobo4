from pyroborobo import Pyroborobo, Controller
import numpy as np


class TutorialController(Controller):
    robot_index_offset = 1048576

    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        self.rob = Pyroborobo.get()
        print("I'm a Python controller")

    def reset(self):
        print("I'm initialised")

    def step(self):  # step is called at each time step
        # Simple avoidance
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        camera_dist = self.get_all_distances()
        if (camera_dist[1] < 1  # if we see something on our right
                or camera_dist[2] < 1):  # or in front of us
            self.set_rotation(1)  # turn left
        elif camera_dist[3] < 1:  # Otherwise, if we see something on our left
            self.set_rotation(-1)  # turn right
        # now let's get talkative
        if self.id == 0:
            print(f"I am {self}, {self.id}, at position {self.absolute_position} and orientation {self.absolute_orientation}")
            for i in range(self.nb_sensors):
                print(f"Sensor {i}:")
                print(f"\tdist: {self.get_distance_at(i)}")
                print(f"\tis object: {self.get_object_at(i) != -1}")
                print(f"\tis_wall: {self.get_wall_at(i)}")
                print(f"\tis robot: {self.get_robot_id_at(i) != -1}")
                is_robot = self.get_robot_id_at(i) != -1
                is_wall = self.get_wall_at(i)
                if is_robot:
                    robid = self.get_robot_id_at(i)
                    print(f"\trobot id: {robid}")
                    print(f"\trobot's controller: {self.get_robot_controller_at(i)}")
                    ctl = self.get_robot_controller_at(i)
                    print(f"\tThis robot is at {ctl.absolute_position} with orientation {ctl.absolute_orientation}.")
                elif self.get_object_at(i) != -1:  # then it's an object
                    print(f"\tphysical object instance: {self.get_object_instance_at(i)}")


if __name__ == "__main__":
    rob = Pyroborobo.create("config/simple.properties",
                            controller_class=TutorialController)
    rob.start()
    rob.update(10000)
    rob.close()
