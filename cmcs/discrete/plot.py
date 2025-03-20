import argparse
import json

import matplotlib.pyplot as plt

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="filename to save the figure")
    args = parser.parse_args()

    file = open("results/simple_birth.json", "r")
    data = json.load(file)
    file.close()

    plt.figure(figsize=(8, 5), dpi=300)
    plt.title("Exponential Growth")
    plt.xlabel("Time")
    plt.ylabel("Density")

    for d in data:
        if (
            d["iterations"] == 20
            and d["lambda"] == 1
            and d["sigma"] == 1
            and d["delta"] == 2
        ):
            plt.plot(
                d["time_units"],
                d["density"],
                "--x",
                label=rf"$N_0$ = {d['initial_density']}",
            )
            plt.xticks(d["time_units"], labels=d["time_units"])

    plt.grid()
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{args.filename}.svg")
    plt.show()
