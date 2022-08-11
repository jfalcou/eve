#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi << '\n'
            << " yi                        = " << yi << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi) << '\n'
            << " -> saturated(div(xi, yi)) = " << eve::saturated(eve::div)(xi, yi) << '\n';

  return 0;
}
