//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/csch.hpp>
#include <eve/function/derivative/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(csch) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::csch)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::csch) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto e = eve::sqrt(eve::eps(eve::as<T>()));
    auto df = [e](auto f, auto x){return (f(x+e)-f(x-e))/(2*e); };
    TTS_ULP_EQUAL(eve::derivative(eve::csch)(T{2.0}), df(eve::csch, T(2.0))  , ulp);
    std::cout << eve::derivative(eve::csch)(T{2.0}) << std::endl;
    std::cout << df(eve::csch, T(2.0)) << std::endl;
    TTS_ULP_EQUAL(eve::derivative(eve::csch)(T{1}), df(eve::csch, T(1.0))  , ulp);
  }
}
