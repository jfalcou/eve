//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/memory.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/store_equivalent.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// simd Tuple case
template<kumi::product_type T, typename S, typename... Ptrs>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_),
       wide<T, S> const& value,
       soa_ptr<Ptrs...>  ptrs) noexcept requires std::same_as<abi_t<T, S>, bundle_>
{
  kumi::for_each([](auto v, auto p) { store(v, p); }, value, ptrs);
}

template<kumi::product_type T, typename S, relative_conditional_expr C, typename... Ptrs>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_), C const& c, wide<T, S> const& value, soa_ptr<Ptrs...> ptrs) noexcept
{
  if constexpr( C::has_alternative )
  {
    auto alt = [&]
    {
      if constexpr( kumi::product_type<typename C::alternative_type> ) return c.alternative;
      else return c.alternative.storage();
    }();

    kumi::for_each(
        [&](auto v, auto part_alt, auto p)
        {
          auto new_c = c.map_alternative([&](auto) { return part_alt; });
          store[new_c](v, p);
        },
        value.storage(),
        alt,
        ptrs);
  }
  else
  {
    kumi::for_each([&](auto v, auto p) { store[c](v, p); }, value.storage(), ptrs);
  }
}

// -----------------------------------------------------------------------------------------------
// simd Regular case
template<real_scalar_value T, typename N>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_),
       wide<T, N> value,
       T         *ptr) noexcept requires std::same_as<abi_t<T, N>, emulated_>
{
  apply<N::value>([&](auto... I) { ((*ptr++ = value.get(I)), ...); });
}

template<real_scalar_value T, typename N>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_),
       wide<T, N> value,
       T         *ptr) noexcept requires std::same_as<abi_t<T, N>, aggregated_>
{
  value.storage().apply(
      [&]<typename... Sub>(Sub&...v)
      {
        int k = 0;
        ((store(v, ptr + k), k += Sub::size()), ...);
      });
}

// -----------------------------------------------------------------------------------------------
// simd Aligned case
template<real_scalar_value T, typename S, typename Lanes>
    EVE_FORCEINLINE void
    store_(EVE_SUPPORTS(cpu_), wide<T, S> const& value, aligned_ptr<T, Lanes> ptr) noexcept
    requires(S::value <= Lanes::value)
    && std::same_as<abi_t<T, S>, emulated_>
{
  store(value, ptr.get());
}

template<real_scalar_value T, typename S, typename Lanes>
    EVE_FORCEINLINE void
    store_(EVE_SUPPORTS(cpu_), wide<T, S> const& value, aligned_ptr<T, Lanes> ptr) noexcept
    requires(S::value <= Lanes::value)
    && std::same_as<abi_t<T, S>, aggregated_>
{
  auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as<Sub>)
  { return eve::aligned_ptr<T, typename Sub::cardinal_type> {ptr.get()}; };

  value.storage().apply(
      [&]<typename... Sub>(Sub&...v)
      {
        int k = 0;
        ((store(v, cast(ptr, as<Sub> {}) + k), k += Sub::size()), ...);
      });
}

template<simd_value T, relative_conditional_expr C, simd_compatible_ptr<T> Ptr>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_), C const& cond, T const& value, Ptr ptr) noexcept
{
  if constexpr( C::is_complete && C::is_inverted ) store(value, ptr);
  else if constexpr( C::has_alternative )
    store(replace_ignored(value, cond, cond.alternative), ptr);
  else if constexpr( C::is_complete ) return;
  else if constexpr( logical_simd_value<T> )
  {
    using mask_type_t = typename element_type_t<T>::mask_type;
    if constexpr( std::is_pointer_v<Ptr> ) store[cond](value.mask(), (mask_type_t *)ptr);
    else
    {
      store[cond](value.mask(),
                  typename Ptr::template rebind<mask_type_t> {(mask_type_t *)ptr.get()});
    }
  }
  else if constexpr( !std::is_pointer_v<Ptr> ) store[cond](value, ptr.get());
  else if constexpr( has_emulated_abi_v<T> )
  {
    auto offset = cond.offset(as<T> {});
    auto count  = cond.count(as<T> {});
    using e_t   = element_type_t<T>;
    auto *src   = (e_t *)(&value.storage());
    std::memcpy((void *)(ptr + offset), (void *)(src + offset), sizeof(e_t) * count);
  }
  else
  {
    using e_t = element_type_t<T>;

    alignas(sizeof(T)) std::array<e_t, T::size()> storage;
    store(value, eve::aligned_ptr<e_t, typename T::cardinal_type>(storage.begin()));

    auto offset = cond.offset(as<T> {});
    auto count  = cond.count(as<T> {});
    std::memcpy((void *)(ptr + offset), (void *)(storage.begin() + offset), sizeof(e_t) * count);
  }
}

template<real_scalar_value T, typename S>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_), logical<wide<T, S>> const& value, logical<T> *ptr) noexcept
{
  store(value.mask(), (typename logical<T>::mask_type *)ptr);
}

template<real_scalar_value T, typename S, typename Lanes>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_),
       logical<wide<T, S>> const    & value,
       aligned_ptr<logical<T>, Lanes> ptr) noexcept requires(requires {
  store(value.mask(), aligned_ptr<typename logical<T>::mask_type, Lanes> {});
})
{
  using mask_type_t = typename logical<T>::mask_type;
  store(value.mask(), aligned_ptr<mask_type_t, Lanes> {(mask_type_t *)ptr.get()});
}

template<simd_value T, relative_conditional_expr C, simd_compatible_ptr<T> Ptr>
requires has_store_equivalent<T, Ptr> EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_), C const& c, T const& v, Ptr ptr) noexcept
{
  auto [c1, v1, ptr1] = store_equivalent(c, v, ptr);
  return store[c1](v1, ptr1);
}

template<simd_value T, simd_compatible_ptr<T> Ptr>
requires has_store_equivalent<T, Ptr> EVE_FORCEINLINE void
store_(EVE_SUPPORTS(cpu_), T const& v, Ptr ptr) noexcept
{
  return store[ignore_none](v, ptr);
}
}
