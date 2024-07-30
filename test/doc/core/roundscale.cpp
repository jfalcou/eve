// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                              
  std::cout << "-> roundscale(wf0, index_t<0>())              = " << eve::roundscale(wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale(wf0, 2*wi)                      = " << eve::roundscale(wf0, 2*wi) << "\n";
  std::cout << "-> roundscale[downward](wf0, index_t<0>())    = " << eve::roundscale[eve::downward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[upward](wf0, index_t<0>())      = " << eve::roundscale[eve::upward](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[to_nearest](wf0, index_t<0>())  = " << eve::roundscale[eve::to_nearest](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale[toward_zero](wf0, index_t<0>()) = " << eve::roundscale[eve::toward_zero](wf0, eve::index_t<0>()) << "\n";
  std::cout << "-> roundscale(wf, wi1)                        = " << eve::roundscale(wf, wi1) << "\n";
}
