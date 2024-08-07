// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f);
  wf0+= 1.2345678;
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                                       = " << wf0 << "\n";
  std::cout << "<- wu0                                       = " << wu0 << "\n";

  std::cout << "-> fracscale(wf0, index_t<0>())              = " << eve::fracscale(wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale(wf0, 2*wi)                      = " << eve::fracscale(wf0, wu0) << "\n";
  std::cout << "-> fracscale[downward](wf0, index_t<0>())    = " << eve::fracscale[eve::downward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[upward](wf0, index_t<0>())      = " << eve::fracscale[eve::upward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[to_nearest](wf0, index_t<0>())  = " << eve::fracscale[eve::to_nearest](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[toward_zero](wf0, index_t<0>()) = " << eve::fracscale[eve::toward_zero](wf0, eve::index_t<0>()) << "\n";
}
