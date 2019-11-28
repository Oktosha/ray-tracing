class Base {
  public:
  virtual int DoComputation() const;
  virtual ~Base() = default;
};

class Child : public Base {
  public:
  int DoComputation() const override {
    return 42;
  }
};

int DoComputationWithBase(Base *base_object) {
  return base_object->DoComputation();
}