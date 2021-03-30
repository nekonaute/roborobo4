from pyroborobo import Pyroborobo, Controller
import numpy as np

class MedeaController(Controller):

    def __init__(self, wm):
        super().__init__(wm)
        self.weights = None
        self.received_weights = dict()
        self.rob = Pyroborobo.get()
        self.next_gen_every_it = 400
        self.deactivated = False
        self.next_gen_in_it = self.next_gen_every_it

    def reset(self):
        if self.weights is None:
            self.weights = np.random.uniform(-1, 1, (self.nb_inputs(), 2))

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
            # Movement
            inputs = self.get_inputs()
            trans_speed, rot_speed = inputs @ self.weights
            self.set_translation(np.clip(trans_speed, -1, 1))
            self.set_rotation(np.clip(rot_speed, -1, 1))
            # Share weights
            self.share_weights()

    def nb_inputs(self):
        return (1  # bias
                + self.nb_sensors * 3  # cam inputs
                + 2  # landmark inputs
                )

    def share_weights(self):
        for robot_controller in self.get_all_robot_controllers():
            if robot_controller:
                robot_controller.receive_weights(self.id, self.weights)

    def receive_weights(self, rid, weights):
        self.received_weights[rid] = (weights.copy())

    def get_inputs(self):
        dists = self.get_all_distances()
        is_robots = self.get_all_robot_ids() != -1
        is_walls = self.get_all_walls()
        is_objects = self.get_all_objects() != -1

        robots_dist = np.where(is_robots, dists, 1)
        walls_dist = np.where(is_walls, dists, 1)
        objects_dist = np.where(is_objects, dists, 1)

        landmark_dist = self.get_closest_landmark_dist()
        landmark_orient = self.get_closest_landmark_orientation()

        inputs = np.concatenate([[1], robots_dist, walls_dist, objects_dist, [landmark_dist, landmark_orient]])
        assert(len(inputs) == self.nb_inputs())
        return inputs

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

def main():
    rob = Pyroborobo.create("config/medea.properties",
                            controller_class=MedeaController)
    rob.start()
    rob.update(10000)
    rob.close()


if __name__ == "__main__":
    main()
