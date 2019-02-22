//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_LOGICAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_LOGICAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_),
                              wide<logical<T>, N, ABI> const &value,
                              logical<T> *ptr) noexcept requires(void, Native<ABI>)
  {
    using type = typename wide<T, N>::storage_type;
    store(wide<T, N>(type(value.storage())), (T *)ptr);
  }

  // -----------------------------------------------------------------------------------------------
  // Aligned case
  template<typename T, typename S, std::size_t N, typename ABI>
  EVE_FORCEINLINE auto
  store_(EVE_SUPPORTS(cpu_),
         wide<logical<T>, S, ABI> const &value,
         aligned_ptr<logical<T>, N>
             ptr) noexcept requires(void, Native<ABI>, If<(wide<T, S, ABI>::static_alignment <= N)>)
  {
    using type = typename wide<T, S>::storage_type;
    store(wide<T, S>(type(value.storage())), aligned_ptr<T, N>((T *)ptr.get()));
  }
}

#endif
