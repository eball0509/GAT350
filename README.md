# GAT350 - Graphics Exploration

This project explores fundamental computer graphics concepts by implementing a software renderer and a ray tracer.

**Software Renderer**

* **Features:**
    * **Vertex and Fragment Shaders:** Supports custom vertex and fragment shaders for flexible lighting and material effects.
    * **Lighting Models:** Implements Gouraud and Phong shading for realistic lighting calculations on 3D models.
    * **Primitive Rendering:** Renders basic primitives like points, lines, and triangles.
    * **Model Loading:** Supports loading and rendering 3D models (e.g., OBJ format).
    * **Post-Processing:** Includes basic post-processing effects like gamma correction.
    * **Libraries:** Utilizes SDL for windowing and input, GLM for linear algebra and vector operations, and STB for image loading.
    
   ![Screenshot 2024-10-12 212329](https://github.com/user-attachments/assets/783ced05-ffa2-4f50-af89-a2e357d52266)

   ![Screenshot 2024-10-12 212309](https://github.com/user-attachments/assets/bb7c91e8-594d-4583-a6a5-06cf55e6b740)

    * **Usage:** You can move around in the Software Rendere with these controls:
      While holding Right Click:
      W - UP
      A - Right
      S - Down
      D - Left
      Q - Backwards
      E - Forwards
                                                                                 

**Ray Tracer**

* **Features:**
    * **Primitive Rendering:** Renders spheres, planes, and other basic shapes.
    * **Model Rendering:** Supports rendering complex 3D models.
    * **Material Models:** Implements Lambertian, metallic, and dielectric materials for realistic reflections and refractions.
    * **Ray-Object Intersection:** Efficiently calculates intersections between rays and scene objects.
    * **Anti-Aliasing:** Reduces aliasing artifacts using techniques like super-sampling.
    * **Multiple Bounce Reflections:** Simulates multiple reflections for more accurate and realistic rendering.
 
    * ![Screenshot 2024-12-05 153834](https://github.com/user-attachments/assets/0a175bbc-bfe2-40d3-986c-422ef0012bef)
      
**Understanding Vertex and Fragment Shaders**

* **Vertex Shader:**
    * **Purpose:** Transforms vertex positions and prepares data for rasterization.
    * **Key Operations:** 
        * Model, view, and projection transformations.
        * Clipping.
        * Perspective division.

* **Fragment Shader**
    * **Purpose:** Determines the color of each pixel (fragment).
    * **Key Operations:** 
        * Lighting calculations.
        * Texturing.
        * Blending.
        * Other effects (e.g., fog, shadows, transparency).

* **Key Differences:**
    * **Scope:** Vertex shader operates on vertices, fragment shader operates on pixels.
    * **Data Flow:** Vertex shader output is used to generate fragments for fragment shader processing.

**Getting Started**

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/eball0509/GAT350](https://github.com/eball0509/GAT350)
