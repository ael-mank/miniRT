import sys

def parse_obj_file(file_path):
    vertices = []
    triangles = []

    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith('v '):
                parts = line.strip().split()
                vertex = (float(parts[1]), float(parts[2]), float(parts[3]))
                vertices.append(vertex)
            elif line.startswith('f '):
                parts = line.strip().split()
                v1 = int(parts[1].split('/')[0]) - 1
                v2 = int(parts[2].split('/')[0]) - 1
                v3 = int(parts[3].split('/')[0]) - 1
                triangles.append((v1, v2, v3))

    return vertices, triangles

def generate_c_code(vertices, triangles):
    c_code = ""
    for i, (v1, v2, v3) in enumerate(triangles):
        c_code += f"triangle = create_triangle(\n"
        c_code += f"    (t_point3){{{vertices[v1][0]}, {vertices[v1][1]}, {vertices[v1][2]}}},  // Vertex 1\n"
        c_code += f"    (t_point3){{{vertices[v2][0]}, {vertices[v2][1]}, {vertices[v2][2]}}},  // Vertex 2\n"
        c_code += f"    (t_point3){{{vertices[v3][0]}, {vertices[v3][1]}, {vertices[v3][2]}}},  // Vertex 3\n"
        c_code += f"    MATTE, \n"
        c_code += f"    (t_vec3){{0, 1, 0.73}}\n"
        c_code += f");\n"
        c_code += f"head = add_triangle(head, triangle);\n\n"
    return c_code

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <path_to_obj_file>")
        return

    file_path = sys.argv[1]
    vertices, triangles = parse_obj_file(file_path)
    c_code = generate_c_code(vertices, triangles)

    with open("generated_triangles.c", "w") as file:
        file.write(c_code)

    print("C code generated and saved to generated_triangles.c")

if __name__ == "__main__":
    main()