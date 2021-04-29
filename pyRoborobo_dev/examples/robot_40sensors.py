from pyroborobo import Pyroborobo, Controller, WorldObserver, SquareObject, MovableObject
import numpy as np
import random

simulation_mode_at_startup = 0

# 8=>16 senseurs
# nommer les senseurs
# coder l'évitement des murs

def principal_value(deg):
    deg_mod = np.mod(deg, 360)
    if deg_mod > 180:
        return deg_mod - 360
    else:
        return deg_mod

def angle_diff(x, y):
    return principal_value(x - y)

class BoidsController(Controller):

    def __init__(self, world_model):
        # It is *mandatory* to call the super constructor before any other operation to
        # link the python object to its C++ counterpart
        Controller.__init__(self, world_model)
        self.rob = Pyroborobo.get()
        self.camera_max_range = 0
        self.repulse_radius = 0
        self.orientation_radius = 0

    def reset(self):
        self.repulse_radius = 0.2
        self.orientation_radius = 0.6

    def step(self):  # step is called at each time step
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        camera_dist = self.get_all_distances()
        camera_id = self.get_all_robot_ids()
        camera_angle_rad = self.get_all_sensor_angles()
        camera_angle = camera_angle_rad * 180 / np.pi
        own_orientation = self.absolute_orientation
        for i in np.argsort(camera_dist):  # get the index from the closest to the farthest
            if camera_angle[i] < -270 or camera_angle[i] > 270:
                continue
            else:
                dist = camera_dist[i]
                if dist < self.repulse_radius:
                    if camera_angle[i] != 0:
                        self.set_rotation(-camera_angle_rad[i] / np.pi)
                    else:
                        self.set_rotation(1)
                elif dist < self.orientation_radius and camera_id[i] != -1:
                    orient_angle = self.get_robot_relative_orientation_at(i)
                    self.set_rotation(orient_angle / np.pi)
                elif dist < self.camera_max_range and camera_id[i] != -1:
                    self.set_rotation(camera_angle_rad[i] / np.pi)
                break  # stop


# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class MyWorldObserver(WorldObserver):
    def __init__(self, world):
        super().__init__(world)
        rob = Pyroborobo.get()

    def init_pre(self):
        super().init_pre()

    def init_post(self):
        super().init_post()

        '''
        for x in range(2,799,4):
            for y in {2,798}:
                block = BlockObject()
                block = rob.add_object(block)
                block.soft_width = 0
                block.soft_height = 0
                block.solid_width = 4
                block.solid_height = 4
                block.set_color(164, 128, 0)
                block.set_coordinates(x,y)
                # print ("i,j=",i,j)
                retValue = block.can_register()
                # print("Register block (",block.get_id(),") :", retValue)
                block.register()
                block.show()
        for x in {2,798}:
            for y in range(2+4,795,4):
                block = BlockObject()
                block = rob.add_object(block)
                block.soft_width = 0
                block.soft_height = 0
                block.solid_width = 4
                block.solid_height = 4
                block.set_color(164, 128, 0)
                block.set_coordinates(x,y)
                # print ("i,j=",i,j)
                retValue = block.can_register()
                # print("Register block (",block.get_id(),") :", retValue)
                block.register()
                block.show()
        '''

        '''
        # ball
        ball = BallObject()
        ball = rob.add_object(ball)
        #ball.unregister()
        ball.set_color(192,128,0) # ne fait rien
        ball.radius = 16
        ball.footprint_radius = 0
        #ball.set_coordinates(50,50)
        #ball.set_coordinates(750, 799)
        ball.set_coordinates(110, 120)
        retValue = ball.can_register()
        ball.register()
        ball.show()
        '''

        for i in range(4): #1521):
            rob.add_robot()

        x, y = 20, 20
        delta_X, delta_Y = 20, 20
        #delta_X, delta_Y = 50, 50
        for robot in rob.controllers:
            robot.set_absolute_orientation(random.randint(-180,180))
            robot.set_position(x, y)
            x = x + delta_X
            if x > 780:
                x = 20
                y += delta_Y
            # 2021-04-27 BP -- il faut créer les robots directements en python sinon ils doivent trouver un place au hasard avant


        for i in {0,1}:
            block = BlockObject()
            block = rob.add_object(block)
            block.soft_width = 0
            block.soft_height = 0
            block.solid_width = 200
            block.solid_height = 200
            block.set_color(120, 32, 20)
            block.set_coordinates(200+i*400, 400)
            retValue = block.can_register()
            print("Register block (",block.get_id(),") :", retValue)
            block.register()
            block.show()

        print("End of worldobserver::init_post")

    def step_pre(self):
        super().step_pre()

    def step_post(self):
        super().step_post()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class BlockObject(SquareObject):
    def __init__(self, id=-1, data={}):
        super().__init__(id, data)

    def step(self):
        # self.unregister()
        # self.register()
        # self.show()
        return

    def is_walked(self, id_):
        return

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class BallObject(MovableObject): # repris exactement de l'exemple ball_example.py

    def __init__(self, id_=-1, data={}): # la doc dit: def __init__(self): --- pourquoi c'est différent?
        MovableObject.__init__(self, id_)
        self.data = data

    def step(self):
        super().step()
        if np.random.random() < 0.001*0.0001:
            self.hide()
            self.relocate()
            self.show()

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)
        #print(f"I'm kicked by {id_}")

    def inspect(self, prefix):
        return f"[INSPECT] Ball #{self.id}\n"

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

if __name__ == "__main__":

    rob = Pyroborobo.create("config/robot_40sensors.properties",
                            controller_class=BoidsController,
                            world_observer_class=MyWorldObserver,
                            #agent_observer_class=MyAgentObserver,
                            object_class_dict={},
                            override_conf_dict={"gDisplayMode": simulation_mode_at_startup, "gRobotDisplayFocus": True}
                            )
    rob.start()
    rob.update(100000)
    rob.close()
