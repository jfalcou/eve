// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf0( [](auto i, auto) { return 1.2345678+i; } );
  eve::wide<std::uint32_t>  wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                                       = " << wf0 << "\n";
  std::cout << "<- wu0                                       = " << wu0 << "\n";

  std::cout << "-> roundscale(wf0, index_t<0>())              = " << eve::roundscale(wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale(wf0, 2*wi)                      = " << eve::roundscale(wf0, wu0) << "\n";
  std::cout << "-> roundscale[downward](wf0, index_t<0>())    = " << eve::roundscale[eve::downward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[upward](wf0, index_t<0>())      = " << eve::roundscale[eve::upward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[to_nearest](wf0, index_t<0>())  = " << eve::roundscale[eve::to_nearest](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[toward_zero](wf0, index_t<0>()) = " << eve::roundscale[eve::toward_zero](wf0, eve::index_t<0>()) << "\n";
}
