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
    EVE_FORCEINLINE auto preprocess_zip_range_traits_support(Traits tr, kumi::tuple<Rngs...>)
    {
      using N = iteration_cardinal_t<decltype(tr), kumi::tuple<value_type_t<Rngs>...>>;

      auto force_cardinal = algo::traits{algo::force_cardinal<N{}()>};

      static_assert(!Traits::contains(algo::common_with_types_key), "FIX-#880");

      auto tr_external = tr;

      auto tr_internal = default_to(tr_external, force_cardinal);

      return std::pair{tr_external, tr_internal};
    }

    template <typename Traits, typename ...Rngs>
    EVE_FORCEINLINE auto preprocess_zip_range(Traits tr, kumi::tuple<Rngs...> rngs) {
      auto tr_pair = preprocess_zip_range_traits_support(tr, rngs);
      // Bindings don't work with captures
      auto tr_external = tr_pair.first;
      auto tr_internal = tr_pair.second;

      auto processed_components = kumi::map([&](auto rng) { return preprocess_range(tr_internal, rng); }, rngs);

      auto f = zip_iterator(kumi::map([](auto r) { return r.begin(); }, processed_components));
      auto l = zip_iterator(kumi::map([](auto r) { return r.end(); }, processed_components));

      return preprocess_range(tr_external, f, l);
    }
  }
}
