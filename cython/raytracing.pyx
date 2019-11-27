# cython: language_level=3

def print_hello_to(name):
  print("Hello, {}!".format(name))

def render(h, w):
  """ Renders example (h, w, 3) image"""
  image = [[[i / w, j / h, 0.2] for i in range(w)] for j in range(h)]
  return image