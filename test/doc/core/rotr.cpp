// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wu0                            = " << wu0 << "\n";
  std::cout << "<- wu1                            = " << wu1 << "\n";

  std::cout << "-> rotr(wu0, wu1)                 = " << eve::rotr(wu0, wu1) << "\n";
  std::cout << "-> rotr[ignore_last(2)](wu0, wu1) = " << eve::rotr[eve::ignore_last(2)](wu0, wu1) << "\n";
  std::cout << "-> rotr[wu0 != 0](wu0, wu1)       = " << eve::rotr[wu0 != 0](wu0, wu1) << "\n";
}
