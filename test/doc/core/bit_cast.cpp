// revision 2
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                   = " << wf0 << "\n";
  std::cout << "<- wi0                   = " << wi0 << "\n";
  std::cout << "<- wu0                   = " << wu0 << "\n";

  std::cout << "-> bit_cast(wf0, as(wu)) = " << eve::bit_cast(wf0, eve::as(wu0)) << "\n";
  std::cout << "-> bit_cast(wf0, as(wu0))= " << eve::bit_cast(wf0, eve::as(wu0)) << "\n";
  std::cout << "-> bit_cast(wi0, as(wu0))= " << eve::bit_cast(wi0, eve::as(wu0)) << "\n";
  std::cout << "-> bit_cast(wu0, as(wi0))= " << eve::bit_cast(wu0, eve::as(wi0)) << "\n";
  std::cout << "-> bit_cast(wi0, as(wu0))= " << eve::bit_cast(wi0, eve::as(wu0)) << "\n";
  std::cout << "-> bit_cast(wu, as(wi0)) = " << eve::bit_cast(wu0, eve::as(wi0)) << "\n";
}
