#include <eve/eve.hpp>
#include <iostream>

int main()
{
  float arr[4];
  int iarr[4];
  eve::logical<float> larr[4];

  eve::wide<float, eve::fixed<4>> w = {3, 2, 1, 0};
  eve::logical<eve::wide<float, eve::fixed<4>>> lw = {true, false, true, false};

  eve::store(w, arr);
  eve::store(lw, larr);
  eve::store(lw, iarr);

  std::cout << "arr: ";
  for (auto val : arr) {
    std::cout << val << " ";
  }
  std::cout << "\n";

  std::cout << "larr: ";
  for (auto val : larr) {
    std::cout << val << " ";
  }
  std::cout << "\n";

  std::cout << "iarr: ";
  for (auto val : iarr) {
    std::cout << val << " (" << (val ? "true" : "false") << ") ";
  }
  std::cout << "\n";
}
