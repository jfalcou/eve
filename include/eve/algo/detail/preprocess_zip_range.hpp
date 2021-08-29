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
    template <typename Rng>
    using rng_value_type = std::remove_reference_t<decltype(*std::declval<Rng>().begin())>;

    template <typename Traits, typename ZipTraits, typename ...Rngs>
    EVE_FORCEINLINE auto preprocess_zip_range_traits_support(Traits tr, ZipTraits, kumi::tuple<Rngs...>)
    {
      using value_type = kumi::tuple<rng_value_type<Rngs>...>;
      using N = forced_cardinal_t<decltype(tr), value_type>;

      auto force_cardinal = algo::traits{algo::force_cardinal<N{}()>};

      auto divisible_by_cardinal = [&] {
        if constexpr (ZipTraits::contains(algo::divisible_by_cardinal))
        {
          return default_to(tr, algo::traits(algo::divisible_by_cardinal));
        }
        else
        {
          return eve::algo::traits{};
        }
      }();

      auto common_with_types = [&] {
        if constexpr (ZipTraits::contains(common_with_types_key))
        {
          using Param = rbr::get_type_t<ZipTraits, common_with_types_key>;
          return []<typename... ParamTypes, typename... ZipTypes>(std::common_type<ParamTypes...>,
                                                                  std::common_type<ZipTypes...>)
          {
            return algo::traits {algo::common_with_types<ParamTypes..., ZipTypes...>};
          }
          (Param {}, std::common_type<rng_value_type<Rngs>...> {});
        }
        else
        {
          return eve::algo::traits{};
        }
      }();

      static_assert(!Traits::contains(algo::common_with_types_key), "FIX-#880");

      auto tr_external = default_to(tr, divisible_by_cardinal);

      auto tr_internal = default_to(default_to(tr_external, force_cardinal), common_with_types);

      return std::pair{tr_external, tr_internal};
    }

    template <typename Traits, typename ZipTraits, typename ...Rngs>
    EVE_FORCEINLINE auto preprocess_zip_range(Traits tr, ZipTraits zip_tr, kumi::tuple<Rngs...> rngs) {
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
