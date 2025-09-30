import numpy as np
import matplotlib.pyplot as plt


sorting_methods = ["Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort"]


sizes = np.array([10, 50, 100, 1000, 5000, 10000, 50000])


times = {
    "Insertion Sort": [1.8e-06, 8.119e-06, 2.9607e-05, 0.001001, 0.026041, 0.092139, 2.2842],
    "Quick Sort": [1.9e-06, 5.873e-06, 1.2009e-05, 0.00012, 0.001002, 0.002, 0.0061],
    "Merge Sort": [4.92e-06, 3.4044e-05, 5.7211e-05, 0.0004, 0.002, 0.004, 0.02183],
    "Heap Sort": [3.691e-06, 1.1908e-05, 2.0698e-05, 0.000366, 0.002026, 0.003, 0.014504]
}


plt.figure(figsize=(10, 6))

for method in sorting_methods:
    plt.plot(sizes, times[method], marker='o', label=method)

plt.xscale("log")  
plt.yscale("log")  
plt.xlabel("Number of Elements (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Sorting Algorithm Performance Comparison")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.show()
