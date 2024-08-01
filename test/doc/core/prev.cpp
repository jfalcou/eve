// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0 = {-0.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f, 30.0f,eve::mindenormal(eve::as<float>()),
                   eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide wi0 = {-1, 2, -3, -4,  -32765, -32766, -32767, -32768 };
  eve::wide wu0 = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                       = " << wf0 << "\n";
  std::cout << "<- wi0                       = " << wi0 << "\n";
  std::cout << "<- wu0                       = " << wu0 << "\n";

  std::cout << "-> prev(wf0)                 = " << eve::prev(wf0) << "\n";
  std::cout << "-> prev(wf0, wi1)            = " << eve::prev(wf0, wu0) << "\n";
  std::cout << "-> prev[ignore_last(2)](wf0) = " << eve::prev[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> prev[wf0 != 0](wf0)       = " << eve::prev[wf0 != 0](wf0) << "\n";
  std::cout << "-> prev[pedantic](wf0)       = " << eve::prev[eve::pedantic](wf0) << "\n";
  std::cout << "-> prev[saturated ](wi0)     = " << eve::prev[eve::saturated ](wi0) << "\n";
  std::cout << "-> prev(wu0)                 = " << eve::prev(wu0) << "\n";
  std::cout << "-> prev(wi0)                 = " << eve::prev(wi0) << "\n";
  std::cout << "-> prev(wi0, wu0)            = " << eve::prev(wi0, wu0) << "\n";
}
