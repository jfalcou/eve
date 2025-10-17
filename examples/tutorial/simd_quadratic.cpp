//! [simd-function]
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <array>

int main()
{
  auto print = [](std::string name, auto v){ //utility to print the results
    std::cout << name << " =  {";
    for(std::size_t i=0; i <  v.size(); ++i) std::cout << v[i] << ((i != v.size()-1) ? ", ":"}");
    std::cout << std::endl;
  };

  auto quadratics = [](auto & result,  auto const& aa, auto const& bb, auto const& cc){
    // result will be a zip of two arrays
    auto quad_it = [](auto e){                                               //this is the EVE version of the scalar resolution algorithm above
      auto [aaa, bbb, ccc] = e;                                              // get the coefficients
      auto delta = eve::fnma(4*aaa, ccc, eve::sqr(bbb));                     // compute delta (fnma is the fma version of -a*b+c
      auto rmax = eve::fam(-bbb, -eve::sign(bbb), eve::sqrt(delta))/(2*aaa); // compute the root with maximal abslute value
      auto rmin = eve::if_else(eve::is_eqz(rmax), eve::zero, ccc/(rmax*aaa));// compute the other root (is_eqz(rmax) test for zeroes. Could be `rmax == 0`)
      eve::swap_if(rmin > rmax, rmin, rmax);                                 // order by increasing values
      auto iseqza = eve::is_eqz(aaa);
      rmin = eve::if_else(eve::is_eqz(aaa), -ccc/bbb, rmin);                 // first degree aaa is zero first root is -ccc/bbb
      rmax = eve::if_else(eve::is_eqz(aaa), eve::nan, rmax);                 // first degree aaa is zero second root is nan
      return eve::zip(rmin, rmax);                                           // return properly typed values (always use zip to return multiple values)
    };
    // the algo transform_to takes care of using simd chunks to use quad_it
    // the input vector size need not be a multiple of (the automagically chosen) best SIMD vector size
    eve::algo::transform_to(eve::algo::views::zip(aa, bb, cc), result, quad_it);
  };

  using a_t = std::array<double, 11>;

  a_t a{5.0,  12.0,  6.0,  7.0, 1.0, 1.0,   1.0,   1.0, 1.0e-20, 0.0, 1.0};
  a_t b{3.0,   1.0,  4.0, -2.0, 2.0, 1.0,   1.0,   1.0, 1.0e20,  1.0, 2.0};
  a_t c{-1.0, -5.0, -6.0, -6.0, 5.0, 30.0, 35.0, -40.0, -1.0,   -1.0, 1.0};
  a_t rmin, rmax;
  auto r = eve::views::zip(rmin, rmax); //prepare container view for the results
  quadratics(r, a, b, c);
  print("a   ", a);
  print("b   ", b);
  print("c   ", c);
  print("rmin", rmin);
  print("rmax", rmax);
}
//! [simd-function]
