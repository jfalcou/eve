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
  namespace detail
  {
    inline constexpr struct { EVE_FORCEINLINE auto operator()(auto, auto x) const { return x; } } return_2nd = {};
  }

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
    constexpr auto operator[](T t) const
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

    protected:
    constexpr Func<OptionsValues> const& derived() const { return static_cast<Func<OptionsValues>>(*this); }
  };

  //====================================================================================================================

  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct elementwise_callable : callable<Func, OptionsValues, conditional_option, Options...>
  {
    template<callable_options O, typename T, typename... Ts>
    constexpr auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    {
      using func_t                =  Func<OptionsValues>;
      constexpr bool is_supported = requires{ func_t::deferred_call(arch, opts, x0, xs...); };
      constexpr bool any_simd     = (simd_value<T> || ... || simd_value<Ts>);

      // Are we dealing with a no-condition call ?
      if constexpr( option_type_is<condition_key, O, ignore_none_> )
      {
        // If a deferred call is present, let's call it
        if      constexpr( is_supported )  return func_t::deferred_call(arch, opts, x0, xs...);
        else if constexpr( any_simd )
        {
          // if not, try to slice/aggregate from smaller wides or to map the scalar version
          if constexpr((has_aggregated_abi_v<Ts> || ...)) return aggregate(this->derived(), x0, xs...);
          else                                            return map(this->derived(), x0, xs...);
        }
      }
      else
      {
        // Grab the condition
        auto const cond     = opts[condition_key];

        // Drop the conditional and process the function call with the universal masker
        auto const rmv_cond = options{rbr::drop(condition_key, opts)};
        auto const f        = Func<decltype(rmv_cond)>{rmv_cond};

        // If the conditional call is supported, call it
        if      constexpr( is_supported ) return detail::mask_op(cond, f, x0, xs...);
        // if not, call the non-masked version then mask piecewise
        else if constexpr( any_simd )     return detail::mask_op(cond, detail::return_2nd, x0, f(x0,xs...));
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
    constexpr auto behavior(auto arch, O const& opts, as<T> const& target) const
    {
      using func_t                =  Func<OptionsValues>;
      if constexpr( requires{ func_t::deferred_call(arch, opts, target); } )
      {
        return func_t::deferred_call(arch, opts, target);
      }
      else
      {
        // Compute the raw constant
        auto const constant_value = Func<OptionsValues>::value(target,opts);

        // Apply a mask if any and replace missing values with 0 if no alternative is provided
        if constexpr(option_type_is<condition_key, O, ignore_none_>) return constant_value;
        else  return detail::mask_op(opts[condition_key], detail::return_2nd, 0, constant_value);
      }
    }
  };
}
