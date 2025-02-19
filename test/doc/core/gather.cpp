#include <iostream>
#include <eve/module/core.hpp>

int main()
{
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  eve::wide<int, eve::fixed<4>> res = eve::gather(v.data(), eve::wide<unsigned char, eve::fixed<4>>{0, 2, 2, 11});

  std::cout << "res -> " << res << std::endl;
}
