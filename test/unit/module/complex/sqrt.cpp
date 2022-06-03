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
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of sqrt on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::sqrt(eve::complex<e_t>(e, f)),  cv(std::sqrt(c_t(e, f))), 2);
    }
  }
};

EVE_TEST( "Check behavior of sqrt on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t =  eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_sqrt = [](auto x, auto y){return cv(std::sqrt(c_t(x, y))); };
  auto init_with_std = [std_sqrt](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_sqrt(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::sqrt(z_t{a0,a1}), init_with_std(a0, a1), 2);
};


EVE_TEST( "Check behavior of pedantic(sqrt) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
 using e_t = typename T::value_type;
 using ce_t = eve::complex<e_t>;
 using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;
 using c_t = std::complex<e_t>;
  z_t b;
  for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
  {
    ce_t z = cv(std::sqrt(c_t(a0.get(i), a1.get(i))));
    b.set(i, z);
  }
  TTS_ULP_EQUAL(eve::pedantic(eve::sqrt)(z_t{a0,a1}), b, 2.0);
};

EVE_TEST_TYPES( "Check return types of eve::sqrt", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using eve::as;
  // specific values tests
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()))), c_t(eve::inf(as<T>())), 0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),eve::zero(as<T>()))), c_t(eve::zero(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan(as<T>()),eve::nan(as<T>()))),c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()),eve::nan(as<T>()))),c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()))), c_t(0, eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan (as<T>()),eve::inf(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()), eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()), eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan (as<T>()),eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),eve::one(as<T>()))), c_t(eve::zero(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),eve::mone(as<T>()))),c_t(eve::zero(as<T>()),eve::minf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()),eve::nan(as<T>()))),  c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan(as<T>()),eve::one(as<T>()))),  c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan(as<T>()),eve::nan(as<T>()))),  c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()), -eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()), -eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),-eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan (as<T>()),-eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),-eve::one(as<T>()))), c_t(eve::zero(as<T>()),-eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::minf(as<T>()),-eve::mone(as<T>()))),c_t(eve::zero(as<T>()),-eve::minf(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::inf(as<T>()), -eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan(as<T>()), -eve::one(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan(as<T>()), -eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::nan (as<T>()),-eve::inf(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()), eve::nan(as<T>()))), c_t(eve::nan(as<T>()),-eve::nan(as<T>())),0.5);

  auto psqrt =  eve::pedantic(eve::sqrt);
  TTS_ULP_EQUAL(psqrt(c_t(eve::inf(as<T>()),eve::inf(as<T>()))),c_t(eve::inf(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::zero(as<T>()),eve::inf(as<T>()))),c_t(eve::inf(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::nan(as<T>()),eve::zero(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::one(as<T>()), eve::inf(as<T>()))), c_t(eve::inf(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::inf(as<T>()), eve::inf(as<T>()))), c_t(eve::inf(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::minf(as<T>()),eve::inf(as<T>()))), c_t(eve::inf(as<T>()),eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::inf(as<T>()), -eve::inf(as<T>()))), c_t(eve::inf(as<T>()),-eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::minf(as<T>()),-eve::inf(as<T>()))), c_t(eve::inf(as<T>()),-eve::inf(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::one(as<T>()),eve::nan(as<T>()))), c_t(eve::nan(as<T>()),eve::nan(as<T>())),0.5);
  TTS_ULP_EQUAL(psqrt(c_t(eve::one(as<T>()),eve::zero(as<T>()))), c_t(eve::one(as<T>()),eve::zero(as<T>())),0.5);



  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()), -eve::inf(as<T>()))), c_t(eve::inf(as<T>()),-eve::inf(as<T>())),0.5);

  TTS_ULP_EQUAL(eve::sqrt(c_t(1)), c_t(1), 0);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::mone(as<T>()))), c_t(0, eve::one(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::one(as<T>()))), c_t(eve::one(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::zero(as<T>()))), c_t(eve::zero(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::zero(as<T>()),eve::zero(as<T>()))), c_t(eve::zero(as<T>()),eve::zero(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(eve::mzero(as<T>()),eve::zero(as<T>()))),c_t(eve::zero(as<T>()),eve::zero(as<T>())),0.5);
  TTS_ULP_EQUAL(eve::sqrt(c_t(0, 2)), c_t(1, 1), 1);
  for(T i=-5; i <=  T(5) ; i+= T(0.6))
  {
    for(T j =-5; j < T(5); j+= T(0.5))
    {
      TTS_ULP_EQUAL(eve::sqr(eve::sqrt(c_t(i, j))), c_t(i, j), 30.0);
    }
  }
   TTS_ULP_EQUAL(eve::sqrt(c_t(-4)), c_t(0, 2), 0);
   TTS_ULP_EQUAL(eve::sqrt(T(-4)), eve::nan(as<T>()), 0);
//  TTS_ULP_EQUAL(eve::cmplx(eve::sqrt)(T(-4)), c_t(0, 2), 0);

};
