//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/legendre.hpp>
#include <type_traits>
#include <boost/math/special_functions/legendre.hpp>

TTS_CASE_TPL("Check diff(legendre) return type", EVE_TYPE)
{
    TTS_EXPR_IS(eve::diff(eve::legendre)((unsigned int)(0), T()), T);
}

TTS_CASE_TPL("Check eve::diff(eve::legendre) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T,unsigned>;
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(2u, T{0.5}), T(boost::math::legendre_p_prime(2u, 0.5)), 1.0);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(2u, T{0.1}), T(boost::math::legendre_p_prime(2u, 0.1)), 1.0);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(3u, T{0.5}), T(boost::math::legendre_p_prime(3u, 0.5)), 1.0);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(3u, T{0.1}), T(boost::math::legendre_p_prime(3u, 0.1)), 1.0);

    TTS_ULP_EQUAL(eve::diff(eve::legendre)(i_t(2u), T{0.5}), T(boost::math::legendre_p_prime(2u, 0.5)), 0.5);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(i_t(2u), T{0.1}), T(boost::math::legendre_p_prime(2u, 0.1)), 1.0);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(i_t(3u), T{0.5}), T(boost::math::legendre_p_prime(3u, 0.5)), 0.5);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(i_t(3u), T{0.1}), T(boost::math::legendre_p_prime(3u, 0.1)), 1.0);
    TTS_ULP_EQUAL(eve::diff(eve::legendre)(i_t(5u), T{0.1}), T(boost::math::legendre_p_prime(5u, 0.1)), 1.0);
  }
}
