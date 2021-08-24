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
    template <typename Traits, typename ...Rngs>
    auto preprocess_zip_range(Traits tr, kumi::tuple<Rngs...> rngs) {
      using value_type = kumi::tuple<std::remove_reference_t<decltype(*std::declval<Rngs>().begin())>...>;
      using N = forced_cardinal_t<Traits, value_type>;

      auto tr_with_cardinal = default_to(tr, traits{force_cardinal<N{}()>});

      auto processed_components = kumi::map([tr_with_cardinal](auto rng) { return preprocess_range(tr_with_cardinal, rng); }, rngs);

      auto f = zip_iterator(kumi::map([](auto r) { return r.begin(); }, processed_components));
      auto l = zip_iterator(kumi::map([](auto r) { return r.end(); }, processed_components));

      auto as_eve_its = preprocess_eve_it_sentinel(tr, f, l);

      return enhance_to_output(as_eve_its, [processed_components](auto i) {
          return zip_iterator{
            kumi::map([](auto r_i, auto i_i) { return r_i.to_output_iterator(i_i);},
            processed_components, i)
          };
        });
    }
  }
}
