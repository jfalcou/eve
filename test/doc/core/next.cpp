// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0 = {-0.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f, 30.0f,eve::mindenormal(eve::as<float>()),
                   eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide wi0 = {-1, 2, -3, -4, 327654, 32765, 32766, 32767 };
  eve::wide wu0 = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                       = " << wf0 << "\n";
  std::cout << "<- wi0                       = " << wi0 << "\n";
  std::cout << "<- wu0                       = " << wu0 << "\n";

  std::cout << "-> next(wf0)                 = " << eve::next(wf0) << "\n";
  std::cout << "-> next(wf0, wi1)            = " << eve::next(wf0, wu0) << "\n";
  std::cout << "-> next[ignore_last(2)](wf0) = " << eve::next[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> next[wf0 != 0](wf0)       = " << eve::next[wf0 != 0](wf0) << "\n";
  std::cout << "-> next[pedantic](wf0)       = " << eve::next[eve::pedantic](wf0) << "\n";
  std::cout << "-> next[saturated ](wi0)     = " << eve::next[eve::saturated ](wi0) << "\n";
  std::cout << "-> next(wu0)                 = " << eve::next(wu0) << "\n";
  std::cout << "-> next(wi0)                 = " << eve::next(wi0) << "\n";
  std::cout << "-> next(wi0, wu0)            = " << eve::next(wi0, wu0) << "\n";
}
