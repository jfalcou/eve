//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/ptr_iterator.hpp>

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
    auto operator()(Traits traits, I f, S l) const
    {
      EVE_ASSERT(f != l, "preprocess_range requires a non-empty range");

      auto* raw_f = &*f;
      auto* raw_l = raw_f + (l - f);
      using T = std::remove_reference_t<decltype(*raw_f)>;
      using it = unaligned_ptr_iterator<T, eve::fixed<eve::expected_cardinal_v<T>>>;

      return detail::preprocess_range_result{traits, it{raw_f}, it{raw_l}};
    }

    // Base case. Should validate that I, S are a valid iterator pair
    template <typename Traits, typename I, typename S>
    auto operator()(Traits traits, I f, S l) const
    {
      EVE_ASSERT(f != l, "preprocess_range requires a non-empty range");
      return detail::preprocess_range_result{traits, f, l};
    }

  } inline constexpr preprocess_range;
}
