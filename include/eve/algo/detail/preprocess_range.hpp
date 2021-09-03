//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/eve_iterator.hpp>
#include <eve/algo/detail/convert.hpp>
#include <eve/algo/traits.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace eve::algo
{
  struct preprocess_range_
  {
    template <typename Traits, std::contiguous_iterator I, typename S>
    EVE_FORCEINLINE auto operator()(Traits traits_, I f, S l) const;

    template <typename Traits, typename I, typename S>
      requires eve::detail::tag_dispatchable<preprocess_range_, Traits, I, S>
    EVE_FORCEINLINE auto operator()(Traits traits, I f, S l) const {
      return tagged_dispatch(*this, traits, f, l);
    }

    template <typename Traits, typename Rng>
      requires eve::detail::tag_dispatchable<preprocess_range_, Traits, Rng>
    EVE_FORCEINLINE auto operator()(Traits traits_, Rng&& rng) const {
      return tagged_dispatch(*this, traits_, std::forward<Rng>(rng));
    }

    template <typename Traits, typename Rng>
    EVE_FORCEINLINE auto operator()(Traits traits_, Rng&& rng) const {
      return operator()(traits_, rng.begin(), rng.end());
    }

    template <typename Traits, typename T, typename A>
    EVE_FORCEINLINE auto operator()(Traits traits_, eve::aligned_ptr<T, A> f, T* l) const;

    template <typename Traits, typename T, typename A1, typename A2>
    EVE_FORCEINLINE auto operator()(Traits traits_, eve::aligned_ptr<T, A1> f, eve::aligned_ptr<T, A2> l) const;

    // Base case. Should validate that I, S are a valid iterator pair
    template <typename Traits, iterator I, sentinel_for<I> S>
    EVE_FORCEINLINE auto operator()(Traits traits_, I f, S l) const;
  };

  inline constexpr preprocess_range_ preprocess_range;

  template<typename Traits, typename I, typename S, typename ToOutput>
  struct preprocess_range_result
  {
    private:
    Traits   traits_;
    I        f_;
    S        l_;
    ToOutput to_output_;

    public:
    preprocess_range_result(Traits traits, I f, S l, ToOutput to_output)
        : traits_(traits)
        , f_(f)
        , l_(l)
        , to_output_(to_output)
    {
    }

    Traits traits() const { return traits_; }

    I begin() const { return f_; }
    S end() const { return l_; }

    template<typename I_> EVE_FORCEINLINE auto to_output_iterator(I_ it) const
    {
      return to_output_(it);
    }
  };

  template<typename Traits, typename I, typename S, typename ToOutput, typename Update>
  EVE_FORCEINLINE auto enhance_to_output(preprocess_range_result<Traits, I, S, ToOutput> prev,
                                         Update                                          update)
  {
    return preprocess_range_result(prev.traits(),
                                   prev.begin(),
                                   prev.end(),
                                   [update, prev](auto it)
                                   { return update(prev.to_output_iterator(it)); });
  }
}
