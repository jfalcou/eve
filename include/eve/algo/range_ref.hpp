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
  struct range_ref
  {
   private:
    Rng *rng;

   public:
    using is_non_owning = int;

    range_ref() = default;

    explicit range_ref(Rng &rng) : rng(&rng) {}

    // FIX-874: non member ones should be used
    auto begin() const { return rng->begin(); }
    auto end() const { return rng->end(); }

    template<typename Traits>
    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, Traits traits, range_ref self)
    {
      return preprocess_range(traits, *self.rng);
    }
  };

  template <typename T>
  concept non_owning_range = relaxed_range<T> && requires {
    { typename T::is_non_owning{} };
  };

  struct take_range_ref_
  {
    template <typename R>
    auto operator()(R&& r) const
    {
      using no_ref = std::remove_reference_t<R>;

      if constexpr ( non_owning_range<no_ref> ) return r;
      else                                      return range_ref<no_ref>{r};
    }
  };
  inline constexpr take_range_ref_ take_range_ref;
}
