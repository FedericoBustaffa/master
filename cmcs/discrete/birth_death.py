import argparse
import json

import matplotlib.pyplot as plt


def simulate(N, delta, birth_rate, death_rate, incoming, carrying_capacity, iterations):
    time_units = []
    density = []
    for i in range(0, iterations, delta):
        time_units.append(i)
        density.append(N)
        d = ((birth_rate - death_rate) * N + incoming) * (1 - N / carrying_capacity)
        N = d if d > 0 else 0

    return time_units, density


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("config", type=str, help="specify the config file")
    args = parser.parse_args()

    file = open(args.config, "r")
    config = json.load(file)
    file.close()

    initial_densities = config["initial_N"]
    deltas = config["delta"]
    birth_rates = config["birth_rate"]
    death_rates = config["death_rate"]
    incomings = config["incoming"]
    capacities = config["carrying_capacity"]
    iterations = config["iterations"]

    plt.figure(figsize=(8, 5), dpi=300)
    plt.title("Linear Birth/Death Model")
    plt.xlabel("Time")
    plt.ylabel("Population Density")

    for n in initial_densities:
        for delta in deltas:
            for br in birth_rates:
                for dr in death_rates:
                    for inc in incomings:
                        for k in capacities:
                            for it in iterations:
                                time_units, density = simulate(
                                    n, delta, br, dr, inc, k, it
                                )
                                label = ""
                                if len(initial_densities) > 1:
                                    label = rf"$N_0$ = {n}"
                                elif len(birth_rates) > 1:
                                    label = rf"$r_d$ = {br}"
                                elif len(death_rates) > 1:
                                    label = rf"$s_d$ = {dr}"
                                elif len(incomings) > 1:
                                    label = rf"$\beta$ = {inc}"
                                elif len(capacities) > 1:
                                    label = rf"$K$ = {k}"

                                plt.plot(time_units, density, "x--", label=label)
                                plt.xticks(time_units, labels=time_units)

    plt.grid()
    plt.legend()
    plt.tight_layout()
    plt.show()
