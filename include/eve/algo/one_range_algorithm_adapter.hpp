//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/concepts.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

namespace eve::algo
{
  template <typename Adaptee>
  struct one_range_algorithm_adapter
  {
   private:
    Adaptee const& self() const { return static_cast<Adaptee const&>(*this); }

    template <instance_of<algo::traits> Traits, typename I, typename S, typename ... Args>
      requires std::invocable<preprocess_range_, Traits, I, S>
    EVE_FORCEINLINE decltype(auto) after_dealing_with_traits(Traits tr_, I f_, S l_, Args&& ... args) const
    {
      auto [tr, f, l] = preprocess_range(tr_, f_, l_);
      return self().impl(tr, f, l, std::forward<Args>(args)...);
    }


    template <instance_of<algo::traits> Traits, typename Rng, typename ... Args>
      requires std::invocable<preprocess_range_, Traits, Rng>
    EVE_FORCEINLINE decltype(auto) after_dealing_with_traits(Traits tr_, Rng&& rng, Args&& ... args) const
    {
      auto [tr, f, l] = preprocess_range(tr_, std::forward<Rng>(rng));
      return self().impl(tr, f, l, std::forward<Args>(args)...);
    }

   public:

    template <typename Arg, typename ... Args>
    EVE_FORCEINLINE decltype(auto) operator()(Arg&& arg, Args&& ... args) const
    {
      if constexpr( instance_of<Arg, algo::traits> )
      {
        auto tr_ = eve::algo::default_to(arg, self().default_traits());
        return after_dealing_with_traits(tr_, std::forward<Args>(args)...);
      }
      else
      {
        return after_dealing_with_traits(
            self().default_traits(), std::forward<Arg>(arg), std::forward<Args>(args)...);
      }
    }
  };
}
