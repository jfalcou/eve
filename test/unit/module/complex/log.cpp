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

EVE_TEST( "Check behavior of log on scalar"
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
      TTS_ULP_EQUAL(eve::log(eve::complex<e_t>(e, f)),  cv(std::log(c_t(e, f))), 2);
      TTS_ULP_EQUAL(eve::log(eve::complex<e_t>(e, f)),  cv(std::log(c_t(e, f))), 2.0);
    }
  }
};

EVE_TEST( "Check behavior of log on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return cv(std::log(c_t(x, y))); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::log(z_t{a0,a1}), init_with_std(a0, a1), 2);
};

// EVE_TEST_TYPES( "Check return types of eve::log", eve::test::scalar::ieee_reals)
//   <typename T>(eve::as<T>)
// {
//   using eve::as;
//   using e_t = eve::element_type_t<T>;
//   using c_t = eve::complex<e_t>;

//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), eve::mone(as<T>()))), c_t(eve::inf(as<T>()), -eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf(as<T>()), 0)), c_t(eve::inf(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf(as<T>()), 0)), c_t(eve::inf(as<T>()), eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan(as<T>()), eve::nan(as<T>()))),  c_t(eve::nan(as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), eve::zero(as<T>()))),  c_t(eve::inf(as<T>()), eve::zero(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), eve::zero(as<T>()))),  c_t(eve::inf(as<T>()), eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), eve::zero(as<T>()))),  c_t(eve::inf (as<T>()), eve::zero (as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::one  (as<T>()), eve::inf (as<T>()))), c_t(eve::inf(as<T>()), eve::pio_2(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), c_t(eve::nan(as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), c_t(eve::inf(as<T>()), eve::zero(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), eve::one(as<T>()))),  c_t(eve::inf(as<T>()), eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), c_t(eve::inf (as<T>()), eve::zero (as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), eve::mone(as<T>()))), c_t(eve::nan (as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::one  (as<T>()), -eve::inf (as<T>()))), c_t(eve::inf(as<T>()), -eve::pio_2(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::one  (as<T>()), -eve::nan (as<T>()))), c_t(eve::nan(as<T>()), -eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), -eve::one (as<T>()))), c_t(eve::inf(as<T>()), -eve::zero(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), -eve::one(as<T>()))),  c_t(eve::inf(as<T>()), -eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), -eve::one (as<T>()))), c_t(eve::inf (as<T>()), -eve::zero (as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), -eve::one(as<T>()))),  c_t(eve::nan (as<T>()), -eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), -eve::mone(as<T>()))), c_t(eve::nan (as<T>()), -eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), -eve::nan(as<T>()))),  c_t(eve::nan (as<T>()), -eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan(as<T>()), eve::zero(as<T>()))),  c_t(eve::nan(as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::zero(as<T>()))), c_t(eve::minf(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::zero(as<T>()),  eve::zero(as<T>()))),  c_t(eve::minf(as<T>()), eve::zero(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), 3*eve::pio_4(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), eve::pi(as<T>())/4), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), -eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), -3*eve::pio_4(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::inf  (as<T>()), -eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), -eve::pi(as<T>())/4), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::mzero(as<T>()))), c_t(eve::minf(as<T>()), eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::nan  (as<T>()), -eve::inf(as<T>()))),  c_t(eve::inf (as<T>()), -eve::nan(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::minf (as<T>()), eve::nan(as<T>()))),  c_t(eve::inf (as<T>()), eve::nan(as<T>())), 0.5);

//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::mone(as<T>()))), c_t(eve::zero(as<T>()), eve::pi(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::one(as<T>()))), c_t(eve::zero(as<T>())), 0.5);
//   TTS_ULP_EQUAL(eve::pedantic(eve::log)(c_t(eve::zero(as<T>()), eve::one(as<T>()))),c_t(eve::zero(as<T>()), eve::pio_2(as<T>())), 0.5);

//   TTS_ULP_EQUAL(eve::log(c_t(-4)), c_t(eve::log(T(4)), eve::pi(as<T>())), 0);
//   TTS_ULP_EQUAL(eve::log(T(-4)), eve::nan(as<T>()), 0);
// // TTS_ULP_EQUAL(eve::cmplx(eve::log)(T(-4)), c_t(eve::log(T(4)), eve::pi(as<T>())), 0);
// };
