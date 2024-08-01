// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0 = {-1.0f, 2.3f, 45000.7f, -64768.6f};
  eve::wide wi0 = {-1l, 2l, -3l, eve::valmax(eve::as<std::int64_t>())};


  std::cout << "<- wf0                   = " << wf0 << "\n";
  std::cout << "<- wi0                   = " << wi0 << "\n";

  std::cout << "-> saturate(wf0, as(wu)) = " << eve::saturate(wf0, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wi, as(wu0)) = " << eve::saturate(wi0, eve::as<std::int16_t>()) << "\n";
}
