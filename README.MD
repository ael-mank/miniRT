<p align="center">
    <h1 align="center">MINIRT</h1>
</p>
<p align="center">
    <em><code>❯ Raytracing renderer written in C.</code></em>
</p>



##  Overview


miniRT is a simple raytracing renderer written in C. The project is designed to render 3D scenes using the raytracing algorithm. The project is built with the C programming language and is designed to run on Unix-based systems.



##  Features

- Many geometric objects: spheres, planes, cubes, triangles, and cylinders.
- Textures such as Metal, Glass, Matte and Light.
- Texture mapping
- Anti-aliasing
- Depth of field
- Soft shadows
- Optimized rendering using a [BVH](https://en.wikipedia.org/wiki/Bounding_volume_hierarchy) tree



##  Getting Started

###  Installation

Build the project from source:

1. Clone the miniRT repository:
```sh
❯ git clone https://github.com/ael-mank/miniRT
```

2. Navigate to the project directory:
```sh
❯ cd miniRT
```

3. Compile the project using the Makefile:
```sh
❯ make
```

###  Usage

To run the project, execute the following command:

```sh
❯ ./miniRT [scene.rt]
```

##  Resources and References

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book series by Peter Shirley. 

- [Scratcapixel](https://www.scratchapixel.com/) website.

- [Aurelien Brabant](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx#finding-the-pixels-first-bytes-address) blog post about the minilibx.
