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
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/all.hpp>
#include <eve/function/pedantic/frexp.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <type_traits>
#include <cmath>
#include <array>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of frexp"
            , eve::test::simd::ieee_reals

            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::frexp(T())  , (std::array<T, 2>));
  TTS_EXPR_IS( eve::frexp(v_t()), (std::array<v_t, 2>));
  TTS_EXPR_IS( eve::pedantic(eve::frexp)(T())  , (std::array<T, 2>));
  TTS_EXPR_IS( eve::pedantic(eve::frexp)(v_t()), (std::array<v_t, 2>));
  TTS_EXPR_IS( eve::raw(eve::frexp)(T())  , (std::array<T, 2>));
  TTS_EXPR_IS( eve::raw(eve::frexp)(v_t()), (std::array<v_t, 2>));

  using eve::as;
  using eve::zero;
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::zero(as<T>()));
    TTS_IEEE_EQUAL(r0, (eve::zero(as<T>())));
    TTS_EQUAL     (r1, zero(as<T>()));
    TTS_EXPECT(eve::all(eve::is_positive(r1))   );
  }

  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::mzero(as<T>()));
    TTS_IEEE_EQUAL(r0, (eve::mzero(as<T>())));
    TTS_EQUAL     (r1, zero(as<T>()));
    TTS_EXPECT( eve::all(eve::is_negative(r1) ));
  }
  //==  corner cases
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::nan(as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::nan(as<T>())));
    TTS_EQUAL     (r1, zero(as<T>()));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::inf(as<T>()));
    auto [q0, q1] = eve::pedantic(eve::frexp)(eve::minf(as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(as<T>())));
    TTS_EQUAL     (r1, zero(as<T>()));

    TTS_IEEE_EQUAL(q0, (eve::minf(as<T>())));
    TTS_EQUAL     (q1, zero(as<T>()));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::mindenormal(as<T>()));

    TTS_ULP_EQUAL (r0, T(0.5), 1);
    TTS_EQUAL     (r1, T(eve::minexponent(as<T>())-eve::nbmantissabits(as<T>())+1));
   }
};

//==================================================================================================
// frexp  tests
//==================================================================================================
EVE_TEST( "Check behavior of frexp on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  {
    auto [m, e] = eve::frexp(a0);
    TTS_EQUAL( m, T([&](auto i, auto) { int se(0); return std::frexp(a0.get(i), &se);}));
    TTS_EQUAL( e, T([&](auto i, auto) { int se(0); std::frexp(a0.get(i), &se);  return v_t(se); }));
  }
  {
    auto [m, e] = eve::pedantic(eve::frexp)(a0);
    TTS_EQUAL( m, T([&](auto i, auto) { int se(0); return std::frexp(a0.get(i), &se); }));
    TTS_EQUAL( e, T([&](auto i, auto) { int se(0); std::frexp(a0.get(i), &se);  return v_t(se); }));
  }
  {
    auto [m, e] = eve::raw(eve::frexp)(a0);
    TTS_EQUAL( m, T([&](auto i, auto) { int se(0); return std::frexp(a0.get(i), &se); }));
    TTS_EQUAL( e, T([&](auto i, auto) { int se(0); std::frexp(a0.get(i), &se);  return v_t(se); }));
  }
};
