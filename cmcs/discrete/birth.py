import argparse

import matplotlib.pyplot as plt


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
    parser.add_argument("-initial_N", type=int, help="specify the initial density")
    parser.add_argument("-delta", type=int, help="specify the timestep")
    parser.add_argument("-lam", type=int, help="specify the number of offsprings")
    parser.add_argument("-sigma", type=int, help="specify the rate of reproduction")
    parser.add_argument("-iterations", type=int, help="specify number of iterations")
    args = parser.parse_args()

    N = args.initial_N
    delta = args.delta
    lam = args.lam
    sigma = args.sigma
    iterations = args.iterations

    time_units, density = run_simulation(N, delta, lam, sigma, iterations)
    time_units, density2 = run_simulation(N, delta, lam + 1, sigma, iterations)

    plt.figure(figsize=(12, 6), dpi=100)
    plt.title("Exponential Growth")
    plt.xlabel("Time")
    plt.xticks(time_units, labels=time_units)
    plt.ylabel("Density")
    plt.plot(time_units, density, "rx--", label=r"\lambda = " + str(lam))
    plt.plot(time_units, density2, "bx--", label=r"\lambda = " + str(lam + 1))
    plt.grid()
    plt.legend()
    plt.show()
