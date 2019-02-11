//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXTRACT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/function/store.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(simd_),
                             wide<T, N, ABI> const &v0,
                             U const &i) noexcept
  {
    using wide_t =  wide<T, N, ABI>; 
    using result_t = T;
    result_t data[wide_t::static_size];
    eve::store(v0, &data[0]);
    return data[i];
  }


}


#endif
