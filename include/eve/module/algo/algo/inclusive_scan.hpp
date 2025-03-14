//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/array_utils.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/algo/algo/traits.hpp>


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

        delegate(Op o, Zero z, Wide i) : op(o), zero(z), running_sum(i) {}

        EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
        {
          auto load_it  = LoadStore::load_it(it);
          auto store_it = LoadStore::store_it(it);

          auto xs = eve::load[ignore.else_(eve::as_value(zero, as<Wide> {}))](load_it);
          xs      = eve::scan(xs, op, zero);
          xs      = op(xs, running_sum);
          running_sum = Wide(xs.back());

          eve::store[ignore](xs, store_it);
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
        auto processed = preprocess_range(tr, EVE_FWD(rng));
        if( processed.begin() == processed.end() ) return;

        using I      = decltype(processed.begin());
        using wide_t = eve::wide<U, iterator_cardinal_t<I>>;

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
        TraitsSupport::get_traits(), views::convert(EVE_FWD(rng), eve::as<U>{}), op_zero, init);
    }

    template <relaxed_range Rng, typename U>
    EVE_FORCEINLINE void operator()(Rng&& rng, U init) const
    {
      operator()(EVE_FWD(rng), std::pair{eve::add, eve::zero}, init);
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
        TraitsSupport::get_traits(), r[force_type<U>], op_zero, init);
    }

    template <zipped_range_pair R, typename U>
    EVE_FORCEINLINE auto operator()(R r, U init) const
    {
      operator()(r, std::pair{eve::add, eve::zero}, init);
    }

    template <typename R1, typename R2, typename Op, typename Zero, typename U>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, std::pair<Op, Zero> op_zero, U init) const
    {
      operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)), op_zero, init);
    }

    template <typename R1, typename R2, typename U>
      requires zip_to_range<R1, R2>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, U init) const
    {
      return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)), init);
    }
  };

  inline constexpr auto inclusive_scan_to = function_with_traits<inclusive_scan_to_>[no_traits];
}
