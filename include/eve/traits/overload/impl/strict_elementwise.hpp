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
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct strict_elementwise_callable
  //!   @brief CRTP base class giving an EVE's @callable the strict elementwise function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   Elementwise functions in EVE are built using a very common pattern. Inheriting from
  //!   eve::strict_elementwise_callable simplifies the implementation of such @callable by just requiring the
  //!   definition of the architecture specific implementations functions.
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
  //!   @see conditional_callable
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct strict_elementwise_callable : conditional_callable<Func, OptionsValues, Options...>
  {
    using base_t = conditional_callable<Func, OptionsValues, Options...>;
    using func_t =  Func<OptionsValues>;

    struct ignore { template<typename T> operator T() { return T{}; } };

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto adapt_call(auto a, O const& o, T x, Ts... xs) const
    {
      constexpr bool has_implementation         = requires{ func_t::deferred_call(a, o, x, xs...); };
      constexpr bool supports_map_no_conversion = requires{ map(this->derived(), x, xs...); };
      constexpr bool any_emulated               = (has_emulated_abi_v<T> || ... || has_emulated_abi_v<Ts>);
      constexpr bool any_aggregated             = (has_aggregated_abi_v<T> || ... || has_aggregated_abi_v<Ts>);

      if      constexpr(any_aggregated)                             return aggregate(this->derived(), x, xs...);
      else if constexpr(any_emulated && supports_map_no_conversion) return map(this->derived(), x, xs...);
      else if constexpr(has_implementation)                         return func_t::deferred_call(a, o, x, xs...);
      else                                                          return ignore{};
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        constexpr bool supports_call = !std::same_as<ignore, decltype(adapt_call(arch, opts, x0, xs...))>;
        static_assert(supports_call, "[EVE] - Implementation for current strict elementwise callable cannot be called or is ambiguous");
        return adapt_call(arch, opts, x0, xs...);
      }
      else
      {
        return base_t::behavior(arch, opts, x0, xs...);
      }
    }
  };
}
