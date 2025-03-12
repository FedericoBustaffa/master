import sys

import numpy as np
import pandas as pd

if __name__ == "__main__":
    times = {
        "algorithm": [],
        "array_length": [],
        "time": [],
    }

    for i, path in enumerate(sys.argv):
        if i == 0:
            continue

        # extract properties
        tokens = path.split("_")
        alg = tokens[0]
        n = int(tokens[2].removesuffix(".txt"))

        # fill with results
        times["algorithm"].append(alg)
        times["array_length"].append(n)

        with open(path, "r") as file:
            lines = file.readlines()
            ts = [
                float(line.split(" ")[4].removesuffix("s\n"))
                for line in lines
                if line != ""
            ]

            times["time"].append(np.mean(ts))

    # save the results
    df = pd.DataFrame(times)
    order = ["plain", "auto", "avx"]
    df["algorithm"] = pd.Categorical(df["algorithm"], categories=order, ordered=True)
    df.sort_values(by=["algorithm", "array_length"], inplace=True)
    df.to_csv("./times.csv", index=False, header=True, float_format="%g")
