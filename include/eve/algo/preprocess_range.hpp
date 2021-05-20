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

#include <eve/assert.hpp>

#include <iterator>
#include <type_traits>

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
      EVE_ASSERT(f != l, "preprocess_range requires a non-empty range");

      auto* raw_f = &*f;
      auto* raw_l = raw_f + (l - f);
      using T = std::remove_reference_t<decltype(*raw_f)>;
      using it = unaligned_ptr_iterator<T, eve::fixed<eve::expected_cardinal_v<T>>>;

      return operator()(traits_, it{raw_f}, it{raw_l});
    }

    // Base case. Should validate that I, S are a valid iterator pair
    template <typename Traits, iterator_basics I, sentinel_for<I> S>
    auto operator()(Traits traits_, I f, S l) const
    {
      EVE_ASSERT(f != l, "preprocess_range requires a non-empty range");

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
