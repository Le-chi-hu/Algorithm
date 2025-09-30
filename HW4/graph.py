import networkx as nx
import matplotlib.pyplot as plt
import pandas as pd


def load_adjlist_csv(filename):
    df = pd.read_csv(filename)
    edges = []
    for _, row in df.iterrows():
        u = int(row['Node'])  
        if pd.isna(row['Neighbors']):
            continue  # If the node has no neighbors, skip it.
        neighbors = list(map(int, str(row['Neighbors']).split()))
        for v in neighbors:
            if u < v:  # Avoid adding repeated undirected edges
                edges.append((u, v))
    return edges


def get_all_nodes(filename):
    df = pd.read_csv(filename)
    return df['Node'].tolist()


def build_graph(filename):
    edges = load_adjlist_csv(filename)
    nodes = get_all_nodes(filename)
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)
    return G


G_original = build_graph("OriginalGraph.csv")
G_dfs = build_graph("DFSTree.csv")
G_bfs = build_graph("BFSTree.csv")


pos = nx.spring_layout(G_original, seed=42)


plt.figure(figsize=(18, 6))


plt.subplot(1, 3, 1)
nx.draw(G_original, pos, with_labels=True, node_color='skyblue', edge_color='gray', node_size=500)
plt.title("Original Graph")


plt.subplot(1, 3, 2)
nx.draw(G_dfs, pos, with_labels=True, node_color='lightgreen', edge_color='green', node_size=500)
plt.title("DFS Tree")


plt.subplot(1, 3, 3)
nx.draw(G_bfs, pos, with_labels=True, node_color='lightcoral', edge_color='red', node_size=500)
plt.title("BFS Tree")

plt.tight_layout()
plt.show()
