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
#include <eve/traits/overload/impl/strict_elementwise.hpp>

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct elementwise_callable
  //!   @brief CRTP base class giving an EVE's @callable the elementwise function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   Elementwise functions in EVE are built using a very common pattern. Inheriting from eve::elementwise_callable
  //!   simplifies the implementation of such @callable by just requiring the definition of the architecture specific
  //!   implementations functions.
  //!
  //!   Elementwise functions in EVE automatically supports masking, aggregated and emulated cases.
  //!   Elementwise @callable are also able to handle mixed SIMD/Scalar calls by performing all the required
  //!   conversions, letting the implementation of the deferred overload named in the EVE_CALLABLE_OBJECT to only
  //!   handle common type cases.
  //!
  //!   @tparam Func          Type of current @callable being implemented.
  //!   @tparam OptionsValues Type of stored options.
  //!   @tparam Options       List of supported option specifications.
  //!
  //!   @see strict_elementwise_callable
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct elementwise_callable : strict_elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_elementwise_callable<Func, OptionsValues, Options...>;
    using ignore = typename base_t::ignore;
    using func_t = typename base_t::func_t;

    template<typename Src, typename Tgt>
    EVE_FORCEINLINE static constexpr Tgt cvt(Src e, as<Tgt>)
    {
      if      constexpr (std::same_as<Src, Tgt>)                       return e;
      else if constexpr (std::same_as<Src, bool> || scalar_value<Src>) return Tgt{e};
      else                                                             return detail::call_convert(e, as_element<Tgt>{});
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto adapt_call(auto arch, O const& opts, T x, Ts... xs) const
    {
      // we test for no logicals first to prevent mishandling bools
      constexpr bool no_logicals = !(eve::logical_value<T> || ... || eve::logical_value<Ts>);
      constexpr bool all_bools   = (std::same_as<T, bool> && ... && std::same_as<Ts, bool>);

      if constexpr (all_bools)
      {
        constexpr bool has_implementation = requires{ func_t::deferred_call(arch, opts, x, xs...); };
        if constexpr(has_implementation) return func_t::deferred_call(arch, opts, x, xs...);
        else
        {
          static_assert ( has_implementation
                        , "[EVE] - Implementation for current logical callable cannot be called or is ambiguous"
                        );
          return ignore{};
        }
      }
      else if constexpr (no_logicals)
      {
        using cv_t  = common_value_t<T, Ts...>;
        using cve_t = element_type_t<cv_t>;

        constexpr auto s_cvt = [](auto e) {
          if constexpr (scalar_value<decltype(e)>) return static_cast<cve_t>(e);
          else                                     return e;
        };

        constexpr bool is_callable = !std::same_as<ignore, decltype(base_t::adapt_call(arch, opts, s_cvt(x), s_cvt(xs)...))>;

        if constexpr (is_callable)     return base_t::adapt_call(arch, opts, s_cvt(x), s_cvt(xs)...);
        else
        {
          constexpr bool is_convertible = requires{ func_t::deferred_call(arch, opts, cv_t{x}, cv_t{xs}...); };

          if constexpr(is_convertible) return func_t::deferred_call(arch, opts, cv_t{x}, cv_t{xs}...);
          else                         return ignore{};
        }
      }
      else
      {
        using          cl_t         = common_logical_t<T, Ts...>;
        constexpr bool any_emulated = (has_emulated_abi_v<T> || ... || has_emulated_abi_v<Ts>);

        if constexpr(any_emulated)  return base_t::behavior(arch, opts, cvt(x, as<cl_t>{}), cvt(xs, as<cl_t>{})...);
        else
        {
          constexpr bool is_callable = !std::same_as<ignore, decltype(base_t::adapt_call(arch, opts, x, xs...))>;

          if constexpr(is_callable) return base_t::behavior(arch, opts, x, xs...);
          else                      return base_t::behavior(arch, opts, cvt(x, as<cl_t>{}), cvt(xs, as<cl_t>{})...);
        }
      }
    }

    template<callable_options O, typename T, typename... Ts>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        constexpr bool supports_call = !std::same_as<ignore, decltype(adapt_call(arch,opts,x0,xs...))>;
        static_assert(supports_call, "[EVE] - Implementation for current elementwise callable cannot be called or is ambiguous");
        return adapt_call(arch, opts, x0, xs...);
      }
      else
      {
        return base_t::behavior(arch, opts, x0, xs...);
      }
    }
  };
}
