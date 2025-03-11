import matplotlib.pyplot as plt

if __name__ == "__main__":
    file = open("log.txt", "r")
    lines = file.readlines()
    plains, autos = zip(
        *[(lines[i][:-1], lines[i + 1][:-1]) for i in range(0, len(lines), 2)]
    )

    plain_times = []
    auto_times = []
    for p, a in zip(plains, autos):
        plain_times.append(float(p.split(" ")[4][:-1]))
        auto_times.append(float(a.split(" ")[4][:-1]))

    plt.figure(figsize=(10, 6), dpi=300)
    plt.xlabel("Time")
    plt.ylabel("Frequency")
    plt.hist(plain_times, alpha=0.5, edgecolor="k", label="Plain")
    plt.hist(auto_times, alpha=0.5, edgecolor="k", label="Auto")
    plt.legend()
    plt.savefig("./hist.png")
