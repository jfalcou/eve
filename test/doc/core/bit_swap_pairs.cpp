// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide<int, eve::fixed<4>> wi0{2, 4, 9, 5};
  eve::wide<int, eve::fixed<4>> wi1{1, 3, 3, 3};
  eve::wide<int, eve::fixed<4>> wi2{0, 2, 1, 2};
  eve::wide<int, eve::fixed<4>> wi3{0, -2, -1, 7};

  std::cout << std::showbase << std::hex;
  std::cout << "<- wi0                                           = " << wi0 << "\n";
  std::cout << "<- wi1                                           = " << wi1 << "\n";
  std::cout << "<- wi2                                           = " << wi2 << "\n";

  std::cout << "-> bit_swap_pairs(wi0, wi1, wi2)                 = " << eve::bit_swap_pairs(wi0, wi1, wi2) << "\n";
  std::cout << "-> bit_swap_pairs[ignore_last(2)](wi0, wi1, wi2) = " << eve::bit_swap_pairs[eve::ignore_last(2)](wi0, wi1, wi2) << "\n";
  std::cout << "-> bit_swap_pairs[wi3 > 0](wi0, wi1, wi3)        = " << eve::bit_swap_pairs[wi3 >= 0](wi0, wi1, wi3) << "\n";
}
