//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>
#include <boost/math/complex/asinh.hpp>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of asinh on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 300.0 : 3.5;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::asinh(eve::complex<e_t>(e, f)),  cv(boost::math::asinh(c_t(e, f))), ulp);
    }
  }
};

EVE_TEST( "Check behavior of asinh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-5, 5)
                             , eve::test::randoms(-5, 5))
        )
  <typename T>(T const& a0, T const&  a1)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 300.0 : 2.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_asinh = [](auto x, auto y){return cv(boost::math::asinh(c_t(x, y))); };
  auto init_with_std = [std_asinh](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_asinh(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::asinh(z_t{a0,a1}), init_with_std(a0, a1), ulp);
};

EVE_TEST_TYPES( "Check return types of eve::asinh", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 300.0 : 0.75;
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using eve::as;

  // specific values tests

   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), eve::zero(as<T>()))), c_t(eve::nan (as<T>()), eve::zero(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::one  (as<T>()), eve::inf (as<T>()))), c_t(eve::inf(as<T>()),  eve::pio_2(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), c_t(eve::nan(as<T>()),  eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), c_t(eve::inf (as<T>()), eve::zero(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), eve::pi(as<T>())/4), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::inf (as<T>()), eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::one  (as<T>()), -eve::inf (as<T>()))), c_t(eve::inf(as<T>()),  -eve::pio_2(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::one  (as<T>()), -eve::nan (as<T>()))), c_t(eve::nan(as<T>()),  -eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), -eve::one (as<T>()))), c_t(eve::inf (as<T>()), -eve::zero(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), -eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), -eve::pi(as<T>())/4), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::inf  (as<T>()), -eve::nan(as<T>()))),  c_t(eve::inf (as<T>()), -eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), -eve::one(as<T>()))),  c_t(eve::nan (as<T>()), -eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), -eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), -eve::nan(as<T>())), ulp);
   TTS_ULP_EQUAL(eve::asinh(c_t(eve::nan  (as<T>()), -eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), -eve::nan(as<T>())), ulp);

   TTS_ULP_EQUAL(eve::asinh(c_t(eve::zero(as<T>()),  eve::zero(as<T>()))), c_t(eve::zero(as<T>()), eve::zero(as<T>())), ulp);
};
