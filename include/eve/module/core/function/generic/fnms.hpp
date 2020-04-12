//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FNMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FNMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/add.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
#include <type_traits>
#include <eve/concept/compatible.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fnms_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T,U> && compatible_values<T,V>
  {
    return arithmetic_call(fnms, a, b, c);
  }
  
  template<real_value T>
  EVE_FORCEINLINE T fnms_(EVE_SUPPORTS(cpu_)
                         , T const &a
                         , T const &b
                         , T const &c) noexcept
  requires native<T>
  {
    return -a*b-c;
  }
  
  template<real_value T, typename D>
  EVE_FORCEINLINE T fnms_(EVE_SUPPORTS(cpu_)
                         , D const &
                         , T const &a
                         , T const &b
                         , T const &c) noexcept
  requires native<T>
  {
    return -D()(fma)(a, b, c);
  }
}

#endif
