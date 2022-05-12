//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST( "Check behavior of horner on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0))
        )
<typename T>(T const& x)
{
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
  std::vector<elt_t> const c0(10, 2.0);
  std::vector<elt_t> c1(c0);
  polynom_t p0(c0);
  std::cout << "p0  "<< p0 << std::endl;
  for(size_t i=0; i <c0.size() ; ++i) std::cout << c0[i] << " ";
  std::cout << std::endl;
  auto z = p0(c0);
  for(size_t i=0; i <c0.size() ; ++i) std::cout << c0[i] << " ";
  std::cout << std::endl;
  for(size_t i=0; i <z.size()  ; ++i) std::cout <<  z[i] << " ";
  std::cout << std::endl;
  for(size_t i=0; i <c1.size()  ; ++i) std::cout <<  c1[i] << " ";
  std::cout << std::endl;
  p0(c1);
  for(size_t i=0; i <c1.size()  ; ++i) std::cout <<  c1[i] << " ";
  std::cout << std::endl;

  std::cout << p0(x) << std::endl;
  std::cout << p0(elt_t(2.0))<< std::endl;

};
