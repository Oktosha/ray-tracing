# ray-tracing

Completion of the [Ray Tracing in One Weekend](https://raytracing.github.io/) tutorial with c++17
wrapped into Cython.

To launch the jupyter notebook example in `runme.ipynb` prepare the python environment with following:

```shell
python3 -m venv venv/ray-tracing
source venv/ray-tracing/bin/activate
pip install -r requirements.txt
```

Now you can run jupyter notebook server with

```shell
jupyter notebook
```

Or open the `runme.ipynb` file in vscode and select your newly created `ray-tracing` virtual environment as kernel.

It takes ≈47s to render the image below on my machine (1200 x 675 pixels). More benchmarks and details in `runme.ipynb`.

![Result](https://raw.githubusercontent.com/Oktosha/ray-tracing/master/out.png)
