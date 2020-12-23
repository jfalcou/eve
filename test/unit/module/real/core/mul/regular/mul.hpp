//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/derivative/mul.hpp>

#include <type_traits>

TTS_CASE_TPL("Check eve::mul return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::mul(T()  , T()   ), T);
  TTS_EXPR_IS(eve::mul(v_t(), T()   ), T);
  TTS_EXPR_IS(eve::mul(T()  , v_t() ), T);
}

TTS_CASE_TPL("Check eve::mul behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::mul(T( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::mul(T( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::mul(T(12), T(4)), (T(48 )));

  TTS_EQUAL(eve::mul(v_t( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::mul(v_t( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::mul(v_t(12), T(4)), (T(48 )));

  TTS_EQUAL(eve::mul(T( 0), v_t(1)), (T(0  )));
  TTS_EQUAL(eve::mul(T( 1), v_t(1)), (T(1  )));
  TTS_EQUAL(eve::mul(T(12), v_t(4)), (T(48 )));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::mul(T(-1), T(1)) , (T(-1)));
    TTS_EQUAL(eve::mul(T(-6), T(-2)), (T(12)));

    TTS_EQUAL(eve::mul(v_t(-1), T(1)) , (T(-1)));
    TTS_EQUAL(eve::mul(v_t(-6), T(-2)), (T(12)));

    TTS_EQUAL(eve::mul(T(-1), v_t(1)) , (T(-1)));
    TTS_EQUAL(eve::mul(T(-6), v_t(-2)), (T(12)));
  }
  if constexpr(eve::floating_real_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    std::cout << eve::derivative_1st(eve::mul)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::derivative_3rd(eve::mul)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::derivative_<3>(eve::mul)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::derivative_<6>(eve::mul)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::derivative_<4>(eve::mul)(v_t(1), T(2), T(3), T(4), T(5)) << std::endl;
  }
}
