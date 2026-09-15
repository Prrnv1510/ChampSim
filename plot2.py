import matplotlib.pyplot as plt

# Benchmarks
benchmarks = ["456.hmmer", "429.mcf", "473.astar"]

# Miss-rate reduction (%)
reduction = [5.9033, 1.3881, 1.6444]

plt.figure(figsize=(6,4))
plt.bar(benchmarks, reduction, width=0.5)

plt.title("LLC Miss-rate Reduction over LRU")
plt.ylabel("Reduction (%)")
plt.ylim(0, 7)

# Value labels on top of bars
for i, value in enumerate(reduction):
    plt.text(i, value + 0.1, f"{value:.2f}%", ha="center")

plt.tight_layout()
plt.show()