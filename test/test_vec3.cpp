#include "../src/vec3.h"

using namespace std;

int main() {
  {
    auto v = Vec3();
    cout << v << endl;
    cout << endl;
  }
  {
    auto v = Vec3(1, 2, 3);
    cout << v << endl;
    cout << endl;
  }
  return 0;
}
