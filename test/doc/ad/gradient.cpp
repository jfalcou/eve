#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <array>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<float>;


int main()
{
  auto f = [](auto x, auto y,  auto z){
    return eve::fma(x, y, z);
  };

  auto print = [](std::string const & s, auto g){
    std::cout << s << " gradient of f is : {";
    for(int i=0; i < 2 ; ++i)
    {
      std::cout << g[i] << ", ";
    }
    std::cout << g[2] << "}" << '\n'   ;
  };

  {
    float x = 3;
    float y = 1;
    float z = 5;
    // std::array<float, 3>
    auto g = eve::gradient(f, x, y, z);
    std::cout << "---- simd" << '\n'
              << "<- x                                   = " << x << '\n'
              << "<- y                                   = " << y << '\n'
              << "<- z                                   = " << z << '\n';

    print("usual", g);
  }
  {
    auto f = [](auto x, auto y,  auto z){return eve::fma(x, y, z); };
    wide_ft x = {3, 4, 5, 6};
    wide_ft y = {1, 2, 3, 4};
    wide_ft z = {5, 6, 7, 8};
    std::array<wide_ft, 3> g = eve::gradient(f, x, y, z);
    std::cout << "---- simd" << '\n'
              << "<- x                                   = " << x << '\n'
              << "<- y                                   = " << y << '\n'
              << "<- z                                   = " << z << '\n';
    print("usual", g);
    std::array<wide_ft, 3> cg = eve::cyl(eve::gradient)(f, x, y, z);
    print("cylindrcal", cg);
    std::array<wide_ft, 3> sg = eve::sph(eve::gradient)(f, x, y, z);
    print("spherical", sg);

    return 0;
  }
}
