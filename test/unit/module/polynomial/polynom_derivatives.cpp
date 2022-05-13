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
EVE_TEST_TYPES( "Check behavior of derivative"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    polynom_t p0(c0);
    polynom_t der = p0;
    for(size_t i=0; i < 8u; ++i)
    {
      der = eve::derivative(der);
      eve::inplace(eve::derivative)(p0);
      TTS_EXPECT(der == p0);
    }
  } else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of derivative(p, m)"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    polynom_t p0(c0);
    polynom_t der = p0;
    for(size_t i=0; i < 8u; ++i)
    {
      der = eve::derivative(der);
      std::cout << i << " -> der " << der << std::endl;
      auto derb =  eve::derivative(p0, i+1);
      TTS_EXPECT(der == derb);
    }
  } else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of derivative(p, m, all_)"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    polynom_t p0(c0);
    polynom_t der = p0;
    auto ders = eve::derivative(p0, 7, eve::all);
    for(size_t i=0; i < 8u; ++i)
    {
      der = eve::derivative(der);
      std::cout << i << " -> der " << der << std::endl;
      TTS_EXPECT(der == der[i+1]);
    }
  } else TTS_PASS("");
};
