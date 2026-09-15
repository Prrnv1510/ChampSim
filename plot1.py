import matplotlib.pyplot as plt


associativity = [4, 8, 16]

lru = [29.53, 26.95, 25.67]
hawkeye = [31.01, 27.12, 24.16]

plt.figure(figsize=(6,4))

plt.plot(associativity, lru, marker='o', linewidth=2, label='LRU')
plt.plot(associativity, hawkeye, marker='s', linewidth=2, label='Hawkeye')

plt.title("LLC Miss Rate vs LLC Associativity")
plt.xlabel("Associativity (ways)")
plt.ylabel("LLC Miss Rate (%)")

plt.xticks([4, 8, 16])
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend()

plt.tight_layout()

# Saves the figure
plt.savefig("plot1_llc_associativity.png", dpi=300)

# Displays the graph
plt.show()