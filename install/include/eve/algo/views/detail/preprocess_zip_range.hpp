//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits.hpp>

namespace eve::algo::views
{
  template <typename ...Is>
  struct zip_iterator;

  namespace detail
  {
    template <typename Traits, typename ...Rngs>
    EVE_FORCEINLINE auto preprocess_zip_range(Traits tr, kumi::tuple<Rngs...> rngs) {
      // So far decided not to return types to consider in resulting traits.
      // Maybe we should.
      eve::algo::traits types_to_consider{ consider_types_key = kumi::result::cat_t<types_to_consider_for_t<Rngs> ...>{} };
      auto tr_internal = default_to(tr, types_to_consider);

      auto components = kumi::map([&](auto rng) { return preprocess_range(tr_internal, rng); }, rngs);

      auto tr2 = kumi::fold_right(
          default_to,
          kumi::map([](auto r) { return drop_key(consider_types_key, r.traits()); }, components),
          tr);

      auto f = zip_iterator(kumi::map([](auto r) { return r.begin(); }, components));
      auto l = zip_iterator(kumi::map([](auto r) { return r.end(); }, components));

      return preprocess_range(tr2, f, l);
    }
  }
}
