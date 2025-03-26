//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/callable.hpp>

namespace eve
{
  namespace detail
  {
    template<typename C, typename T>
    constexpr EVE_FORCEINLINE bool validate_mask_for() noexcept
    {
      if constexpr (scalar_value<T>)
      {
        if constexpr (std::same_as<C, ignore_none_>) return true;
        else if constexpr (C::has_alternative)       return validate_mask_for<typename C::conditional_type, T>();
        else                                         return !(relative_conditional_expr<C> || simd_value<C>);
      }
      else
      {
        return true;
      }
    }

    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE bool validate_mask_for() noexcept
    {
      if constexpr (O::contains(condition_key)) return validate_mask_for<rbr::result::fetch_t<condition_key, O>, T>();
      else                                      return true;
    }

    template< template<typename> class Func
    , typename OptionsValues
    , typename... Options
    >
    struct conditional_callable_impl : callable<Func, OptionsValues, Options...>
    {
      using func_t =  Func<OptionsValues>;

      struct ignore { template<typename T> operator T() { return T{}; } };

      template<callable_options O, typename T, typename... Ts>
      constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
      {
        return func_t::deferred_call(arch, opts, x0, xs...);
      }
    };
  }

  template< template<typename> class Func
  , typename OptionsValues
  , typename... Options
  >
  struct relative_conditional_callable : detail::conditional_callable_impl<Func, OptionsValues, relative_conditional_option, Options...>
  {
    using base_t = detail::conditional_callable_impl<Func, OptionsValues, relative_conditional_option, Options...>;

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      return base_t::behavior(arch, opts, x0, xs...);
    }
  };

  template< template<typename> class Func
  , typename OptionsValues
  , typename... Options
  >
  struct conditional_callable : detail::conditional_callable_impl<Func, OptionsValues, conditional_option, relative_conditional_option, Options...>
  {
    using base_t = detail::conditional_callable_impl<Func, OptionsValues, conditional_option, relative_conditional_option, Options...>;

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      return base_t::behavior(arch, opts, x0, xs...);
    }
  };
}
