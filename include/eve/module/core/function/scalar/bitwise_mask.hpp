//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_MASK_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/is_nez.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T bitwise_mask_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    using itype = eve::detail::as_integer_t<T>;
    return bitwise_cast<T>(eve::unary_minus(itype(is_nez(a0))));
  }
  
  // -----------------------------------------------------------------------------------------------
  // logical case
  template<typename T>
  EVE_FORCEINLINE constexpr T bitwise_mask_(EVE_SUPPORTS(cpu_), logical<T> const &a0) noexcept
  {
    using itype = eve::detail::as_integer_t<T>;
    return bitwise_cast<T>(unary_minus(itype(is_nez(a0))));
  }

  // -----------------------------------------------------------------------------------------------
  // bool case
  EVE_FORCEINLINE constexpr bool bitwise_mask_(EVE_SUPPORTS(cpu_), bool a0) noexcept
  {
    return a0;
  }
}

#endif
