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
#include <eve/constant/zero.hpp>
#include <eve/function/arg.hpp>
#include <eve/function/diff/arg.hpp>
#include <eve/function/pedantic/arg.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
auto  types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::arg(T())  , T);
  TTS_EXPR_IS( eve::arg(v_t()), v_t);

  TTS_EXPR_IS( eve::pedantic(eve::arg)(T())  , T);
  TTS_EXPR_IS( eve::pedantic(eve::arg)(v_t()), v_t);

  TTS_EXPR_IS( eve::diff(eve::arg)(T())  , T);
  TTS_EXPR_IS( eve::diff(eve::arg)(v_t()), v_t);
};

EVE_TEST_BED( "Check return types of arg on wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );




//==================================================================================================
// arg tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0
                                )
{
  using v_t = eve::element_type_t<T>;
  using eve::zero;
  using eve::pi;
  using eve::as;
  using eve::arg;
  using eve::pedantic;
  using eve::diff;
  auto ref_arg = [&](auto i, auto) { return a0.get(i) >= 0 ? zero(as(v_t())) : pi(as(v_t())); };
  TTS_IEEE_EQUAL( arg(a0), T(ref_arg));
  TTS_IEEE_EQUAL( pedantic(arg)(a0), T(ref_arg));
  TTS_IEEE_EQUAL( diff(arg)(a0), T(0));
};

EVE_TEST_BED( "Check behavior of arg on wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
            , simd_tests
            );

auto corner_tests = []<typename T>( auto& runtime, bool verbose, auto const&, T)
{
  using eve::pi;
  using eve::zero;
  using eve::as;
  using eve::arg;
  using eve::diff;
  using eve::pedantic;
  // Corners cases
  if constexpr(eve::platform::supports_nans)
  {
    using eve::nan;
    TTS_IEEE_EQUAL(arg(nan(as<T>())), pi(as<T>()));
    TTS_IEEE_EQUAL(arg(-nan(as<T>())), zero(as<T>()));
    TTS_IEEE_EQUAL(pedantic(arg)(nan(as<T>())), nan(as<T>()));
    TTS_IEEE_EQUAL(pedantic(arg)(-nan(as<T>())), nan(as<T>()));
    TTS_IEEE_EQUAL(diff(arg)(nan(as<T>())), zero(as<T>()));
    TTS_IEEE_EQUAL(diff(arg)(-nan(as<T>())), zero(as<T>()));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    using eve::inf;
    using eve::minf;
    TTS_IEEE_EQUAL(arg(minf(as<T>())), pi(as<T>()));
    TTS_IEEE_EQUAL(arg(inf(as<T>())), zero(as<T>()));
    TTS_IEEE_EQUAL(pedantic(arg)(minf(as<T>())), pi(as<T>()));
    TTS_IEEE_EQUAL(pedantic(arg)(inf(as<T>())), zero(as<T>()));
    TTS_IEEE_EQUAL(diff(arg)(minf(as<T>())), zero(as<T>()));
    TTS_IEEE_EQUAL(diff(arg)(inf(as<T>())), zero(as<T>()));
  }

};

EVE_TEST_BED( "Check  with nans and infs"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::no_data)
            , corner_tests
            );
