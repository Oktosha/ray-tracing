# cython: language_level=3
# distutils: language=c++

cdef extern from "hierarchy.h":
  cppclass Base:
    int DoComputation() const

  cppclass Child(Base):
    int DoComputation() const

  int  DoComputationWithBase(Base *base_object)

def do_computation_py():
  cdef Child ch
  return DoComputationWithBase(&ch)