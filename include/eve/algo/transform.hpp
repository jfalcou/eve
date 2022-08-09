//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/array_utils.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/views/convert.hpp>
#include <eve/algo/for_each.hpp>
#include <eve/algo/traits.hpp>

namespace eve::algo
{
  namespace detail
  {
    template<typename LoadStore, typename Op>
    struct transform_delegate
    {
      Op op;

      explicit transform_delegate(Op op) : op(op) {}

      EVE_FORCEINLINE void operator()(auto it, eve::relative_conditional_expr auto ignore)
      {
        auto load_it  = LoadStore::load_it(it);
        auto store_it = LoadStore::store_it(it);

        auto xs        = eve::load[ignore](load_it);
        auto processed = op(xs);

        using out_t = eve::element_type_t<decltype(processed)>;
        auto cvt_and_store_it = views::convert(store_it, as<out_t>{});

        eve::store[ignore](processed, cvt_and_store_it);
      }
    };
  }

  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!  @var transform_inplace
  //!
  //!  @brief same as;
  //!  @code{.cpp}
  //!  eve::algo::tranform_to(eve::views::zip(r, r), op)
  //!  @endcode
  //!  but slightly more efficient
  //!
  //!   **Required header:** `#include <eve/algo/transform.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct transform_inplace_ : TraitsSupport
  {
    template <relaxed_range Rng, typename Op>
    EVE_FORCEINLINE void operator()(Rng&& rng, Op op) const
    {
      detail::transform_delegate<inplace_load_store, Op> d{op};
      for_each[TraitsSupport::get_traits()](EVE_FWD(rng), d);
    }
  };

  inline constexpr auto transform_inplace = function_with_traits<transform_inplace_>[default_simple_algo_traits];

  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!  @var transform_to
  //!
  //!  @brief SIMD version of std::transform
  //!    * Accepts two things zipping together to range of pair.
  //!    * Also can accept a `zipped_range_pair`.
  //!    * returns void.
  //!    * default unrolling is 4.
  //!    * will align by default.
  //!    * the output type of the operation, is not considered in cardinal computation.
  //!      (otherwise we'd have to require the predicate to be a template).
  //!    * if the operation output type differs from the output range type, converts.
  //!
  //!   **Required header:** `#include <eve/algo/transform.hpp>`
  //!
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct transform_to_ : TraitsSupport
  {
    template <zipped_range_pair R, typename Op>
    EVE_FORCEINLINE void operator()(R r, Op op) const
    {
      detail::transform_delegate<to_load_store, Op> d{op};
      for_each[TraitsSupport::get_traits()](r, d);
    }

    template <typename R1, typename R2, typename Op>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2, Op op) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)), op);
    }
  };

  inline constexpr auto transform_to = function_with_traits<transform_to_>[default_simple_algo_traits];
}
