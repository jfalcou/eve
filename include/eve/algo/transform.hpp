//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/views/convert.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

namespace eve::algo
{
  namespace detail
  {
    template<typename LoadStore>
    struct transform_common
    {
      template <typename Op>
      struct delegate
      {
        Op op;

        explicit delegate(Op op) : op(op) {}

        EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
        {
          auto load_it  = LoadStore::load_it(it);
          auto store_it = LoadStore::store_it(it);

          auto xs        = eve::load[ignore](load_it);
          auto processed = op(xs);

          using out_t = eve::element_type_t<decltype(processed)>;
          auto cvt_and_store_it = views::convert(store_it, as<out_t>{});

          eve::store[ignore](op(xs), cvt_and_store_it);
          return false;
        }

        template<typename I, std::size_t size>
        EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
        {
          array_map(arr, call_single_step(this));
          return false;
        }
      };

      template<typename Traits, typename Rng, typename Op>
      EVE_FORCEINLINE void operator()(Traits tr, Rng &&rng, Op op) const
      {
        auto processed = preprocess_range(tr, std::forward<Rng>(rng));
        if( processed.begin() == processed.end() ) return;

        delegate<Op> d{op};
        algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      }
    };
  }

  template <typename TraitsSupport>
  struct transform_inplace_ : TraitsSupport
  {
    template <relaxed_range Rng, typename Op>
    EVE_FORCEINLINE void operator()(Rng&& rng, Op op) const
    {
      detail::transform_common<inplace_load_store>{}(
        TraitsSupport::get_traits(), std::forward<Rng>(rng), op);
    }
  };

  inline constexpr auto transform_inplace = function_with_traits<transform_inplace_>[default_simple_algo_traits];

  template <typename TraitsSupport>
  struct transform_to_ : TraitsSupport
  {
    template <zipped_range_pair R, typename Op>
    EVE_FORCEINLINE void operator()(R r, Op op) const
    {
      detail::transform_common<to_load_store>{}(TraitsSupport::get_traits(), r, op);
    }

    template <typename R1, typename R2, typename Op>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE void operator()(R1&& r1, R2&& r2, Op op) const
    {
      operator()(views::zip(std::forward<R1>(r1), std::forward<R2>(r2)), op);
    }
  };

  inline constexpr auto transform_to = function_with_traits<transform_to_>[default_simple_algo_traits];
}
