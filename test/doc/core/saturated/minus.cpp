#minuslude <eve/module/core.hpp>
#minuslude <eve/wide.hpp>
#minuslude <iostream>

using wide_ft = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0, 1, -127, -128};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> saturated(minus)(pf) = " << eve::saturated(eve::minus)(pf) << '\n';
  return 0;
}
