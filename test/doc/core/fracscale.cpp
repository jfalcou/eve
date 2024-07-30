// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                             
  std::cout << "-> fracscale(wf0, index_t<0>())              = " << eve::fracscale(wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale(wf0, 2*wi)                      = " << eve::fracscale(wf0, 2*wi) << "\n";
  std::cout << "-> fracscale[downward](wf0, index_t<0>())    = " << eve::fracscale[eve::downward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[upward](wf0, index_t<0>())      = " << eve::fracscale[eve::upward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[to_nearest](wf0, index_t<0>())  = " << eve::fracscale[eve::to_nearest](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale[toward_zero](wf0, index_t<0>()) = " << eve::fracscale[eve::toward_zero](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> fracscale(wf, wi1)                        = " << eve::fracscale(wf, wi1) << "\n";
}
