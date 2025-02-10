//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once


#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/as_element.hpp>
#include <eve/forward.hpp>
#include <eve/traits/overload/impl/callable.hpp>

namespace eve
{
  template< template<typename> class Func
  , typename OptionsValues
  , typename... Options
  >
  struct relative_conditional_callable : callable<Func, OptionsValues, relative_conditional_option, Options...>
  {
    using base_t = callable<Func, OptionsValues, relative_conditional_option, Options...>;
    using func_t =  Func<OptionsValues>;

    struct ignore { template<typename T> operator T() { return T{}; } };

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        return base_t::behavior(arch, opts, x0, xs...);
      }
      else
      {
        // Grab the condition and drop it from the callable
        auto[cond, rmv_cond] = opts.extract(condition_key);
        using cond_t =  decltype(cond);
        [[maybe_unused]] Func<decltype(rmv_cond)> const f{rmv_cond};

        // Check that the mask and the value are of same kind if simd
        constexpr bool compatible_mask = !(simd_value<decltype(cond.mask(as(x0)))> && scalar_value<decltype(f(x0, xs...))>);
        static_assert(compatible_mask, "[EVE] - Scalar values can't be masked by SIMD logicals.");

        // Shush any other cascading errors
        if constexpr(!compatible_mask) return ignore{};
        // Handle masking SIMD with scalar with ?: to prevent issues in masking optimizations
        else
        // Or proceed to find the proper way to handle this masked call
        {
          // Check if func_(arch, cond, opts, ...) exists
          constexpr bool supports_mask  = requires(cond_t c){ func_t::deferred_call(arch, c, opts, x0, xs...); };

          if constexpr (supports_mask)
          {
            // If the conditional call is supported, call it
            // Note that as we pruned out ignore_none earlier, the only special cases inside this call is ignore_all
            return func_t::deferred_call(arch, cond, opts, x0, xs...);
          }
          else
          {
            // if not, call the non-masked version then mask piecewise
            return detail::mask_op(cond, detail::return_2nd, x0, f(x0, xs...));
          }
        }
      }
    }
  };
}
