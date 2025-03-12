import matplotlib.pyplot as plt

if __name__ == "__main__":
    file = open("log.txt", "r")
    lines = file.readlines()
    plains, autos, avxs = zip(
        *[
            (lines[i][:-1], lines[i + 1][:-1], lines[i + 2][:-1])
            for i in range(0, len(lines), 3)
        ]
    )

    plain_times = []
    auto_times = []
    avx_times = []
    for p, au, avx in zip(plains, autos, avxs):
        plain_times.append(float(p.split(" ")[4][:-1]))
        auto_times.append(float(au.split(" ")[4][:-1]))
        avx_times.append(float(avx.split(" ")[4][:-1]))

    plt.figure(figsize=(10, 6), dpi=300)
    plt.xlabel("Time")
    plt.ylabel("Frequency")
    plt.hist(plain_times, alpha=0.5, edgecolor="k", label="Plain")
    plt.hist(auto_times, alpha=0.5, edgecolor="k", label="Auto")
    plt.hist(avx_times, alpha=0.5, edgecolor="k", label="AVX")
    plt.legend()
    plt.savefig("./hist.png")
