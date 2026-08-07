// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25,
                  eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> sinh(wf)                = " << eve::sinh(wf) << "\n";
  std::cout << "-> sinh[ignore_last(2)](wf)= " << eve::sinh[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sinh[wf != -2.0f](wf)   = " << eve::sinh[wf != -2.0f](wf) << "\n";
  {
    float const nan = std::numeric_limits<float>::quiet_NaN();
    float buf[8] = {10.f, 0.f, -0.f, nan, 0.5f, 0.5f, 0.5f, 0.5f};
    eve::wide<float> a{&buf[0]};
    std::cout<<a<<std::endl;
    auto r = eve::sinh(a);
    std::cout << r << "\n";
  }
  {
    float buf[8] = {10.f, 0.f, -0.f, 0.f, 0.5f, 0.5f, 0.5f, 0.5f};
    eve::wide<float> a{&buf[0]};
    std::cout<<a<<std::endl;
    auto r = eve::sinh(a);
    std::cout << r << "\n";
  }

}
