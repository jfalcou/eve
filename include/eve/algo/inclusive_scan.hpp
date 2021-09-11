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
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/constant/as_value.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/scan.hpp>

namespace eve::algo
{
  namespace detail
  {

    template<typename LoadStore>
    struct inclusive_scan_common
    {
      template<typename Op, typename Zero, typename Wide>
      struct delegate
      {
        Op   op;
        Zero zero;
        Wide running_sum;

        delegate(Op op, Zero zero, Wide init) : op(op), zero(zero), running_sum(init) {}

        EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
        {
          auto xs     = LoadStore::load(ignore.else_(eve::as_value(zero, as<Wide> {})), it);
          xs          = eve::scan(xs, op, zero);
          xs          = op(xs, running_sum);
          running_sum = Wide(xs.back());
          LoadStore::store(ignore, xs, it);
          return false;
        }

        template<typename I, std::size_t size>
        EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
        {
          array_map(arr, call_single_step(this));
          return false;
        }
      };

      template<typename Traits, typename Rng, typename Op, typename Zero, typename U>
      EVE_FORCEINLINE void operator()(Traits tr, Rng &&rng, std::pair<Op, Zero> op_zero, U init) const
      {
        auto processed = preprocess_range(tr, std::forward<Rng>(rng));
        if( processed.begin() == processed.end() ) return;

        using I      = decltype(processed.begin());
        using T      = typename LoadStore::template read_value_type<I>;
        using wide_t = eve::wide<T, typename I::cardinal>;

        wide_t wide_init = eve::as_value(init, eve::as<wide_t> {});

        auto [op, zero] = op_zero;

        delegate<Op, Zero, wide_t> d {op, zero, wide_init};
        algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      }
    };
  }

  template <typename TraitsSupport>
  struct inclusive_scan_inplace_ : TraitsSupport
  {
    template <relaxed_range Rng, typename Op, typename Zero, typename U>
    EVE_FORCEINLINE void operator()(Rng&& rng, std::pair<Op, Zero> op_zero, U init) const
    {
      detail::inclusive_scan_common<inplace_load_store>{}(
        TraitsSupport::get_traits(), std::forward<Rng>(rng), op_zero, init);
    }

    template <relaxed_range Rng, typename U>
    EVE_FORCEINLINE void operator()(Rng&& rng, U init) const
    {
      operator()(std::forward<Rng>(rng), std::pair{eve::plus, eve::zero}, init);
    }
  };

  inline constexpr auto inclusive_scan_inplace = function_with_traits<inclusive_scan_inplace_>[no_traits];

  template <typename TraitsSupport>
  struct inclusive_scan_to_ : TraitsSupport
  {
    template <zipped_range_pair R, typename Op, typename Zero, typename U>
    EVE_FORCEINLINE void operator()(R r, std::pair<Op, Zero> op_zero, U init) const
    {
      detail::inclusive_scan_common<to_load_store>{}(
        TraitsSupport::get_traits(), r[common_type], op_zero, init);
    }

    template <zipped_range_pair R, typename U>
    EVE_FORCEINLINE auto operator()(R r, U init) const
    {
      operator()(r, std::pair{eve::plus, eve::zero}, init);
    }

    template <typename R1, typename R2, typename Op, typename Zero, typename U>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, std::pair<Op, Zero> op_zero, U init) const
    {
      operator()(zip(std::forward<R1>(r1), std::forward<R2>(r2)), op_zero, init);
    }

    template <typename R1, typename R2, typename U>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, U init) const
    {
      return operator()(zip(std::forward<R1>(r1), std::forward<R2>(r2)), init);
    }
  };

  inline constexpr auto inclusive_scan_to = function_with_traits<inclusive_scan_to_>[no_traits];
}
