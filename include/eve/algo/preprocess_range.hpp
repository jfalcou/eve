//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/ptr_iterator.hpp>
#include <eve/algo/traits.hpp>

#include <iterator>
#include <ranges>
#include <type_traits>
#include <utility>

namespace eve::algo
{
  namespace detail
  {
    template <typename Traits, typename I, typename S>
    struct preprocess_range_result
    {
      Traits traits;
      I f;
      S l;
    };

    template <typename Traits, typename I, typename S>
    preprocess_range_result(Traits, I, S) -> preprocess_range_result<Traits, I, S>;
  }

  struct preprocess_range_
  {
    template <typename Traits, std::contiguous_iterator I, typename S>
    auto operator()(Traits traits_, I f, S l) const
    {
      using T = std::remove_reference_t<decltype(*f)>;
      using it = unaligned_ptr_iterator<T, eve::fixed<eve::expected_cardinal_v<T>>>;

      T* raw_f = nullptr;
      T* raw_l = raw_f;

      if (f != l)
      {
        raw_f = &*f;
        raw_l = raw_f + (l - f);
      }

      return operator()(traits_, it{raw_f}, it{raw_l});
    }

    template <typename Traits, typename Rng>
      requires std::ranges::contiguous_range<std::remove_reference_t<Rng>>
    auto operator()(Traits traits_, Rng&& rng) const {
      return operator()(traits_,
                        std::ranges::begin(std::forward<Rng>(rng)),
                        std::ranges::end(std::forward<Rng>(rng)));
    }

    template <typename Traits, typename T>
    auto operator()(Traits traits_, eve::aligned_ptr<T> f, T* l) const
    {
      using N            = eve::fixed<eve::expected_cardinal_v<T>>;
      using aligned_it   = aligned_ptr_iterator<T, N>;
      using unaligned_it = unaligned_ptr_iterator<T, N>;

      return operator()(traits_, aligned_it(f), unaligned_it(l));
    }

    // Base case. Should validate that I, S are a valid iterator pair
    template <typename Traits, iterator I, sentinel_for<I> S>
    auto operator()(Traits traits_, I f, S l) const
    {
      auto deduced = [] {
        if constexpr (partially_aligned_iterator<I>)
        {
          if constexpr ( std::same_as<I, S> && !always_aligned_iterator<I> ) return algo::traits(no_aligning, divisible_by_cardinal);
          else                                                               return algo::traits(no_aligning);
        }
        else
        {
          return algo::traits();
        }
      }();
      return detail::preprocess_range_result{default_to(traits_, deduced), f, l};
    }

  } inline constexpr preprocess_range;
}
