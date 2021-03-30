from pyroborobo import Pyroborobo, Controller
from pyroborobo import SquareObject, CircleObject, Pyroborobo


class SwitchObject(CircleObject):
    def __init__(self, id, data):
        CircleObject.__init__(self, id)  # Do not forget to call super constructor
        self.regrow_time = data['regrowTimeMax']
        self.cur_regrow = 0
        self.triggered = False
        self.gate_id = data['sendMessageTo']
        self.rob = Pyroborobo.get()  # Get pyroborobo singleton

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False

    def is_walked(self, rob_id):
        self.triggered = True
        self.rob.objects[self.gate_id].open()
        self.cur_regrow = self.regrow_time
        self.hide()
        self.unregister()

    def inspect(self, prefix=""):
        return "I'm a switch!"


class GateObject(SquareObject):
    def __init__(self, id, data):
        SquareObject.__init__(self, id)
        self.triggered = False
        self.regrow_time = data['regrowTimeMax']
        self.cur_regrow = 0

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False

    def open(self):
        self.triggered = True
        self.hide()
        self.unregister()
        self.cur_regrow = self.regrow_time

    def inspect(self, prefix=""):
        return "I'm a gate!"


class ResourceObject(CircleObject):
    def __init__(self, id_, data):
        CircleObject.__init__(self, id_)  # Do not forget to call super constructor
        self.regrow_time = 100
        self.cur_regrow = 0
        self.triggered = False
        self.rob = Pyroborobo.get()  # Get pyroborobo singleton

    def reset(self):
        self.show()
        self.register()
        self.triggered = False
        self.cur_regrow = 0

    def step(self):
        if self.triggered:
            self.cur_regrow -= 1
            if self.cur_regrow <= 0:
                self.show()
                self.register()
                self.triggered = False


    def is_walked(self, rob_id):
        self.triggered = True
        self.cur_regrow = self.regrow_time
        self.hide()
        self.unregister()

    def inspect(self, prefix=""):
        return f"""I'm a ResourceObject with id: {self.id}"""


class HungryController(Controller):

    def __init__(self, wm):
        super().__init__(wm)
        self.rob = Pyroborobo.get()
        assert self.nb_sensors == 8, "SimpleController only works with 8 sensors"
        self.rotspeed = 0.5

    def reset(self):
        pass

    def step(self):
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)

        must_flee: bool = False  # have we encountered a wall and must prioritise avoiding obstacle

        if self.get_distance_at(1) < 1:  # if we see something on our right
            if self.get_object_at(1) != -1:  # And it is food
                self.set_rotation(-self.rotspeed)  # GO TOWARD IT
            else:
                self.set_rotation(self.rotspeed)  # flee it
                must_flee = True
        elif self.get_distance_at(2) < 1:  # if we see something in front of us
            if self.get_object_at(2) != -1 and not must_flee:  # If we are not avoiding obstacle and it's food
                self.set_rotation(0)
            else:
                self.set_rotation(self.rotspeed)  # turn left
                must_flee = True
        elif self.get_distance_at(3) < 1:  # Otherwise, if we see something on our right
            if self.get_object_at(3) != -1 and not must_flee:
                self.set_rotation(self.rotspeed)  # turn left
            else:
                self.set_rotation(-self.rotspeed)
                must_flee = True

    def inspect(self, prefix):
        output = ""
        for i in range(self.nb_sensors):
            output += f"""sensor {i}:
    dist: {self.get_distance_at(i)}
    id: {self.world_model.camera_objects_ids[i]}
    nbobjs: {len(self.rob.objects)}
    is_object: {self.get_object_at(i)}
    is_robot: {self.get_robot_id_at(i)}
    is_wall: {self.get_wall_at(i)}\n\n"""
        return output


if __name__ == "__main__":
    rob = Pyroborobo.create("config/pywander_pyobj_resource.properties",
                            controller_class=HungryController,
                            object_class_dict={'_default': ResourceObject, 'gate': GateObject, 'switch': SwitchObject})
    rob.start()
    rob.update(10000)
    rob.close()
