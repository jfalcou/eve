//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // scalar Regular case
  template<scalar_value T>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), T value, T *ptr) noexcept
  {
    *ptr = value;
  }

  // -----------------------------------------------------------------------------------------------
  // scalar Aligned case
  template<scalar_value T, std::size_t N>
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
    apply<N::value>([&](auto... I) { ((*ptr++ = value.get(I)), ...); });
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N, aggregated_> const &value, T *ptr) noexcept
  {
    value.storage().apply
    ( [&]<typename... Sub>(Sub&... v)
      {
        int k = 0;
        ((store(v, ptr + k), k += Sub::static_size), ...);
      }
    );
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
    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as_<Sub>)
    {
      return eve::aligned_ptr<T, Sub::static_alignment>{ptr.get()};
    };

    value.storage().apply
    ( [&]<typename... Sub>(Sub&... v)
      {
        int k = 0;
        ((store(v, cast(ptr, as_<Sub>{}) + k), k += Sub::static_size), ...);
      }
    );
  }

  template<real_scalar_value T, typename S, typename ABI>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              logical<wide<T, S, ABI>> const &value,
                              logical<T>* ptr) noexcept
  {
    store(value.mask(), (typename logical<T>::mask_type*) ptr);
  }

  template<real_scalar_value T, typename S, std::size_t A, typename ABI>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              logical<wide<T, S, ABI>> const &value,
                              aligned_ptr<logical<T>, A> ptr) noexcept
    requires (
      requires {store(value.mask(), aligned_ptr<typename logical<T>::mask_type, A>{}); } )
  {
    using mask_type_t = typename logical<T>::mask_type;
    store(value.mask(), aligned_ptr<mask_type_t, A>{(mask_type_t*)ptr.get()});
  }
}
