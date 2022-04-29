# Nicolas
# 2021-03-13

from pyroborobo import Pyroborobo, Controller, AgentObserver, WorldObserver, CircleObject, SquareObject, MovableObject
#from custom.controllers import SimpleController, HungryController
import numpy as np
import random

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

rob = 0

score = 0
malus = 0
bonus = 0
superpacman = False
supercountdown = 0
supercountdownMax = 1000

offset_x = 40
offset_y = 32
edge_width = 36
edge_height = 28


class MyController(Controller):

    def __init__(self, wm):
        super().__init__(wm)
        #Controller.__init__(self, wm) identique à la ligne précédente?
        assert self.nb_sensors == 8, "SimpleController only works with 8 sensors"
        self.agents_met = set()

    def reset(self):
        return

    def step(self):
        global malus,bonus,score,superpacman
        #global rob

        # move around
        self.set_translation(1)  # Let's go forward
        self.set_rotation(0)
        # Now, our world_model object is a PyWorldModel, we can have access to camera_* properties
        if (self.get_distance_at(1) < 1  # if we see something on our left
                or self.get_distance_at(2) < 1):  # or in front of us
            self.set_rotation(0.5)  # turn right
        elif self.get_distance_at(3) < 1:  # Otherwise, if we see something on our right
            self.set_rotation(-0.5)  # turn left


        if self.id != 0: # note that if robot #0 is remote-controlled, step will not be called.
            isPlayerTouched = False
            for i in range(self.nb_sensors):
                if self.get_robot_id_at(i) == 0:
                    isPlayerTouched = True
                    break
            if superpacman == True:
                self.set_color(0,0,255)
                if isPlayerTouched == True:
                    x = offset_x + 10 * edge_width
                    y = offset_y + 12 * edge_height + edge_height / 2
                    success = self.set_position(x, y)
                    bonus = bonus + 1
                    print("Pacman ate ghost",self.id,"!")
                    print("score:", score, "-- malus:", malus, "-- bonus:", bonus)
            else:
                self.set_color(255, 0, 0)
                if isPlayerTouched == True:
                    malus = malus - 1
                    print("score:", score, "-- malus:", malus, "-- bonus:", bonus)

        # track meetings
        '''
        for i in range(self.nb_sensors):
            rob = self.get_robot_id_at(i)
            if rob > 0:
                self.agents_met.add(rob)
                #self.get_robot_instance_at(rob)
                robId = self.get_robot_id_at(i)
                robCtl = self.get_robot_controller_at(i)
        '''
        # how to access others
        #controllers = rob.controllers
        #for c in controllers: # costly!
        #    c.check()
        #print(rob.iterations) # marche pas.

    def check(self):
        #print (self.id)
        return True

    def inspect(self, prefix=""):
        return f"[INFO] robot #{self.id} met {len(self.agents_met)} robots.\n" \
               f"[INFO]   => {self.agents_met}.\n"

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class MyAgentObserver(AgentObserver):
    def __init__(self, wm):
        super().__init__(wm)
        self.arena_size = Pyroborobo.get().arena_size

    def reset(self):
        super().reset()
        return

    def step_pre(self):
        super().step_pre()
        return

    def step_post(self):
        super().step_post()
        margin = 32
        x, y = self.controller.absolute_position
        if x < margin:
            success = self.controller.set_position(self.arena_size[0] - margin - 2, y)
#            if success == false: ... ca peut arriver...
        elif x > self.arena_size[0] - margin:
            success = self.controller.set_position(margin + 2, y)
        return


# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class MyWorldObserver(WorldObserver):
    def __init__(self, world):
        super().__init__(world)
        self.rob = Pyroborobo.get()

    def init_pre(self):
        super().init_pre()
        #BlockObject(SquareObject):

    def init_post(self):
        global offset_x, offset_y, edge_width, edge_height

        super().init_post()

        maze = [ # 201 dots, 4 power pellets
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1],
            [1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1],
            [1, 3, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 3, 1],
            [1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1],
            [1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1],
            [1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1],
            [1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1],
            [1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1],
            [1, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 2, 1, 0, 1, 1, 0, 1, 1, 0, 1, 2, 1, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 2, 1, 0, 1, 0, 0, 0, 1, 0, 1, 2, 1, 1, 1, 1, 1],
            [2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 0, 0, 1, 0, 2, 2, 2, 2, 2, 2, 2],
            [1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1],
            [1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1],
            [1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1],
            [1, 3, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 3, 1],
            [1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1],
            [1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1],
            [1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1],
            [1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1],
            [1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        ]

        for i in range(len(maze)):
            for j in range(len(maze[0])):
                if maze[i][j] == 1:
                    squareobj = SquareObject()
                    squareobj = self.rob.add_object(squareobj)
                    squareobj.soft_width = 0
                    squareobj.soft_height = 0
                    squareobj.solid_width = edge_width
                    squareobj.solid_height = edge_height
                    squareobj.set_color(164,128,0)
                    squareobj.set_coordinates(offset_x+j*edge_width,offset_y+i*edge_height)
                    #print ("i,j=",i,j)
                    squareobj.register()
                    squareobj.show()
                elif maze[i][j] == 2 or maze[i][j] == 3:
                    gum = PacgumObject()
                    gum = self.rob.add_object(gum)
                    if maze[i][j] == 2:
                        gum.set_color(192, 200, 0)
                        gum.set_type("dot")
                        gum.radius = 0
                        gum.footprint_radius = 8
                    else:
                        gum.set_color(255, 255, 0)
                        gum.set_type("Power Pellet")
                        gum.radius = 0
                        gum.footprint_radius = 12
                    gum.set_coordinates(offset_x+j*edge_width,offset_y+i*edge_height)
                    retValue = gum.can_register()
                    #print("Register gum:", retValue)
                    gum.register()
                    gum.show()

        first = True
        for robot in self.rob.controllers:
            if first: #robot.robot.getId() == 0:
                x = offset_x + 10*edge_width
                y = offset_y + 23*edge_height + edge_height/2
                robot.set_position( x, y )
                robot.set_absolute_orientation(-90)
                first = False
            else:
                x = offset_x + 10*edge_width
                y = offset_y + 12*edge_height + edge_height/2
                robot.set_position( x, y )

        # BLOC::BETA
        '''
        ball = BallObject(3,{}) # comment faire pour ne pas spécifier le numéro d'objet à la main? idéalement: ball = BallObject(
        ball = self.rob.add_object(ball)
        ball.set_color(192,128,0) # ne fait rien
        ball.radius = 16
        ball.footprint_radius = 0
        ball.set_coordinates(500,400)
        retValue = ball.can_register()
        print ("Register Movable:", retValue)
        ball.register()
        ball.show()
        '''

    def step_pre(self):
        super().step_pre()
        #pyrob = Pyroborobo.get()
        #if pyrob.iterations == 0:
        #    print ("ZERO")

    def step_post(self):
        global superpacman, supercountdown, supercountdownMax

        super().step_post()
        #for ctlrob in self.rob.controllers:
        #    print(ctlrob.inspect())

        if superpacman == True:
            supercountdown = supercountdown - 1
            if supercountdown % 100 == 0:
                print("Pacman is SUPER-POWERED! Remaining time:",supercountdown)
                if supercountdown == 0:
                    superpacman = False
                    supercountdown = supercountdownMax
                    print ("Pacman is powerless now.")



# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class PacgumObject(CircleObject):

    def __init__(self, id=-1, data={}):
        super().__init__(id, data)

    def step(self):
        return

    def is_walked(self,id):
        global score,malus,bonus,superpacman,supercountdown,supercountdownMax
        #print("touched by",id)
        if id == 0:
            if self.type == "dot":
                self.unregister()
                self.hide()
                score = score + 1
                print("score:", score, "-- malus:", malus,"-- bonus:", bonus)
            elif self.type == "Power Pellet":
                self.unregister()
                self.hide()
                superpacman = True
                supercountdown = supercountdownMax
                print("Pacman ate a Power Pellet!")
        return

    def set_type(self,type):
        self.type = type


# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class BallObject(MovableObject): # repris exactement de l'exemple ball_example.py

    def __init__(self, id_, data): # la doc dit: def __init__(self): --- pourquoi c'est différent?
        MovableObject.__init__(self, id_)
        self.data = data

    def step(self):
        super().step()
        if np.random.random() < 0.001:
            self.hide()
            self.relocate()
            self.show()

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)
        print(f"I'm kicked by {id_}")

    def inspect(self, prefix):
        return f"[INSPECT] Ball #{self.id}\n"


# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


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

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)

    def is_touched(self, id_):
        super().is_touched(id_)

    def inspect(self, prefix=""):
        return "I'm a switch!"

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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
            if self.cur_regrow <= 0 and self.can_register():
                self.show()
                self.register()
                self.triggered = False

    def is_pushed(self, id_, speed):
        super().is_pushed(id_, speed)

    def is_touched(self, id_):
        super().is_touched(id_)

    def is_walked(self, id_):
        return super().is_walked(id_)

    def open(self):
        self.triggered = True
        self.hide()
        self.unregister()
        self.cur_regrow = self.regrow_time

    def inspect(self, prefix=""):
        return "I'm a gate!"

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class BlockObject(SquareObject):
    def __init__(self, id, data):
        super().__init__(id)
        self.data = data
        self.unregister()

    def create(self,x,y):
        self.solid_height = 16
        self.solid_width = 16
        self.soft_width = 0
        self.soft_height = 0
        self.set_coordinates(x, y)
        self.register()

# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

def main():
    global rob

    rob = Pyroborobo.create(
        "config/pacman.properties",
        controller_class=MyController,
        world_observer_class=MyWorldObserver,
#        world_model_class=PyWorldModel,
        agent_observer_class=MyAgentObserver,
        object_class_dict={'gate': GateObject, 'switch': SwitchObject, 'ball': BallObject}
        #,override_conf_dict={"gNbOfInitialRobots": 30} # NOT IMPLEMENTED
    )
    rob.start()
    rob.update(30000)
    rob.close()

if __name__ == "__main__":
    main()