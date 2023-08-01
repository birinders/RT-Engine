# RT-Engine, C++

This is a basic Ray-Tracing Engine I've implemented from the absolute ground up in C++.
The Engine is capable of accurately ray tracing shapes like spheres, and any other shape(s) that can be represented by mathematical equations.

Since the engine is not reliant on polygons or similar methodology, it can (theoretically) simulate objects at near infinite resolution.
The engine uses renowned mathematical hacks like Schilck's Approximation to massively speed up the calculations at infinitesimal loss of accuracy.

The engine accounts for many artifacts present in real cameras as well, like aperture, focal length, etc and other similar artifacts present in actual glass inorder to accurately simulate it.

The engine can currently ray trace 4 different materials-
Glass (Dielectrics), Metals, Fuzzy (Matte) Metals, and Lambertian (solid) surfaces.

This version of the engine uses the OpenGL library just to output the rendered image to a screen. We can completely avoid using it if we use the built in image exporter, which exports the image as a PPM file instead of displaying it to a window. This completely eliminates the requirements of all external dependencies in the project.

### Why I made this project-
I built this project as my Computer Graphics project submission in my 6th semester. The assignment required us to build any 2d project using the OpenGL toolkit for C++, but that didn't feel adequate to me.
Since ray tracing in computer games always piqued my interest, this was the perfect opportunity to merge these common interests. Hence, it was decided that this project shall be built from ground up, with no external dependencies.

This engine is implemented in C++ due to the extremely strict performance requirements of the project. A 1080p image with 50+ spheres of mixed types takes nearly 15 minutes to render a single frame in C++.
Therefore, while Python would've significantly cut down on the development time, the project would've been practically unusable at Python's runtime speed.
Hence, C++ was my language of choice for this project.

Another reason to choose C++ for me was that while I find myself working most comfortably with Python, I never had a real middle-to-large scale project with any other languages.
Since I worked with C++ before I ever switched to Python, now combined with the 3 years of understanding of the subject, I felt I had adequate knowledge to proceed and step out of my comfort zone, and build a project in another language.
While python would've provided something for me in its standard modules (along with a beautiful GC), I believe this project taught me more than just Python ever would've alone.

And then three weeks and countless hours spent debugging later, I lay before you the results-
