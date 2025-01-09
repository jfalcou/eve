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
  std::cout << "<- wi2                                           = " << wi2 << "\n\n";
                                                                 
  std::cout << "-> bit_swap_pairs(wi0, wi1, wi2)                 = " << eve::bit_swap_pairs(wi0, wi1, wi2) << "\n";
  std::cout << "-> bit_swap_pairs[ignore_last(2)](wi0, wi1, wi2) = " << eve::bit_swap_pairs[eve::ignore_last(2)](wi0, wi1, wi2) << "\n";
  std::cout << "-> bit_swap_pairs[wi3 > 0](wi0, wi1, wi3)        = " << eve::bit_swap_pairs[wi3 >= 0](wi0, wi1, wi3) << "\n\n";

  std::cout << "-> bit_swap_pairs(wi0, 3, 2)                 = " << eve::bit_swap_pairs(wi0, 3, 2) << "\n";
  std::cout << "-> bit_swap_pairs[ignore_last(2)](wi0, 3, 2) = " << eve::bit_swap_pairs[eve::ignore_last(2)](wi0, 3, 2) << "\n";
  std::cout << "-> bit_swap_pairs[wi3 > 0](wi0, 3, 2)        = " << eve::bit_swap_pairs[wi3 >= 0](wi0, 3, 2) << "\n\n";

  auto i3 = eve::index_t<3>{};
  auto i2 = eve::index_t<2>{};
  std::cout << "-> bit_swap_pairs(wi0, i3, i2)                 = " << eve::bit_swap_pairs(wi0, i3, i2) << "\n";
  std::cout << "-> bit_swap_pairs[ignore_last(2)](wi0, i3, i2) = " << eve::bit_swap_pairs[eve::ignore_last(2)](wi0, i3, i2) << "\n";
  std::cout << "-> bit_swap_pairs[wi3 > 0](wi0, i3, i2)        = " << eve::bit_swap_pairs[wi3 >= 0](wi0, i3, i2) << "\n\n";
}
