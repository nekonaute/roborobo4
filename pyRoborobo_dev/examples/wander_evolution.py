from pyroborobo import Pyroborobo, Controller, AgentObserver
import numpy as np
try:
    from scipy.stats import rankdata
except ImportError:
    print("This example need scipy as a dependancy. please install scipy with conda or pip")
    import sys
    sys.exit(-1)

from custom.objects import SwitchObject, GateObject


def evaluate_network(input_, network):
    out = np.concatenate([[1], input_])
    for elem in network[:-1]:
        out = np.tanh(out @ elem)
    out = out @ network[-1]  # linear output for last layer
    return out


class EvolController(Controller):

    def __init__(self, wm):
        Controller.__init__(self, wm)
        self.nb_hiddens = 10
        self.weights = [np.random.normal(0, 1, (self.nb_sensors + 1, self.nb_hiddens)),
                        np.random.normal(0, 1, (self.nb_hiddens, 2))]
        self.tot_weights = np.sum([np.prod(layer.shape) for layer in self.weights])

    def reset(self):
        pass

    def step(self):
        input = self.get_all_distances()
        out = np.clip(evaluate_network(input, self.weights), -1, 1)
        self.set_translation(out[0])
        self.set_rotation(out[1])

    def get_flat_weights(self):
        all_layers = []
        for layer in self.weights:
            all_layers.append(layer.reshape(-1))
        flat_layers = np.concatenate(all_layers)
        assert (flat_layers.shape == (self.tot_weights,))
        return flat_layers

    def set_weights(self, weights):
        j = 0
        for i, elem in enumerate(self.weights):
            shape = elem.shape
            size = elem.size
            self.weights[i] = np.array(weights[j:(j + size)]).reshape(shape)
            j += size
        # assert that we have consume all the weights needed
        assert (j == self.tot_weights)
        assert (j == len(weights))


class EvolObserver(AgentObserver):

    def __init__(self, wm):
        super().__init__(wm)
        self.fitness = 0

    def reset(self):
        self.fitness = 0

    def step_post(self):
        speed = self.controller.translation
        rotspeed = np.abs(self.controller.rotation)
        dists = np.asarray(self.controller.get_all_distances())
        fitdelta = 5 * speed + np.min(dists) + 4 * np.exp(-10 * rotspeed)
        if np.random.rand() < 0.0001:
            print(speed, rotspeed, dists)
            print(fitdelta)
        self.fitness += fitdelta


def get_weights(rob: Pyroborobo):
    weights = []
    for ctl in rob.controllers:
        weights.append(ctl.get_flat_weights())
    return weights


def get_fitnesses(rob: Pyroborobo):
    fitnesses = []
    for observer in rob.agent_observers:
        fitnesses.append(observer.fitness)
    return fitnesses


def fitprop(weights, fitnesses):
    adjust_fit = rankdata(fitnesses)
    # adjust_fit = np.clip(fitnesses, 0.00001, None)
    normfit = adjust_fit / np.sum(adjust_fit)
    # select
    new_weights_i = np.random.choice(len(weights), len(weights), replace=True, p=normfit)
    new_weights = np.asarray(weights)[new_weights_i]
    # mutate
    new_weights_mutate = np.random.normal(new_weights, 0.01)
    return new_weights_mutate


def apply_weights(rob, weights):
    for ctl, weight in zip(rob.controllers, weights):
        ctl.set_weights(weight)


def reset_agent_observers(rob):
    for obs in rob.agent_observers:
        obs.reset()


def main():
    nbgen = 10000
    nbiterpergen = 400
    rob: Pyroborobo = Pyroborobo.create(
        "config/pywander_pyobj.properties",
        controller_class=EvolController,
        agent_observer_class=EvolObserver,
        object_class_dict={'gate': GateObject, 'switch': SwitchObject}
    )

    rob.start()
    for igen in range(nbgen):
        print("*" * 10, igen, "*" * 10)
        stop = rob.update(nbiterpergen)
        if stop:
            break
        weights = get_weights(rob)
        fitnesses = get_fitnesses(rob)

        new_weights = fitprop(weights, fitnesses)
        apply_weights(rob, new_weights)
        reset_agent_observers(rob)


if __name__ == "__main__":
    main()
