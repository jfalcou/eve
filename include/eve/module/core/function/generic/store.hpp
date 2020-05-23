//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_STORE_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // scalar Regular case
  template<real_scalar_value T>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), T value, T *ptr) noexcept
  {
    *ptr = value;
  }

  // -----------------------------------------------------------------------------------------------
  // scalar Aligned case
  template<real_scalar_value T, std::size_t N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), T value, aligned_ptr<T, N> ptr) noexcept
  {
    *ptr = value;
  }

  // -----------------------------------------------------------------------------------------------
  // simd Regular case
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N, emulated_> const &value, T *ptr) noexcept
  {
    apply<N::value>([&](auto... I) { ((*ptr++ = value[I]), ...); });
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N, aggregated_> const &value, T *ptr) noexcept
  {
    using str_t = typename wide<T, N, aggregated_>::storage_type;
    value.storage().apply([&](auto &... v) {
      int k = 0;
      ((store(v, ptr + k), k += str_t::small_size), ...);
    });
  }

  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &value, logical<T> *ptr) noexcept
  {
    auto raw_data = bit_cast(value, as_<wide<T, N, ABI>> {});
    store(raw_data, (T *)(ptr));
  }

  // -----------------------------------------------------------------------------------------------
  // simd Aligned case
  template<real_scalar_value T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, S, emulated_> const &value, aligned_ptr<T, N> ptr) noexcept
      requires(wide<T, S, emulated_>::static_alignment <= N)
  {
    store(value, ptr.get());
  }

  template<real_scalar_value T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, S, aggregated_> const &value, aligned_ptr<T, N> ptr) noexcept
      requires(wide<T, S, aggregated_>::static_alignment <= N)
  {
    using str_t = typename wide<T, S, aggregated_>::storage_type;
    value.storage().apply([&](auto &... v) {
      int k = 0;
      ((store(v, ptr + k), k += str_t::small_size), ...);
    });
  }

  template<real_scalar_value T, typename S, std::size_t N, typename ABI>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              logical<wide<T, S, ABI>> const &value,
                              aligned_ptr<logical<T>, N>      ptr) noexcept
      requires(logical<wide<T, S, ABI>>::static_alignment <= N)
  {
    auto raw_data = bit_cast(value, as_<wide<T, S, ABI>> {});
    store(raw_data, (T *)(ptr.get()));
  }
}

#endif
