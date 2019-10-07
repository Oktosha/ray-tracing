#include "vec3.h"

using namespace std;

int main() {
  {
    auto v = vec3();
    for (int e : v.e) {
      cout << e << " ";
    }
    cout << endl;
  }
  {
    auto v = vec3(1, 2, 3);
    for (int e : v.e) {
      cout << e << " ";
    }
    cout << endl;
  }
  return 0;
}
