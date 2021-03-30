from pyroborobo import Pyroborobo, WorldObserver, SquareObject
from textwrap import dedent


class SquareObjectVerbose(SquareObject):
    def __init__(self, id=-1, data={}):
        super().__init__(id, data)

    def inspect(self, prefix=""):
        return dedent(f"""
        Square Object #{self.get_id()}

        """)


class CreateObjectWorldObserver(WorldObserver):
    def __init__(self, world):
        super().__init__(world)
        self.rob = Pyroborobo.get()

    def init_post(self):
        path = {"left": (100, 200), "bottom": (110, 290), "right": (200, 200)}
        color = {"left": (0, 0, 255), "bottom": (0, 255, 0), "right": (255, 0, 0)}
        nb = {"left": 10, "bottom": 9, "right": 10}
        for orient in ["left", "bottom", "right"]:
            for j in range(nb[orient]):
                squareobj = SquareObjectVerbose()
                squareobj = self.rob.add_object(squareobj)
                squareobj.soft_width = 0
                squareobj.soft_height = 0
                squareobj.solid_width = 10
                squareobj.solid_height = 10
                squareobj.set_color(*color[orient])
                if orient in ["left", "right"]:
                    squareobj.set_coordinates(path[orient][0], path[orient][1] + 10 * j)
                else:
                    squareobj.set_coordinates(path[orient][0] + 10 * j, path[orient][1])
                squareobj.register()
                squareobj.show()


def main():
    rob = Pyroborobo.create("config/boids.properties",
                            world_observer_class=CreateObjectWorldObserver,
                            override_conf_dict={"gInitialNumberOfRobots": "2"}
                            )
    rob.start()
    rob.update(1000)
    rob.close()


if __name__ == "__main__":
    main()
