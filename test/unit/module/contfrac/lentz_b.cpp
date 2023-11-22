//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/contfrac.hpp>

template <class U>
struct obj_const_fraction
{
  U z;
  obj_const_fraction(U v) : z(v){};
  auto operator()() { return z;  }
};

//==================================================================================================
//== lentz_b tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of lentz_b on reals",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, eve::pio_4)
                           ,tts::randoms(1.0, 4.0)
                           )
             )
  <typename T>(T const& z , T const& a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto eps = eve::eps(eve::as<u_t>());
  size_t m = 1000u;
  double tol = sizeof(u_t) == 4 ? 1.0e-4 : 1.0e-7;
  using eve::lentz_b;
  {
    // frac with constant coefs
    auto ref = (a1+eve::sqrt(eve::sqr(a1)+4))/2;
    obj_const_fraction<T> f1(a1);
    TTS_RELATIVE_EQUAL(lentz_b(f1, eps, m), ref, tol);
    auto f2 = [a1](){return a1; };
    TTS_RELATIVE_EQUAL(lentz_b(f2, eps, m), ref, tol);
  }
  {
    // tan test with lambda
    auto ref = eve::tan(z);
    auto a = -eve::sqr(z);
    auto b = eve::mone(eve::as(z));
    auto func1 = [a, &b](){ b+= 2; return kumi::tuple{a, b}; };
    auto f =   eve::lentz_b(func1, eps, m);
    TTS_RELATIVE_EQUAL(z/f, ref, tol);
  }
};
