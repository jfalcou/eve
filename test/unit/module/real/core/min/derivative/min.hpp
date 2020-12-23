//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/min.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(min) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::min)(T(), T()), T);
    TTS_EXPR_IS(eve::derivative(eve::min)(T(), T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::min) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::min)(T{2},T{3}), T(1));
    TTS_EQUAL(eve::derivative_2nd(eve::min)(T{2},T{3}), T(0));
    TTS_EQUAL(eve::derivative_1st(eve::min)(T{4},T{3}), T(0));
    TTS_EQUAL(eve::derivative_2nd(eve::min)(T{4},T{3}), T(1));
    using v_t = eve::element_type_t<T>;
    std::cout << eve::derivative_1st(eve::min)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::derivative_3rd(eve::min)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::deriv<3>(eve::min)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::deriv<6>(eve::min)(T(1), T(2), T(3), T(4), T(5)) << std::endl;
    std::cout << eve::deriv<4>(eve::min)(v_t(1), T(3), T(3), T(1), T(5)) << std::endl;
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
