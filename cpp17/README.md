# CPP raytracer by Oktosha

I wrote this raytracer in 2019. In this time the [Raytracing in one Weekend](https://raytracing.github.io/) used less modern C++17 features than current versions. So I wrote a version that used `unique_ptr` a lot. I also wrapped it in Cython to be able to call it right from a Jupyter notebook. It's not optimized for performance but it's the first raytracer to be benchmarked.


## Setup

You need C++ compiler and python with `Cython` module installed. Right from this folder, compile the Python module:

```shell
python setup.py build_ext --inplace
```

Now you have a normal python module. It's name is `raytracing`. You can use the `render` function from it. For example, if you are in the root directory of this repo you can use the render function as follows:

```python
from oktosha.raytracing import render as oktosha_render

# defining the world and the camera...
# ...

image = oktosha_render(world, camera, h=100, w=200)
```

See `runme.ipynb` for the full example and benchmarks.
