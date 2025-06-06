//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
  template<callable_options O, simd_value T, typename Dst>
  EVE_FORCEINLINE void store_(EVE_REQUIRES(cpu_), O const& opts, T value, Dst dst) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (requires { dst.store(opts, value); })
    {
      dst.store(opts, value);
    }
    else if constexpr (has_store_equivalent<T, Dst>)
    {
      auto [n_cx, n_value, n_dst] = store_equivalent(cx, value, dst);
      store[n_cx](n_value, n_dst);
    }
    else if constexpr (kumi::product_type<T>)
    {
      if constexpr (std::same_as<C, ignore_none_>)
      {
        kumi::for_each([](auto v, auto p) { store(v, p); }, value, dst);
      }
      else
      {
        if constexpr (C::has_alternative)
        {
          auto alt = [&]
          {
            if constexpr (kumi::product_type<typename C::alternative_type>) return cx.alternative;
            else return cx.alternative.storage();
          }();

          kumi::for_each(
              [&](auto v, auto part_alt, auto p)
              {
                auto new_c = cx.map_alternative([&](auto) { return part_alt; });
                store[new_c](v, p);
              },
              value.storage(),
              alt,
              dst);
        }
        else
        {
          kumi::for_each([&](auto v, auto p) { store[cx](v, p); }, value.storage(), dst);
        }
      }
    }
    else if constexpr (!std::is_pointer_v<Dst>)
    {
      store[opts](value, dst.get());
    }
    else if constexpr (std::same_as<C, ignore_none_>)
    {
      if constexpr (has_emulated_abi_v<T>)
      {
        apply<T::cardinal_type::value>([&](auto... I) { ((*dst++ = value.get(I)), ...); });
      }
      else if constexpr (has_aggregated_abi_v<T>)
      {
        value.storage().apply(
          [&]<typename... Sub>(Sub&...v)
          {
            int k = 0;
            ((store(v, dst + k), k += Sub::size()), ...);
          });
      }
    }
    else if constexpr (C::has_alternative) store(replace_ignored(value, cx, cx.alternative), dst);
    else if constexpr (C::is_complete) return;
    else if constexpr (has_emulated_abi_v<T>)
    {
      auto offset = cx.offset(as<T> {});
      auto count  = cx.count(as<T> {});
      using e_t   = element_type_t<T>;
      auto *src   = (e_t *)(&value.storage());
      std::memcpy((void *)(dst + offset), (void *)(src + offset), sizeof(e_t) * count);
    }
    else
    {
      using e_t = element_type_t<T>;

      alignas(sizeof(T)) std::array<e_t, T::size()> storage;
      store(value, eve::aligned_ptr<e_t, typename T::cardinal_type>(storage.begin()));

      auto offset = cx.offset(as<T> {});
      auto count  = cx.count(as<T> {});
      std::memcpy((void *)(dst + offset), (void *)(storage.begin() + offset), sizeof(e_t) * count);
    }
  }

  template<callable_options O, typename T, typename N, typename Dst>
  EVE_FORCEINLINE void store_(EVE_REQUIRES(cpu_), O const& opts, logical<wide<T, N>> value, Dst dst) noexcept
  {
    if constexpr (std::is_pointer_v<Dst>)
    {
      store[opts](value.mask(), reinterpret_cast<typename logical<T>::mask_type*>(dst));
    }
    else
    {
      using mask_type_t = typename logical<T>::mask_type;
      store[opts](value.mask(), aligned_ptr<mask_type_t, N> { reinterpret_cast<mask_type_t*>(dst.get()) });
    }
  }
}
