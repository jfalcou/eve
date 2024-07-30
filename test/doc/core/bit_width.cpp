// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                            = " << wu0 << "\n";
                                                  
  std::cout << "-> bit_width(wu0)                 = " << eve::bit_width(wu0) << "\n";
  std::cout << "-> bit_width[ignore_last(2)](wu0) = " << eve::bit_width[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> bit_width[wu0 != 0](wu0)       = " << eve::bit_width[wu0 != 0](wu0) << "\n";
  std::cout << "-> bit_width(wu)                  = " << eve::bit_width(wu) << "\n";
  std::cout << "-> bit_width[ignore_last(2)](wu)  = " << eve::bit_width[eve::ignore_last(2)](wu) << "\n";
  std::cout << "-> bit_width[wu != 0](wu)         = " << eve::bit_width[wu != 0](wu) << "\n";
}
