//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/function/conditional.hpp>

namespace eve
{
  //====================================================================================================================

  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct callable : decorated_with<OptionsValues, Options...>
  {
    using base = decorated_with<OptionsValues, Options...>;

    template<typename T>
    auto operator[](T t) const
    requires( requires(base const& b) { b[t];} )
    {
      auto new_traits = base::operator[](t);
      return  Func<decltype(new_traits)>{new_traits};
    }

    template<typename T> void operator[](T t) const =delete;

    template<typename... Args>
    constexpr auto behavior(auto arch, Args&&... args) const
    {
      return Func<OptionsValues>::deferred_call(arch, EVE_FWD(args)...);
    }
  };

  //====================================================================================================================

  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct elementwise
  {
    template<typename... Ts> constexpr auto behavior(auto arch, Ts const&... xs)
    requires( simd_value<Ts> || ...)
    {
      using tag_t = Func<OptionsValues>;

      // If a deferred call is present, let's call it
      if constexpr( requires{ tag_t::deferred_call(arch, xs...); } )
      {
        return tag_t::deferred_call(arch, xs...);
      }
      else
      {
        // if not, try to slice/aggregate from smaller wides or to map the scalar version
        if constexpr((has_aggregated_abi_v<Ts> || ...)) return aggregate(tag_t{}, xs...);
        else                                            return map(tag_t{}, xs...);
      }
    }
  };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct constant_callable
  //!   @brief CRTP base class giving an EVE's @callable the constant function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   Constants functions in EVE are built using a very common pattern. Inheriting from eve::constant simplifies the
  //!   implementation of such eve::callable by just requiring your eve::callable type to implement a static `value`
  //!   member function that provides the constant value using two parameters:
  //!     * an eve::options pack containing potential decorators passed to the constant.
  //!     * an eve::as instance to specify the output type.
  //!
  //!   Constant functions in EVE also supports masking, which is directly implemented in eve::constant.
  //!
  //!   @note The deferred overload named in the EVE_CALLABLE_OBJECT macro process is still available if an architecture
  //!   specific implementation of any given constant is required.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_constant.cpp}
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct constant_callable : callable<Func, OptionsValues, conditional_option, Options...>
  {
    template<typename O, typename T>
    constexpr auto behavior(auto, O const& opts, as<T> const& target) const
    {
      // Compute the raw constant
      auto const constant_value = [&]()
      {
        if      constexpr( requires{ Func<OptionsValues>::value(opts, target); } )
          return Func<OptionsValues>::value(opts, target);
        else if constexpr( requires{ Func<OptionsValues>::value(target); } )
          return Func<OptionsValues>::value(target);
      }();

      // Apply a mask if any and replace missing values with 0 if no alternative is provided
      if constexpr(option_type_is<condition_key, O, ignore_none_>) return constant_value;
      else  return detail::mask_op(opts[condition_key],[](auto, auto x) { return x; }, 0, constant_value);
    }
  };
}
