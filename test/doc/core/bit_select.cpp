// revision 2
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

  eve::wide wl = {2, -3, 0,  1 << 10};
  eve::wide wi = {3, -2, 4,  2 };
  eve::wide wu = {0u, 1023u, 1u, ~0u << 8};

  std::cout << "<- wl                       = " << wl << "\n";
  std::cout << "<- wi                       = " << wi << "\n";
  std::cout << "<- wu                       = " << wu << "\n";

  std::cout << "-> bit_select(wl, wu, 0) = " << eve::bit_select(wl, wu, ~0u) << "\n";
  std::cout << "-> bit_select(wl, wi, 0) = " << eve::bit_select(wl, wi, -1) << "\n";
}
