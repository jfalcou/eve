// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                                        = " << wu0 << "\n";
                                                              
  std::cout << "-> all(wu0 <= maximum(wu0)/2)                 = " << eve::all(wu0 <= eve::maximum(wu0)/2) << "\n";
  std::cout << "-> all[ignore_last(2)](wu0 <= maximum(wu0)/2) = " << eve::all[eve::ignore_last(2)](wu0 <= eve::maximum(wu0)/2) << "\n";
}
