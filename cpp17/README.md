# CPP17 raytracer by Oktosha

I (@Oktosha) wrote this raytracer in 2019. In this time the [Raytracing in one Weekend](https://raytracing.github.io/) used less modern C++ features than current versions. So I wrote a version that used `unique_ptr` a lot. I also wrapped it in Cython to be able to call it right from a Jupyter notebook. I haven't thought much about the performance. But turns out that the even naive c++ implementation that can be called from python is an interesting benchmark for a python raytracer.

## Setup

You need C++ compiler and python with `Cython` module installed. You can install Cython only or the complete pack of the python dependencies with the `requirements.txt` in the root folder.

You need to compile Cython module to be able to use it. Run this right from this folder:

```shell
python setup.py build_ext --inplace
```

*Running `python cpp17/setup.py build_ext --inplace` won't work, you do need to be in this directory*

Now you have a normal python module. It's name is `raytracing`. You can use the `render` function from it. For example, if you are in the root directory of this repo you can use the render function as follows:

```python
from cpp17.raytracing import render as cpp17_render

# defining the world and the camera...
# ...

image = cpp17_render(world, camera, h=100, w=200)
```

See `runme.ipynb` for the full example and benchmarks.
