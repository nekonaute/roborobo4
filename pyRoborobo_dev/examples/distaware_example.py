from pyroborobo import DistAwareController, Pyroborobo


class MyCustomDistAwareController(DistAwareController):

    def __init__(self, world_model):
        # Obligatory call to super.__init__ to avoid segfault
        DistAwareController.__init__(self, world_model)
        print("Hello, I'm a custom DistAwareController")
        self.rob = Pyroborobo.get()

    def step(self):
        self.set_translation(1)
        self.set_rotation(0.01)
        nbrob = len(self.rob.controllers)

        next_id = (self.id + 1) % nbrob
        dist = self.get_distance_to_robot(next_id)
        print(f"I am {dist} pixel from {next_id}")


if __name__ == "__main__":
    rob = Pyroborobo.create("config/pywander_12sensors.properties",
                            controller_class=MyCustomDistAwareController)
    rob.start()
    rob.update(1000)
    rob.close()
