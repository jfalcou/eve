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

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of acos on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib_type() == spy::libcpp_) ? 100.0 : 2.0;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::acos(eve::complex<e_t>(e, f)),  cv(std::acos(c_t(e, f))), ulp);
    }
  }
};

EVE_TEST( "Check behavior of acos on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-5, 5)
                             , eve::test::randoms(-5, 5))
        )
  <typename T>(T const& a0, T const&  a1)
{
  auto ulp = (spy::stdlib_type() == spy::libcpp_) ? 100.0 : 2.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_acos = [](auto x, auto y){return std::acos(c_t(x, y)); };
  auto init_with_std = [std_acos](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_acos(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::acos(z_t{a0,a1}), init_with_std(a0, a1), ulp);
};


EVE_TEST_TYPES( "Check return types of eve::exp", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  auto ulp = (spy::stdlib_type() == spy::libcpp_) ? 100.0 : 2.5;
   using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using s_t = std::complex<e_t>;
  using eve::as;
  using eve::acos;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan (as<T>()),  eve::zero(as<T>()))), c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  c_t(eve::nan (as<T>()), -eve::inf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::zero (as<T>()), eve::nan (as<T>()))), c_t(eve::pio_2(as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), c_t(eve::nan(as<T>()),  eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::minf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::inf (as<T>()))), c_t(eve::pio_2(as<T>()), -eve::inf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), c_t(eve::zero(as<T>()), eve::minf (as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::inf(as<T>()))),  c_t(eve::pio_4(as<T>()), eve::minf (as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::one(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::inf(as<T>()))),  c_t(eve::nan (as<T>()), -eve::inf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::zero (as<T>()), eve::nan (as<T>()))), c_t(eve::pio_2(as<T>()), eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::one  (as<T>()), eve::nan (as<T>()))), c_t(eve::nan(as<T>()),  eve::nan(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::minf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::one  (as<T>()), eve::inf (as<T>()))), c_t(eve::pio_2(as<T>()), eve::minf(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf  (as<T>()), eve::one (as<T>()))), c_t(eve::pi(as<T>()), -eve::inf (as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf  (as<T>()), eve::inf(as<T>()))),  c_t(T(3)*eve::pio_4(as<T>()), eve::minf (as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  cv(std::acos(s_t(eve::nan  (as<T>()), eve::one(as<T>())))),  ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  cv(std::acos(s_t(eve::nan  (as<T>()), eve::inf(as<T>())))),  ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  cv(std::acos(s_t(eve::nan  (as<T>()), eve::nan(as<T>())))),  ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::zero (as<T>()), eve::nan (as<T>()))), cv(std::acos(s_t(eve::zero (as<T>()), eve::nan (as<T>())))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), cv(std::acos(s_t(eve::one  (as<T>()), eve::nan (as<T>())))), ulp);


 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::inf (as<T>()))), cv(std::acos(s_t(eve::one  (as<T>()), eve::inf (as<T>())))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), cv(std::acos(s_t(eve::inf  (as<T>()), eve::one (as<T>())))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::inf(as<T>()))),  cv(std::acos(s_t(eve::inf  (as<T>()), eve::inf(as<T>())))),  ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::one(as<T>()))), cv(std::acos(s_t(-eve::nan  (as<T>()), eve::one(as<T>())))),    ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::inf(as<T>()))), cv(std::acos(s_t(-eve::nan  (as<T>()), eve::inf(as<T>())))),    ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::nan  (as<T>()), eve::nan(as<T>()))), cv(std::acos(s_t(-eve::nan  (as<T>()), eve::nan(as<T>())))),    ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::one  (as<T>()), eve::inf (as<T>()))),cv(std::acos(s_t(-eve::one  (as<T>()), eve::inf (as<T>())))),   ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf  (as<T>()), eve::one (as<T>()))),cv(std::acos(s_t(-eve::inf  (as<T>()), eve::one (as<T>())))),   ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf (as<T>()), eve::inf(as<T>()))),  cv(std::acos(s_t(-eve::inf  (as<T>()), eve::inf(as<T>())))),   ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::one  (as<T>()), eve::nan (as<T>()))),cv(std::acos(s_t(-eve::one  (as<T>()), eve::nan (as<T>())))),   ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::zero (as<T>()), eve::nan (as<T>()))),cv(std::acos(s_t(-eve::zero (as<T>()), eve::nan (as<T>())))),   ulp);

 TTS_ULP_EQUAL(eve::acos(c_t(eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan(as<T>()), eve::minf   (as<T>())),   ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(-eve::inf (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan(as<T>()), eve::minf   (as<T>())),   ulp);


#endif
 TTS_ULP_EQUAL(eve::acos(c_t(eve::zero(as<T>()),  eve::zero(as<T>()))), c_t(eve::pio_2(as<T>()), eve::zero(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::mzero(as<T>()),  eve::zero(as<T>()))), c_t(eve::pio_2(as<T>()), eve::zero(as<T>())), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::one (as<T>()))),   c_t(0.904556894302381, -1.061275061905036), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::one  (as<T>()), eve::mone (as<T>()))),  c_t(0.904556894302381,  1.061275061905036), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::mone  (as<T>()), eve::one (as<T>()))),  c_t(2.237035759287412, -1.061275061905036), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(eve::mone  (as<T>()), eve::mone (as<T>()))), c_t(2.237035759287412,  1.061275061905036), ulp);

 TTS_ULP_EQUAL(eve::acos(c_t(0.5, -0.5)),  cv(std::acos(s_t(0.5, -0.5))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(1, 1)),       cv(std::acos(s_t(1, 1))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(1, 10)),      cv(std::acos(s_t(1, 10))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(10, 10)),     cv(std::acos(s_t(10, 10))), ulp);
 TTS_ULP_EQUAL(eve::acos(c_t(10, 1)),      cv(std::acos(s_t(10, 1))), ulp);
};
