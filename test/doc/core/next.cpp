// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                       = " << wf0 << "\n";
  std::cout << "<- wi0                       = " << wi0 << "\n";
  std::cout << "<- wi1                       = " << wi1 << "\n";
  std::cout << "<- wu0                       = " << wu0 << "\n";
                                             
  std::cout << "-> next(wf0)                 = " << eve::next(wf0) << "\n";
  std::cout << "-> next(wf0, 2*wi)           = " << eve::next(wf0, 2*wi) << "\n";
  std::cout << "-> next[ignore_last(2)](wf0) = " << eve::next[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> next[wf0 != 0](wf0)       = " << eve::next[wf0 != 0](wf0) << "\n";
  std::cout << "-> next[pedantic](wf0)       = " << eve::next[eve::pedantic](wf0) << "\n";
  std::cout << "-> next[saturated ](wf0)     = " << eve::next[eve::saturated ](wf0) << "\n";
  std::cout << "-> next(wu0)                 = " << eve::next(wu0) << "\n";
  std::cout << "-> next(wu0, 2*wi)           = " << eve::next(wu0, 2*wi) << "\n";
  std::cout << "-> next(wi0)                 = " << eve::next(wi0) << "\n";
  std::cout << "-> next(wf, wi1)             = " << eve::next(wf, wi1) << "\n";
  std::cout << "-> next(wi0, wi1)            = " << eve::next(wi0, wi1) << "\n";
  std::cout << "-> next(wu, wi1)             = " << eve::next(wu, wi1) << "\n";
}
