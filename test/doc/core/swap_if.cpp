#include <eve/wide.hpp>
#include <iostream>


int main()
{
  eve::wide<float, eve::fixed<4>> a = {1.2f, 3.4f, 5.6f, 7.8f};
  eve::wide<float, eve::fixed<4>> b = {0.1f,1e-2f,1e-3f,1e-4f};

  std::cout << "Before swap_if(a < 4.f,a,b)\n"
            << "<- a                    = " << a << '\n'
            << "<- b                    = " << b << '\n'
            << "<- a < 4.f              = " << (a < 4.f) << "\n\n";

            eve::swap_if(a < 4.f,a,b);

  std::cout << "After swap_if(a < 4.f,a,b)\n"
            << "-> a                    = " << a << '\n'
            << "-> b                    = " << b << '\n';

  return 0;
}
