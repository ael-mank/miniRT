import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Function to draw a box given min and max coordinates
def draw_box(ax, min_coords, max_coords, color='r', alpha=0.1):
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

    # Create a 3D polygon collection
    box = Poly3DCollection(edges, alpha=alpha, facecolors=color)
    ax.add_collection3d(box)

# Function to draw a sphere given center and radius
def draw_sphere(ax, center, radius=0.1, color='b'):
    u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
    x = center[0] + radius * np.cos(u) * np.sin(v)
    y = center[1] + radius * np.sin(u) * np.sin(v)
    z = center[2] + radius * np.cos(v)
    ax.plot_surface(x, y, z, color=color, alpha=0.6)

# Initialize the 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Example BVH structure
bvh_nodes = [
    {'min': [-3.00, -3.00, -0.00], 'max': [3.00, 3.00, 5.00], 'object': None, 'children': [
        {'min': [-3.00, -2.00, -0.00], 'max': [2.00, 2.00, 5.00], 'object': None, 'children': [
            {'min': [-3.00, -2.00, 1.00], 'max': [-3.00, 2.00, 5.00], 'object': [0, 0, 3]},
            {'min': [-2.00, -2.00, -0.00], 'max': [2.00, 2.00, 0.00], 'object': [0, 0, 0]}
        ]},
        {'min': [-2.00, -3.00, 1.00], 'max': [3.00, 3.00, 5.00], 'object': None, 'children': [
            {'min': [3.00, -2.00, 1.00], 'max': [3.00, 2.00, 5.00], 'object': [3, 0, 3]},
            {'min': [-2.00, -3.00, 1.00], 'max': [2.00, 3.00, 5.00], 'object': None, 'children': [
                {'min': [-2.00, -3.00, 5.00], 'max': [2.00, -3.00, 1.00], 'object': [0, -3, 3]},
                {'min': [-2.00, 3.00, 1.00], 'max': [2.00, 3.00, 5.00], 'object': [0, 3, 3]}
            ]}
        ]}
    ]}
]

# Recursive function to draw the BVH tree
def draw_bvh_node(ax, node):
    draw_box(ax, node['min'], node['max'], color='r')
    if node['object']:
        draw_sphere(ax, node['object'], color='b')
    if 'children' in node:
        for child in node['children']:
            draw_bvh_node(ax, child)

# Draw the BVH tree
draw_bvh_node(ax, bvh_nodes[0])

# Set plot labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Set plot limits
ax.set_xlim([-4, 4])
ax.set_ylim([-4, 4])
ax.set_zlim([-1, 6])

# Show the plot
plt.show()