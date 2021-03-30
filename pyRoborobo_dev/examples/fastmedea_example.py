from pyroborobo import Pyroborobo, Controller
import numpy as np
from numba import jit
from time import perf_counter


class MedeaController(Controller):

    def __init__(self, wm):
        super().__init__(wm)
        self.weights = None
        self.received_weights = dict()
        self.rob = Pyroborobo.get()
        self.next_gen_every_it = 400
        self.deactivated = False
        self.next_gen_in_it = self.next_gen_every_it
        self._cur_inputs = None  # pre-allocate inputs to avoid too much copy
        self.distances = None
        self.distances = None
        self.is_robots = None
        self.is_walls = None
        self.is_objects = None
        self.robot_controllers = None
        self.prev_dist = np.array([0])

    def reset(self):
        if self.weights is None:
            self.weights = np.random.uniform(-1, 1, (self.nb_inputs(), 2))
        if self._cur_inputs is None:
            self._cur_inputs = np.zeros(self.nb_inputs())
        self.distances = self.get_all_distances()
        self.is_robots = self.get_all_robot_ids()  # only ref, so fast
        self.is_walls = self.get_all_walls()  # only ref, so fast
        self.is_objects = self.get_all_objects()  # only ref, so fast


    def step(self):
        self.next_gen_in_it -= 1
        if self.next_gen_in_it < 0 or self.deactivated:
            self.new_generation()
            self.next_gen_in_it = self.next_gen_every_it

        if self.deactivated:
            self.set_color(0, 0, 0)
            self.set_translation(0)
            self.set_rotation(0)
        else:
            self.set_color(0, 0, 255)
            # Share weights
            self.share_weights()

            # Movement
            inputs = self.get_inputs()
            trans_speed, rot_speed = inputs @ self.weights
            self.set_translation(min(max(-1, trans_speed), 1))  # np.clip is *slow*
            self.set_rotation(min(max(-1, rot_speed), 1))

    def nb_inputs(self):
        return (1  # bias
                + self.nb_sensors * 3  # cam inputs
                + 2  # landmark inputs
                )

    def share_weights(self):
        all_controllers = set(self.is_robots)
        for robot_id in all_controllers:
            if robot_id != -1:
                self.rob.controllers[robot_id].receive_weights(self.id, self.weights)

    def receive_weights(self, rid, weights):
        self.received_weights[rid] = (weights.copy())

    def get_inputs(self):
        landmark_dist = self.get_closest_landmark_dist()
        landmark_orient = self.get_closest_landmark_orientation()
        fast_input_generation(self._cur_inputs, self.distances, self.is_objects, self.is_robots,
                                                 self.is_walls, landmark_dist, landmark_orient)
        return self._cur_inputs

    def new_generation(self):
        if self.received_weights:
            new_weights_key = np.random.choice(list(self.received_weights.keys()))
            new_weights = self.received_weights[new_weights_key]
            # mutation
            # new_weights = np.random.normal(new_weights, 0.1   )
            self.weights = new_weights
            self.received_weights.clear()
            self.deactivated = False
        else:
            self.deactivated = True

    def inspect(self, prefix=""):
        output = "inputs: \n" + str(self.get_inputs()) + "\n\n"
        output += "received weights from: \n"
        output += str(list(self.received_weights.keys()))
        return output


@jit(nopython=True, fastmath=True)
def fast_input_generation(inputs, dists, is_objects, is_robots, is_walls, landmark_dist, landmark_orient):
    i = 0
    inputs[i] = 1
    i += 1
    for j, dist in enumerate(dists):
        inputs[i] = dist if is_robots[j] != 1 else 0
        i += 1
        inputs[i] = dist if is_walls[j] else 0
        i += 1
        inputs[i] = dist if is_objects[j] != 1 else 0
        i += 1
    inputs[i] = landmark_dist
    i += 1
    inputs[i] = landmark_orient
    i += 1
    assert (i == len(inputs))

def main():
    rob = Pyroborobo.create("config/medea.properties",
                            controller_class=MedeaController,
                            override_conf_dict={"gVerbose": "True", "gDisplayMode": "2"})
    rob.start()
    for i in range(10):
        print("start timer")
        curtime = perf_counter()
        should_quit = rob.update(1000)
        print(perf_counter() - curtime)
        if should_quit:
            break
    rob.close()


if __name__ == "__main__":
    main()
