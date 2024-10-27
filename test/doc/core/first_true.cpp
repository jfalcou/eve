// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                                                      = " << wu0 << "\n";

  std::cout << "-> first_true(wu0 >= maximum(wu0)/2)                        = " << *eve::first_true(wu0 >= eve::maximum(wu0)/2) << "\n";
  std::cout << "-> first_true[ignore_first(4)](wu0 <= maximum(wu0)/2 >  1u) = " << *eve::first_true[eve::ignore_first(4)](wu0 > 1u) << "\n";
}
