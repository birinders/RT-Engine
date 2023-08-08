# RT-Engine, C++

## Update 1.1-
### Parallel Processing has been deployed into the project and is currently LIVE!
As mentioned in the initial project notes, a multiprocessing solution was under review for this project. Finally after reviewing the project status and cross-validating relevant race conditions, parallel processing is now live in the project.
This has reduced computational times by over 10x for more complicated scenes (exact figures may vary by your CPU cores), and over 6x for lesser populated scenes! Exact speedups will be posted in a few days for some of the renders displayed underneath.

--------------------------------
This is a basic Ray-Tracing Engine I've implemented from the absolute ground up in C++.
The Engine is capable of accurately ray tracing shapes like spheres, and any other shape(s) that can be represented by mathematical equations.

The engine is technically a path tracer, and relies on vector math, and clever mathematical shortcuts (like Schlick’s Approximation for Dielectric Materials) to produce the desired results, at a relatively lower computational expense. The engine also accurately simulates a camera, with adjustable focal depth, aperture, and can accurately simulate a defocus blur on a set distance, or focal length. The engine has built in anti-aliasing in order to smoothen out any outputs, as well as the anti-aliasing module forming an essential part of the shading algorithm. 

Since the engine is not reliant on polygons or similar methodology, it can (theoretically) simulate objects at near infinite resolution.

The engine can currently ray trace 4 different materials-
Glass (Dielectrics), Metals, Fuzzy (Matte) Metals, and Lambertian (solid) surfaces.

This engine relies on vector mathematics, and can ray trace 3d shapes which can be expressed in the form of equations, like spheres and tori (doughnut shape). This engine can also export the renders in the form of PPM images, which can be converted to other formats by suitable means. 

The camera itself is movable using W,A,S,D keys, and camera's orientation can be adjusted using I,J,K,L keys. Z and X keys control the height of the camera.
Even though the camera is movable, it might still be impractical to do so due to the relatively slow rendering times.

This version of the engine uses the OpenGL library just to output the rendered image to a screen. We can completely avoid using it if we use the built in image exporter, which exports the image as a PPM file instead of displaying it to a window. This completely eliminates the requirement of any and all external dependencies in the project.

### Why I made this project-
I built this project as my Computer Graphics project submission in my 6th semester. The assignment required us to build any 2d project using the OpenGL toolkit for C++, but that didn't feel adequate for the opportunity at hand.
Since ray tracing in computer games always piqued my interest, this presented the perfect opportunity to integrate these common interests. Hence, it was decided that this project shall be built from ground up, with no external dependencies.

### Reminder- The multiprocessing update has been deployed! 
(Run the '''git pull''' command to update your version)

This engine is implemented in C++ due to the extremely strict performance requirements of the project. A 16:9, 1080p image at 100x Anti-Aliasing Sampling with 50+ spheres of mixed types took nearly 30 minutes to render a single frame in C++. Another reason for this relatively slow performance even in C++ was the lack of GPU leverage, or even the other CPU cores, as the application was then entirely single-threaded. 
Now with version 1.1, we have made monumental speed gains by introducing multi-processing and parallelization into the program, such that each individual process is responsible for rendering its own independent part of the frame. This has bumped up the efficiency by over 8 fold, and now a 1080p image with *over 200 spheres* at 100x anti-aliasing takes just under 4 minutes to render.

Therefore, while Python would've significantly cut down on the development time, the project would've been practically unusable at Python's runtime speed.
Hence, C++ was my language of choice for this project.

Another reason to choose C++ for me was that while I find myself working most comfortably with Python, I never had a real middle-to-large scale project with any other languages.
Since I worked with C++ before I ever switched to Python, now combined with the 3 years of understanding of the subject, I felt I had adequate knowledge to proceed and step out of my comfort zone, and build a project in another language.
While python would've provided something for me in its standard modules (along with a beautiful GC), I believe this project taught me more than just Python ever would've alone.

## The Result-

<p align="center">
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/0775cb15-bf94-4390-9cc9-b5316a86e72e" width="400">
  <br>
  <sub>A 800px wide, 16:9 render of 200+ spheres of all types, with 100x Anti Aliasing resampling and 50 reflects-per-ray<br>(Footage has been sped up by 30x)</sub>
</p>

### The Final Render-
<p align="center">
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/52f3388a-3d63-43fd-a128-604cc82044e3" width="800">
  <br>
  <sub>The final render, in full resolution, as produced by the Engine</sub>
</p>
<!--![image](https://github.com/birinders/RT-Engine/assets/102192983/52f3388a-3d63-43fd-a128-604cc82044e3)-->

<!--![random_world (2) (2)](https://github.com/birinders/RT-Engine/assets/102192983/0775cb15-bf94-4390-9cc9-b5316a86e72e)-->
<br>

#### An Example of a real-time render-
<p align="center">
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/2c0f1363-ec5d-4f2d-9931-d5ebc99829ac" alt="Realtime Render" width="800">
  <br>
  <sub>A realtime single-threaded render of a 800px wide, 16:9 render of all 4 type of spheres (the ground itself is a lambertian sphere)<br>STD::Cerr output on the right side<br>(slight colour details may have been lost due to GIF compression)</sub>
</p>
<br>
<!--![ezgif com-optimize](https://github.com/birinders/RT-Engine/assets/102192983/2c0f1363-ec5d-4f2d-9931-d5ebc99829ac)-->
<!--
<p align="center">
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/4a68f214-f239-4431-be5b-351d1ed00695" alt="Cerr Output" width="400">
  <br>
  <sub>The associated STD::cerr Output</sub>
</p>
<br>
-->

<h3 align="center">Some other interesting interactions between materials-</h3><br>
<p align="center">
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/7ea8e514-33dd-48fd-a73c-eec38df42cc7" alt="Cerr Output" width="600">
  <br>
  <sub>A re-render of the random scene, with lowered aperture</sub>
  <br><br><br>
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/b6e12aad-c39a-4965-9c29-292497c9ef45" alt="Cerr Output" width="600">
  <br>
  <sub>Multiple Hollow Glass/Metal Interaction</sub>
  <br><br><br>
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/9e45ec80-44e0-4e8e-b148-37c8a1f6004a" alt="Cerr Output" width="600">
  <br>
  <sub>Dense Glass Sphere in front of Dense Glass Sphere</sub>
  <br><br><br>
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/8dfc9d19-c234-4888-82d5-416514ffaf4c" alt="Cerr Output" width="600">
  <br>
  <sub>Reflective Metal Sphere inside a hollow Glass Sphere</sub>
  <br><br><br>
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/019647aa-c9ea-4851-9690-92da3d41adab" alt="Cerr Output" width="600">
  <br>
  <sub>Same Metal Sphere, instead placed along the upper inside edge of a dense glass sphere</sub>
  <br><br><br>
  <img src="https://github.com/birinders/RT-Engine/assets/102192983/741a0e1d-5811-48cc-a35a-1a909c210581" alt="Cerr Output" width="1000">
  <br>
  <sub>A 36:9 ultrawide shot of the random scene</sub>
  
  
</p>
<!--![image](https://github.com/birinders/RT-Engine/assets/102192983/019647aa-c9ea-4851-9690-92da3d41adab)

![image](https://github.com/birinders/RT-Engine/assets/102192983/8dfc9d19-c234-4888-82d5-416514ffaf4c)

![image](https://github.com/birinders/RT-Engine/assets/102192983/9e45ec80-44e0-4e8e-b148-37c8a1f6004a)

![image](https://github.com/birinders/RT-Engine/assets/102192983/7ea8e514-33dd-48fd-a73c-eec38df42cc7)
![image](https://github.com/birinders/RT-Engine/assets/102192983/b6e12aad-c39a-4965-9c29-292497c9ef45)

![image](https://github.com/birinders/RT-Engine/assets/102192983/741a0e1d-5811-48cc-a35a-1a909c210581)


<!--![3_spheres_output (2)](https://github.com/birinders/RT-Engine/assets/102192983/014698a4-b4ed-41b9-8123-81a9d03af193)-->
<!--![3_spheres_cmd](https://github.com/birinders/RT-Engine/assets/102192983/4a68f214-f239-4431-be5b-351d1ed00695)-->

