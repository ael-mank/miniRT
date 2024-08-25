import json
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from mpl_toolkits.mplot3d import Axes3D
import tkinter as tk
from tkinter import ttk
import networkx as nx
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Function to draw a box given min and max coordinates
def draw_box(ax, min_coords, max_coords, color='r', alpha=0.3):
    x_min, y_min, z_min = min_coords
    x_max, y_max, z_max = max_coords

    # Define the vertices of the box
    vertices = [
        [x_min, y_min, z_min], [x_max, y_min, z_min], [x_max, y_max, z_min], [x_min, y_max, z_min],
        [x_min, y_min, z_max], [x_max, y_min, z_max], [x_max, y_max, z_max], [x_min, y_max, z_max]
    ]

    # Define the 12 edges composing the box
    edges = [
        [vertices[0], vertices[1], vertices[2], vertices[3]],
        [vertices[4], vertices[5], vertices[6], vertices[7]],
        [vertices[0], vertices[1], vertices[5], vertices[4]],
        [vertices[2], vertices[3], vertices[7], vertices[6]],
        [vertices[1], vertices[2], vertices[6], vertices[5]],
        [vertices[4], vertices[7], vertices[3], vertices[0]]
    ]

    # Create a 3D polygon collection for faces
    box_faces = Poly3DCollection(edges, alpha=alpha, facecolors=color, edgecolors='k')
    ax.add_collection3d(box_faces)

# Recursive function to draw the BVH tree
def draw_bvh_node(ax, node, current_level, target_level, colors):
    if node is None:
        return

    color = 'yellow' if node['object'] is not None else colors[current_level % len(colors)]
    if current_level == target_level:
        draw_box(ax, node['min'], node['max'], color=color, alpha=0.3 if node['object'] is None else 1.0)

    if 'children' in node:
        for child in node['children']:
            draw_bvh_node(ax, child, current_level + 1, target_level, colors)

# Function to render the BVH tree at the selected level
def render_bvh_tree(target_level):
    # Define colors for different levels
    colors = ['red', 'green', 'blue', 'cyan', 'magenta', 'orange']

    # Initialize the 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Draw the BVH tree
    draw_bvh_node(ax, bvh_tree, current_level=0, target_level=target_level, colors=colors)

    # Set plot labels
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Set plot limits
    ax.set_xlim([0, 600])
    ax.set_ylim([0, 600])
    ax.set_zlim([0, 600])

    # Show the plot
    plt.show()

# Function to create a networkx graph from the BVH tree
def create_bvh_graph(node, graph, parent=None):
    if node is None:
        return

    node_id = id(node)
    graph.add_node(node_id, label=node.get('object', ''))

    if parent is not None:
        graph.add_edge(parent, node_id)

    if 'children' in node:
        for child in node['children']:
            create_bvh_graph(child, graph, node_id)

# Function to create a hierarchical layout for the graph
def hierarchy_pos(G, root=None, width=1., vert_gap=0.2, vert_loc=0, xcenter=0.5):
    pos = _hierarchy_pos(G, root, width, vert_gap, vert_loc, xcenter)
    return pos

def _hierarchy_pos(G, root, width=1., vert_gap=0.2, vert_loc=0, xcenter=0.5, pos=None, parent=None, parsed=[]):
    if pos is None:
        pos = {root: (xcenter, vert_loc)}
    else:
        pos[root] = (xcenter, vert_loc)
        
    children = list(G.neighbors(root))
    if not isinstance(G, nx.DiGraph) and parent is not None:
        children.remove(parent)  
    if len(children) != 0:
        dx = width / len(children) 
        nextx = xcenter - width/2 - dx/2
        for child in children:
            nextx += dx
            pos = _hierarchy_pos(G, child, width=dx, vert_gap=vert_gap, vert_loc=vert_loc-vert_gap, xcenter=nextx, pos=pos, parent=root, parsed=parsed)
    return pos

# Function to render the BVH tree graph
def render_bvh_graph():
    graph = nx.DiGraph()
    create_bvh_graph(bvh_tree, graph)

    pos = hierarchy_pos(graph, root=id(bvh_tree))
    labels = nx.get_node_attributes(graph, 'label')

    fig, ax = plt.subplots()
    nx.draw(graph, pos, ax=ax, with_labels=True, labels=labels, node_size=500, node_color='lightblue', font_size=8, font_weight='bold', arrows=True)
    return fig

# Load the BVH structure from a JSON file
with open('bvh_structure.json', 'r') as file:
    bvh_tree = json.load(file)

# Create the main window
root = tk.Tk()
root.title("BVH Tree Renderer")

# Create a label and dropdown menu for selecting the level
label = ttk.Label(root, text="Select Level:")
label.pack(pady=10)

level_var = tk.IntVar()
level_dropdown = ttk.Combobox(root, textvariable=level_var)
level_dropdown['values'] = list(range(10))  # Assuming a maximum of 10 levels
level_dropdown.current(0)
level_dropdown.pack(pady=10)

# Function to handle rendering and closing previous plot
def on_render_button_click():
    plt.close('all')  # Close any existing plots
    render_bvh_tree(level_var.get())

# Create a button to render the BVH tree
render_button = ttk.Button(root, text="Render", command=on_render_button_click)
render_button.pack(pady=20)

# Create a frame for the tree visualization
tree_frame = ttk.Frame(root)
tree_frame.pack(pady=20)

# Render the BVH tree graph and embed it in the GUI
fig = render_bvh_graph()
canvas = FigureCanvasTkAgg(fig, master=tree_frame)
canvas.draw()
canvas.get_tk_widget().pack()

# Run the GUI event loop
root.mainloop()