// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                               = " << wu0 << "\n";
                                                     
  std::cout << "-> byte_reverse(wu0)                 = " << eve::byte_reverse(wu0) << "\n";
  std::cout << "-> byte_reverse[ignore_last(2)](wu0) = " << eve::byte_reverse[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> byte_reverse[wu0 != 2u](wu0)      = " << eve::byte_reverse[wu0 != 2u](wu0) << "\n";
}
