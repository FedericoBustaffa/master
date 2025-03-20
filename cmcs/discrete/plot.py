import json

import matplotlib.pyplot as plt

if __name__ == "__main__":
    file = open("results/simple_birth.json", "r")
    data = json.load(file)
    file.close()

    plt.figure(figsize=(8, 5), dpi=100)
    plt.title("Exponential Growth")

    for d in data:
        if (
            d["iterations"] == 20
            and d["lambda"] == 1
            and d["sigma"] == 1
            and d["delta"] == 1
        ):
            plt.plot(
                d["time_units"],
                d["density"],
                "--x",
                label=rf"$N_0$ = {d['initial_density']}",
            )

    plt.grid()
    plt.legend()
    plt.tight_layout()
    plt.show()
