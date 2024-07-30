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
                                             
  std::cout << "-> prev(wf0)                 = " << eve::prev(wf0) << "\n";
  std::cout << "-> prev(wf0, 2*wi)           = " << eve::prev(wf0, 2*wi) << "\n";
  std::cout << "-> prev[ignore_last(2)](wf0) = " << eve::prev[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> prev[wf0 != 0](wf0)       = " << eve::prev[wf0 != 0](wf0) << "\n";
  std::cout << "-> prev[pedantic](wf0)       = " << eve::prev[eve::pedantic](wf0) << "\n";
  std::cout << "-> prev[saturated ](wf0)     = " << eve::prev[eve::saturated ](wf0) << "\n";
  std::cout << "-> prev(wu0)                 = " << eve::prev(wu0) << "\n";
  std::cout << "-> prev(wu0, 2*wi)           = " << eve::prev(wu0, 2*wi) << "\n";
  std::cout << "-> prev(wi0)                 = " << eve::prev(wi0) << "\n";
  std::cout << "-> prev(wf, wi1)             = " << eve::prev(wf, wi1) << "\n";
  std::cout << "-> prev(wi0, wi1)            = " << eve::prev(wi0, wi1) << "\n";
  std::cout << "-> prev(wu, wi1)             = " << eve::prev(wu, wi1) << "\n";
}
