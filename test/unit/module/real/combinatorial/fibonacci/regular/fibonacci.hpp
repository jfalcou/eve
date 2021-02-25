//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fibonacci.hpp>
#include <eve/constant/valmin.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::fibonacci return type", EVE_TYPE)
{
    using i_t = eve::as_integer_t<T, unsigned>;
    using elt_t = eve::element_type_t<T>;
    TTS_EXPR_IS(eve::fibonacci(i_t(), T(), T()), T);
    TTS_EXPR_IS(eve::fibonacci(std::uint8_t(), T(), T()), T);
    TTS_EXPR_IS(eve::fibonacci(i_t(), elt_t(), T()), T);
    TTS_EXPR_IS(eve::fibonacci(i_t(), T(), elt_t()), T);
    TTS_EXPR_IS(eve::fibonacci(i_t(), elt_t(), elt_t()), T);
}

TTS_CASE_TPL("Check eve::fibonacci behavior", EVE_TYPE)
{
    using i_t = eve::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::fibonacci(9u, T(1), T(1)) , T(55));
  TTS_EQUAL(eve::fibonacci(i_t(9), T(1), T(1)) , T(55));

}
