from pyroborobo import Pyroborobo, Controller


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
        if (self.get_distance_at(1) < 1  # if we see something on our left
                or self.get_distance_at(2) < 1):  # or in front of us
            self.set_rotation(0.5)  # turn right
        elif self.get_distance_at(3) < 1:  # Otherwise, if we see something on our right
            self.set_rotation(-0.5)  # turn left



if __name__ == "__main__":
    import os
    os.makedirs("logs/screenshot_example", exist_ok=True)
    rob = Pyroborobo.create("config/simple.properties",
                            controller_class=SimpleController,
                            override_conf_dict={"gLogDirectoryname": "logs/screenshot_example"})
    rob.start()

    rob.update(100)
    rob.save_screenshot("full_screenshot_for_iter_100")

    rob.init_trajectory_monitor()  # log trajectory for all agents
    rob.update(100)
    rob.save_trajectory_image("all_agents")

    rob.init_trajectory_monitor(0)  # log the trajectory for agent with id 0
    rob.update(100)
    rob.save_trajectory_image("agent_0")

    # let's make a movie
    for i in range(100):
        rob.update(1)
        rob.save_screenshot(f"movie_iter_{i:03}")
    # Now we have 100 screen shot and can make a movie with it. Look at libraries like moviepy to create mp4
    # from these images

    rob.close()
