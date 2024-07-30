// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                         
  std::cout << "-> bit_select(wl, wu, 0) = " << eve::bit_select(wl, wu, ~0u) << "\n";
  std::cout << "-> bit_select(wl, wi, 0) = " << eve::bit_select(wl, wi, -1) << "\n";
}
