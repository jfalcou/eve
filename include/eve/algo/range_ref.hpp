//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/relaxed.hpp>

namespace eve::algo
{
  template<relaxed_range Rng>
  struct range_ref_wrapper
  {
    private:
      Rng *rng;
    public:
      using is_non_owning = void;

      range_ref_wrapper() = default;

      explicit range_ref_wrapper(Rng &rng) : rng(&rng) {}

      // FIX-874: non member ones should be used
      auto begin() const { return rng->begin(); }
      auto end() const { return rng->end(); }

      template<typename Traits>
      EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits traits, range_ref_wrapper self)
      {
        return preprocess_range(traits, *self.rng);
      }
  };

  template <typename T>
  concept non_owning_range = relaxed_range<T> && requires {
    typename T::is_non_owning;
  };

  struct range_ref_
  {
    EVE_FORCEINLINE auto operator()(non_owning_range auto r) const { return r; }

    template<relaxed_range R>
      requires (!non_owning_range<R>)  // gcc concepts bug
    EVE_FORCEINLINE auto operator()(R& r) const { return range_ref_wrapper{r}; }
  };

  inline constexpr range_ref_ range_ref;
}
