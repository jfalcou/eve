//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/concepts/eve_iterator.hpp>
#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/traits.hpp>
#include <eve/detail/meta.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace eve::algo
{
  namespace detail
  {
    template <typename I, typename S>
    concept pointer_iterator_sentinel =
      (std::is_pointer_v<I> || eve::detail::instance_of<I, aligned_ptr>) &&
      (std::is_pointer_v<S> || eve::detail::instance_of<S, aligned_ptr>) &&
      std::same_as<typename eve::pointer_traits<I>::value_type,
                   typename eve::pointer_traits<S>::value_type>;
  }

  struct preprocess_range_
  {
    template <typename Traits, typename I, typename S>
      requires  detail::pointer_iterator_sentinel<I, S>
    EVE_FORCEINLINE auto operator()(Traits traits_, I f, S l) const;

    template <typename Traits, std::contiguous_iterator I, typename S>
      requires ( !std::is_pointer_v<I> )
    EVE_FORCEINLINE auto operator()(Traits traits_, I f, S l) const;

    template <typename Traits, typename I, typename S>
      requires eve::detail::tag_dispatchable<preprocess_range_, Traits, I, S>
    EVE_FORCEINLINE auto operator()(Traits traits, I f, S l) const {
      return tagged_dispatch(*this, traits, f, l);
    }

    template <typename Traits, typename Rng>
      requires eve::detail::tag_dispatchable<preprocess_range_, Traits, Rng>
    EVE_FORCEINLINE auto operator()(Traits traits_, Rng&& rng) const {
      return tagged_dispatch(*this, traits_, EVE_FWD(rng));
    }

    template <typename Traits, typename Rng>
    EVE_FORCEINLINE auto operator()(Traits traits_, Rng&& rng) const {
      return operator()(traits_, rng.begin(), rng.end());
    }
    // Base case. Should validate that I, S are a valid iterator pair
    template <typename Traits, iterator I, sentinel_for<I> S>
    EVE_FORCEINLINE auto operator()(Traits traits_, I f, S l) const;
  };

  inline constexpr preprocess_range_ preprocess_range;

  template<typename Traits, typename I, typename S>
  struct preprocess_range_result
  {
    private:
    Traits   traits_;
    I        f_;
    S        l_;

    public:
    preprocess_range_result(Traits traits, I f, S l)
        : traits_(traits)
        , f_(f)
        , l_(l)
    {
    }

    Traits traits() const { return traits_; }

    I begin() const { return f_; }
    S end() const { return l_; }
  };
}
