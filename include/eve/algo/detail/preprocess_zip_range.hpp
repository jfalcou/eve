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
    template<typename Ranges>
    struct preprocessed_zip_result
    {
      Ranges ranges;

      auto traits() const { return get<0>(ranges).traits(); }

      auto begin() const
      {
        return zip_iterator(kumi::map([](auto r) { return r.begin(); }, ranges));
      }

      auto end() const
      {
        return zip_iterator(kumi::map([](auto r) { return r.end(); }, ranges));
      }

      template<typename I> auto to_output_iterator(I i) const
      {
        return zip_iterator(
            kumi::map([](auto r_i, auto i_i) { return r_i.to_output_iterator(i_i); }, ranges, i));
      }
    };

    template <typename Ranges>
    preprocessed_zip_result(Ranges) -> preprocessed_zip_result<Ranges>;

    template <typename Traits, typename ...Rngs>
    auto preprocess_zip_range(Traits traits, kumi::tuple<Rngs...> rngs) {
      return preprocessed_zip_result{
        kumi::map([traits](auto rng) { return preprocess_range(traits, rng); }, rngs)
      };
    }
  }
}
