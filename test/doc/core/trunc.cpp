// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                        = " << wf0 << "\n";
  std::cout << "<- wi0                        = " << wi0 << "\n";
  std::cout << "<- wu0                        = " << wu0 << "\n";
                                              
  std::cout << "-> trunc(wf0)                 = " << eve::trunc(wf0) << "\n";
  std::cout << "-> trunc[ignore_last(2)](wf0) = " << eve::trunc[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> trunc[wf0 != 0](wf0)       = " << eve::trunc[wf0 != 0](wf0) << "\n";
  std::cout << "-> trunc[almost](wf0)         = " << eve::trunc[eve::almost](wf0) << "\n";
  std::cout << "-> trunc[raw2](wf0)            = " << eve::trunc[eve::raw2](wf0) << "\n";
  std::cout << "-> trunc(wu0)                 = " << eve::trunc(wu0) << "\n";
  std::cout << "-> trunc[ignore_last(2)](wu0) = " << eve::trunc[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> trunc[wu0 != 0](wu0)       = " << eve::trunc[wu0 != 0](wu0) << "\n";
  std::cout << "-> trunc(wi0)                 = " << eve::trunc(wi0) << "\n";
  std::cout << "-> trunc[ignore_last(2)](wi0) = " << eve::trunc[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> trunc[wi0 != 0](wi0)       = " << eve::trunc[wi0 != 0](wi0) << "\n";
}
