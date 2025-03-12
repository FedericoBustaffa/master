import matplotlib.pyplot as plt
import pandas as pd

if __name__ == "__main__":
    df = pd.read_csv("./times.csv")

    algs = df["algorithm"].unique()
    sizes = df["array_length"].unique()

    plt.figure(figsize=(10, 6), dpi=300)
    plt.title("Time trend over input dimension")

    for alg in algs:
        tmp = df[df["algorithm"] == alg][["array_length", "time"]]
        plt.plot(tmp["array_length"], tmp["time"], marker="o", label=alg)

    plt.xlabel("Array Length")
    plt.ylabel("Time (seconds)")

    plt.xscale("log", base=2)
    plt.grid()
    plt.legend()
    plt.savefig("trend.svg")
    plt.show()
