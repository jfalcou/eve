//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/views/backward.hpp>
#include <eve/algo/views/zip.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo
  //! @{
  //!  @var copy
  //!
  //!  @brief version of std::copy
  //!    * Accepts two things zipping together to range of pair.
  //!    * Also can accept a `zipped_range_pair`.
  //!    * returns void.
  //!    * default unrolling is 4.
  //!    * will align by default.
  //!    * for copying to the same scalar type consider using `std::memmove` instead.
  //!    * will do conversions if necessary.
  //!
  //!   **Required header:** `#include <eve/algo/copy.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct copy_ : TraitsSupport
  {
    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      return transform_to[TraitsSupport::get_traits()](r, do_nothing{});
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  inline constexpr auto copy = function_with_traits<copy_>[default_simple_algo_traits];

  template <typename TraitsSupport>
  struct copy_backward_ : TraitsSupport
  {
    template <zipped_range_pair R>
    EVE_FORCEINLINE void operator()(R r) const
    {
      auto [from, to] = r;
      return copy[TraitsSupport::get_traits()](views::backward(from), views::backward(to));
    }

    template <typename R1, typename R2>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
    }
  };

  inline constexpr auto copy_backward = function_with_traits<copy_backward_>[default_simple_algo_traits];
}
