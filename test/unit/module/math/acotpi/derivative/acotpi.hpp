//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/acotpi.hpp>
#include <eve/function/derivative/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(cos) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::acotpi)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::acotpi) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto e = eve::sqrt(eve::eps(eve::as<T>()));
    auto df = [e](auto f, auto x){return (f(x+e)-f(x-e))/(2*e); };
    TTS_ULP_EQUAL(eve::derivative(eve::acotpi)(T{0.25}), df(eve::acotpi, T(0.25))  , ulp);
    std::cout << eve::derivative(eve::acotpi)(T{0.25}) << std::endl;
    std::cout << df(eve::acotpi, T(0.25)) << std::endl;
    TTS_ULP_EQUAL(eve::derivative(eve::acotpi)(T{0}), -eve::invpi(eve::as<T>())        , 0.5);
    TTS_ULP_EQUAL(eve::derivative(eve::acotpi)(T{-0.25}), df(eve::acotpi, T(-0.25)), ulp);
    std::cout << eve::derivative(eve::acotpi)(T{0}) << std::endl;
    std::cout << eve::derivative(eve::acotpi)(-T(0)) << std::endl;
  }
}
