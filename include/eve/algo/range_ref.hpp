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
  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!   @struct range_ref_wrapper
  //!   @brief a non_owning_range wrapper around owning range.
  //!          Should be created via `range_ref`
  //!
  //!   **Required header:** `#include <eve/algo/range_ref.hpp>`
  //!
  //! @}
  //================================================================================================

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

  //================================================================================================
  //! @addtogroup algo_concepts
  //! @{
  //!    @var non_owning_range
  //!    @brief a non_owning range is a relaxed_range that does not own it's elements and
  //!           can be copied without it's contents being affected
  //!           TODO: FIX-#1017: how is this related to `std::borrowed_range`?
  //!
  //!    Can be enabled via: defining 'is_non_owning' internal typedef.
  //!
  //!   **Required header:** `#include <eve/algo/range_ref.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename T>
  concept non_owning_range = relaxed_range<T> && requires {
    typename T::is_non_owning;
  };

  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!    @var range_ref
  //!    @brief for a `non_owning_range` returns it, otherwise returns a `range_ref_wrapper`.
  //!
  //!   **Required header:** `#include <eve/algo/range_ref.hpp>`
  //! @}
  //================================================================================================

  struct range_ref_
  {
    EVE_FORCEINLINE auto operator()(non_owning_range auto r) const { return r; }

    template<relaxed_range R>
      requires (!non_owning_range<R>)  // gcc concepts bug
    EVE_FORCEINLINE auto operator()(R& r) const { return range_ref_wrapper{r}; }
  };

  inline constexpr range_ref_ range_ref;
}
