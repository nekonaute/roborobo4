from pyroborobo import Pyroborobo, Controller, WorldObserver
import numpy as np


class LandmarkWorldObserver(WorldObserver):
    def __init__(self, world):
        super().__init__(world)
        self.rob = Pyroborobo.get()


    def init_post(self):
        arena_size = np.asarray(self.rob.arena_size)
        landmark = self.rob.add_landmark()
        landmark.radius = 20
        landmark.set_coordinates(*(arena_size//2))
        landmark.show()
        self.move_landmarks()

    def step_pre(self, *args, **kwargs):
        if (self.rob.iterations + 1) % 400 == 0:
            # The first one blinks
            if self.rob.landmarks[-1].visible:
                self.rob.landmarks[-1].hide()
            else:
                self.rob.landmarks[-1].show()
            # the others move
            self.move_landmarks()

    def move_landmarks(self):
        arena_size = np.asarray(self.rob.arena_size)
        for landmark in self.rob.landmarks[:-1]:  # Only the last landmarks
            lbound = np.array([landmark.radius + 8] * 2)
            ubound = arena_size - (landmark.radius + 8)
            x, y = np.random.randint(lbound, ubound)
            landmark.hide()
            landmark.set_coordinates(x, y)
            landmark.show()

class GoToClosestLandMarkController(Controller):
    def __init__(self, wm):
        super().__init__(wm)

    def reset(self):
        pass

    def step(self):
        orient = self.get_closest_landmark_orientation()
        self.set_rotation(np.clip(orient, -1, 1))
        self.set_translation(1)



def main():
    rob = Pyroborobo.create("config/landmarks.properties",
                            world_observer_class=LandmarkWorldObserver,
                      controller_class=GoToClosestLandMarkController)
    rob.start()
    for i in range(10):
        must_quit = rob.update(400)
        if must_quit:
            break
    rob.close()


if __name__ == "__main__":
    main()
