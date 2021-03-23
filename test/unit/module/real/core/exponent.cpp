//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/exponent.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of exponent on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as_<T>)
{
  using r_t = eve::as_integer_t<T>;
  TTS_EXPR_IS( eve::exponent(T())  , r_t);
};


//==================================================================================================
// exponent tests
//==================================================================================================
EVE_TEST( "Check behavior of exponent on wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
            )
<typename T>( T const& a0 )
{
  using r_t = eve::as_integer_t<T>;
  using eve::exponent;

  auto ref_exponent = [&](auto i, auto) { int e; std::frexp(a0.get(i), &e); return e-1; };
  TTS_EQUAL( exponent(a0), r_t(ref_exponent));
};

//==================================================================================================
// corner tests
//==================================================================================================
EVE_TEST_TYPES( "Check  with nans and infs"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as_<T>)
{
  using eve::as;
  using eve::exponent;
  using eve::zero;
  using r_t = eve::as_integer_t<T>;
  // Corners cases
  if constexpr(eve::platform::supports_nans)
  {
    using eve::nan;
    TTS_EQUAL(exponent(nan(as<T>())), zero(as<r_t>()));
    TTS_EQUAL(exponent(-nan(as<T>())), zero(as<r_t>()));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    using eve::inf;
    using eve::minf;
    TTS_EQUAL(exponent(minf(as<T>())), zero(as<r_t>()));
    TTS_EQUAL(exponent(inf(as<T>())), zero(as<r_t>()));
  }
};
