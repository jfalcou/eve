//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N, emulated_> const &value, T *ptr) noexcept
  {
    apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
  }

  template<typename T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N, aggregated_> const &value, T *ptr) noexcept
  {
    using str_t = typename wide<T, N, aggregated_>::storage_type;
    value.storage().apply ( [&](auto&... v)
                            {
                              int k = 0;
                              (( store(v, ptr+k), k+=str_t::small_size),...);
                            }
                          );
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &value, logical<T> *ptr) noexcept
  {
    store(bitwise_cast(value,as_<wide<T, N, ABI>>{}), (T *)(ptr));
  }

  // -----------------------------------------------------------------------------------------------
  // Aligned case
  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_),
         wide<T, S, emulated_> const &value,
         aligned_ptr<T, N>            ptr,
         std::enable_if_t<(wide<T, S, emulated_>::static_alignment <= N)> * = 0) noexcept
  {
    store(value, ptr.get());
  }

  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_),
         wide<T, S, aggregated_> const &value,
         aligned_ptr<T, N>              ptr,
         std::enable_if_t<(wide<T, S, aggregated_>::static_alignment <= N)> * = 0) noexcept
  {
    using str_t = typename wide<T, S, aggregated_>::storage_type;
    value.storage().apply ( [&](auto&... v)
                            {
                              int k = 0;
                              (( store(v, ptr+k), k+=str_t::small_size),...);
                            }
                          );
  }

  template<typename T, typename S, std::size_t N, typename ABI>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_),
         logical<wide<T, S, ABI>> const &value,
         aligned_ptr<logical<T>, N>      ptr,
         std::enable_if_t<(logical<wide<T, S, ABI>>::static_alignment <= N)> * = 0) noexcept
  {
    store(value, ptr.get());
  }
}

#endif
