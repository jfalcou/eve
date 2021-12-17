//#include <eve/function/lambert.hpp>
#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pd = {-1.0, -0.367879441171441, 0.0, -0.2, 0.2, -0.0, 3.0, 100.0};

  auto [w0, wm1] = eve::lambert(pd);
  std::cout << "---- simd" << '\n'
            << "<- pd             = " << pd << '\n'
            << "-> w0             = " << w0 << '\n'
            << "-> wm1            = " << wm1<< '\n';


  float        xf = -0.2f;
  auto [sw0, swm1] = eve::lambert(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> sw0             = " << sw0 << '\n'
            << "-> swm1            = " << swm1<< '\n';
  return 0;
}
