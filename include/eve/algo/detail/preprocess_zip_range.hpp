//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/value_type.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <typename ...Is>
  struct zip_iterator;

  namespace detail
  {
    template <typename Traits, typename ...Rngs>
    EVE_FORCEINLINE auto preprocess_zip_range(Traits tr, kumi::tuple<Rngs...> rngs) {
      auto tr_internal = [&]{
        static_assert(!has_type_overrides_v<Traits>, "FIX-#880, FIX-#896");

        using N = iteration_cardinal_t<Traits, kumi::tuple<value_type_t<Rngs>...>>;
        auto force_cardinal = algo::traits{algo::force_cardinal<N{}()>};

        return default_to(tr, force_cardinal);
      }();

      auto components = kumi::map([&](auto rng) { return preprocess_range(tr_internal, rng); }, rngs);

      auto tr2 = kumi::fold_right(
          default_to,
          kumi::map([](auto r) { return drop_key(force_cardinal_key, r.traits()); }, components),
          tr);

      auto f = zip_iterator(kumi::map([](auto r) { return r.begin(); }, components));
      auto l = zip_iterator(kumi::map([](auto r) { return r.end(); }, components));

      return preprocess_range(tr2, f, l);
    }
  }
}
