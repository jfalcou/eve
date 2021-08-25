//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>

namespace eve::algo
{
  template <typename ...Is>
  struct zip_iterator;

  namespace detail
  {
    template <typename Traits, typename ZipTraits, typename ...Rngs>
    auto preprocess_zip_range_traits_support(Traits tr, ZipTraits, kumi::tuple<Rngs...>)
    {
      using value_type = kumi::tuple<std::remove_reference_t<decltype(*std::declval<Rngs>().begin())>...>;
      using N = forced_cardinal_t<decltype(tr), value_type>;

      auto tr_external = [&] {
        if constexpr (ZipTraits::contains(eve::algo::divisible_by_cardinal))
        {
          return default_to(tr, eve::algo::traits(eve::algo::divisible_by_cardinal));
        }
        else
        {
          return tr;
        }
      }();

      auto tr_internal = default_to(tr_external, eve::algo::traits{force_cardinal<N{}()>});

      return std::pair{tr_external, tr_internal};
    }

    template <typename Traits, typename ZipTraits, typename ...Rngs>
    auto preprocess_zip_range(Traits tr, ZipTraits zip_tr, kumi::tuple<Rngs...> rngs) {
      auto tr_pair = preprocess_zip_range_traits_support(tr, zip_tr, rngs);
      // Bindings don't work with captures
      auto tr_external = tr_pair.first;
      auto tr_internal = tr_pair.second;

      auto processed_components = kumi::map([&](auto rng) { return preprocess_range(tr_internal, rng); }, rngs);

      auto f = zip_iterator(kumi::map([](auto r) { return r.begin(); }, processed_components));
      auto l = zip_iterator(kumi::map([](auto r) { return r.end(); }, processed_components));

      auto as_eve_its = preprocess_eve_it_sentinel(tr_external, f, l);

      return enhance_to_output(as_eve_its, [processed_components](auto i) {
          return zip_iterator{
            kumi::map([](auto r_i, auto i_i) { return r_i.to_output_iterator(i_i);},
            processed_components, i)
          };
        });
    }
  }
}
