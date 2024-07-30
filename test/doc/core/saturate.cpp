// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wi0                   = " << wi0 << "\n";
  std::cout << "<- wu0                   = " << wu0 << "\n";
                                         
  std::cout << "-> saturate(wf0, as(wu)) = " << eve::saturate(wf0, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wf, as(wu0)) = " << eve::saturate(wf, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wi, as(wu0)) = " << eve::saturate(wi, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wu0, as(wi)) = " << eve::saturate(wu0, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wi0, as(wu)) = " << eve::saturate(wi0, eve::as<std::int16_t>()) << "\n";
  std::cout << "-> saturate(wu, as(wi0)) = " << eve::saturate(wu, eve::as<std::int16_t>()) << "\n";
}
