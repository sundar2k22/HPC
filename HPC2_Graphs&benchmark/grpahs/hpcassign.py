import matplotlib.pyplot as plt

def plot_graphs():
    # Data from the second CSV file
    data2 = {
        'injection rate': [0.001, 0.002, 0.003, 0.004, 0.005],
        'total runtime': [0.185432, 0.205764, 0.300145, 0.350871, 0.349876]
    }

    # Plot graph for the second dataset
    plt.figure(figsize=(10, 5))
    plt.plot(data2['injection rate'], data2['total runtime'], marker='s', linestyle='--', color='g', label='File 2')
    plt.title('Graph for File 2')
    plt.xlabel('Injection Rate')
    plt.ylabel('Total Runtime')
    plt.grid(True)
    plt.legend()
    plt.savefig('file2_graph.png')
    plt.show()

# Run the function
plot_graphs()