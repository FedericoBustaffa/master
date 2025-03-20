import argparse
import json


def run_simulation(N, delta, lam, sigma, iterations):
    time_units = []
    density = []
    for i in range(0, iterations, delta):
        time_units.append(i)
        density.append(N)
        N = (1 + lam * delta / sigma) * N

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
    lambdas = config["lambda"]
    sigmas = config["sigma"]
    iterations = config["iterations"]

    results = []

    for n in initial_densities:
        for delta in deltas:
            for lam in lambdas:
                for sigma in sigmas:
                    for it in iterations:
                        time_units, density = run_simulation(n, delta, lam, sigma, it)
                        partial = {
                            "initial_density": n,
                            "delta": delta,
                            "lambda": lam,
                            "sigma": sigma,
                            "iterations": it,
                            "time_units": time_units,
                            "density": density,
                        }
                        results.append(partial)

    file = open("results/simple_birth.json", "w")
    json.dump(results, file, indent=2)
    file.close()
