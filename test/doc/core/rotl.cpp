// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  wu0 = ~wu0; 
  eve::wide wu1{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                            = " << wu0 << "\n";
  std::cout << "<- wu1                            = " << wu1 << "\n";

  std::cout << "-> rotl(wu0, wu1)                 = " << eve::rotl(wu0, wu1) << "\n";
  std::cout << "-> rotl[ignore_last(2)](wu0, wu1) = " << eve::rotl[eve::ignore_last(2)](wu0, wu1) << "\n";
  std::cout << "-> rotl[wu0 != 0](wu0, wu1)       = " << eve::rotl[wu0 != 0](wu0, wu1) << "\n";
}
