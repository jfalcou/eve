//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/replace.hpp>
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
  store_(EVE_SUPPORTS(cpu_), wide<T, N> const &value, T *ptr) noexcept
    requires std::same_as<abi_t<T, N>, emulated_>
  {
    apply<N::value>([&](auto... I) { ((*ptr++ = value.get(I)), ...); });
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, N> const &value, T *ptr) noexcept
    requires std::same_as<abi_t<T, N>, aggregated_>
  {
    value.storage().apply
    ( [&]<typename... Sub>(Sub&... v)
      {
        int k = 0;
        ((store(v, ptr + k), k += Sub::size()), ...);
      }
    );
  }

  // -----------------------------------------------------------------------------------------------
  // simd Aligned case
  template<real_scalar_value T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, S, emulated_> const &value, aligned_ptr<T, N> ptr) noexcept
      requires(wide<T, S, emulated_>::alignment() <= N)
  {
    store(value, ptr.get());
  }

  template<real_scalar_value T, typename S, std::size_t N>
  EVE_FORCEINLINE void
  store_(EVE_SUPPORTS(cpu_), wide<T, S, aggregated_> const &value, aligned_ptr<T, N> ptr) noexcept
      requires(wide<T, S, aggregated_>::alignment() <= N)
  {
    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as_<Sub>)
    {
      return eve::aligned_ptr<T, Sub::alignment()>{ptr.get()};
    };

    value.storage().apply
    ( [&]<typename... Sub>(Sub&... v)
      {
        int k = 0;
        ((store(v, cast(ptr, as_<Sub>{}) + k), k += Sub::size()), ...);
      }
    );
  }

  template<simd_value T, relative_conditional_expr C, simd_compatible_ptr<T> Ptr>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              C const &cond,
                              T const &value,
                              Ptr ptr) noexcept
  {
         if constexpr ( C::is_complete && C::is_inverted ) store(value, ptr);
    else if constexpr ( C::has_alternative )               store(replace_ignored(value, cond, cond.alternative), ptr);
    else if constexpr ( C::is_complete ) return;
    else if constexpr ( logical_simd_value<T> )
    {
      using mask_type_t = typename element_type_t<T>::mask_type;
      if constexpr ( std::is_pointer_v<Ptr> ) store[cond](value.mask(), (mask_type_t*) ptr);
      else
      {
        store[cond](value.mask(), typename Ptr::template rebind<mask_type_t>{(mask_type_t*)ptr.get()});
      }
    }
    else if constexpr ( !std::is_pointer_v<Ptr> ) store[cond](value, ptr.get());
    else if constexpr ( has_emulated_abi_v<T> )
    {
      auto offset = cond.offset( as_<T>{} );
      auto count = cond.count( as_<T>{} );
      using e_t = element_type_t<T>;
      auto* src   = (e_t*)(&value.storage());
      std::memcpy((void*)(ptr + offset), (void*)(src + offset), sizeof(e_t) * count);
    }
    else
    {
      using e_t = element_type_t<T>;

      alignas(sizeof(T)) std::array<e_t, T::size()> storage;
      store(value, eve::aligned_ptr<e_t, sizeof(T)>(storage.begin()));

      auto offset = cond.offset( as_<T>{} );
      auto count = cond.count( as_<T>{} );
      std::memcpy((void*)(ptr + offset), (void*)(storage.begin() + offset), sizeof(e_t) * count);
    }
  }

  template<real_scalar_value T, typename S>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              logical<wide<T, S>> const &value,
                              logical<T>* ptr) noexcept
  {
    store(value.mask(), (typename logical<T>::mask_type*) ptr);
  }

  template<real_scalar_value T, typename S, std::size_t A>
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(cpu_),
                              logical<wide<T, S>> const &value,
                              aligned_ptr<logical<T>, A> ptr) noexcept
    requires (
      requires {store(value.mask(), aligned_ptr<typename logical<T>::mask_type, A>{}); } )
  {
    using mask_type_t = typename logical<T>::mask_type;
    store(value.mask(), aligned_ptr<mask_type_t, A>{(mask_type_t*)ptr.get()});
  }
}
