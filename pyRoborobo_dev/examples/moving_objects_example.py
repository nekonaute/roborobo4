# DEMO 7

from pyroborobo import Pyroborobo, CircleObject, SquareObject
import copy


class SlowMoveObject(CircleObject):
    def __init__(self, id_, data):
        CircleObject.__init__(self, id_)
        self.data = data
        self.default_x = copy.copy(data["x"])
        self.default_y = copy.copy(data["y"])
        self.move_every = 100
        self.cur_it = self.move_every

    def step(self):
        self.cur_it -= 1
        if self.cur_it < 0:
            x, y = self.position
            new_x, new_y = x+20, y
            if Pyroborobo.get().iterations < 200:
                try:
                    self.radius = 100
                except RuntimeError:
                    print("[ERROR FOR THE EXAMPLE] Cannot work, object not unregistered first")

            self.unregister()
            success = self.set_coordinates(new_x, new_y)
            if not success:
                self.set_coordinates(self.default_x, self.default_y)
            self.register()
            self.cur_it = self.move_every


class UWallObject(SquareObject):
    def __init__(self, id, data):
        super().__init__(id)
        self.data = data
        self.unregister()
        if data["side"] == "left":
            self.solid_height = 100
            self.solid_width = 10
            self.soft_width = 0
            self.soft_height = 0
            self.set_coordinates(200, 300)
        elif data["side"] == "right":
            self.solid_height = 100
            self.solid_width = 10
            self.soft_width = 0
            self.soft_height = 0
            self.set_coordinates(300, 300)
        elif data["side"] == "bottom":
            self.solid_height = 10
            self.solid_width = 90
            self.soft_width = 0
            self.soft_height = 0
            self.set_coordinates(250, 345)
        self.register()

    def step(self):
        pass

    def inspect(self, prefix=""):
        return str(self.position)



def main():
    rob = Pyroborobo.create("config/moving_objects.properties",
        object_class_dict={"slowmove": SlowMoveObject, "uwall": UWallObject})
    rob.start()
    rob.update(10000)
    rob.close()


if __name__ == "__main__":
    main()
