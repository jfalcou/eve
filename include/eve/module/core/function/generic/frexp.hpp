//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED


#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // tagged cases
  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                        , TAG const & tag_
                                        , T const & a0) noexcept
  Requires(std::tuple<T, T>, behave_as<floating_point, T>)
  {
    auto [m, e] = ifrexp(tag_, a0);
    if constexpr(is_Vectorizable_v<T>)
      return  std::tuple<T, T>{m, static_cast<T>(e)};
    else
      return  std::make_tuple(m, convert(e, as<value_type_t<T>>()));
  }
  
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                        , T const & a0) noexcept
  Requires(std::tuple<T, T>, behave_as<floating_point, T>)
  {
    auto [m, e] = ifrexp(a0); 
    if constexpr(is_Vectorizable_v<T>)
      return  std::tuple<T, T>{m, static_cast<T>(e)};
    else
      return  std::make_tuple(m, convert(e, as<value_type_t<T>>()));
  }
}

#endif
