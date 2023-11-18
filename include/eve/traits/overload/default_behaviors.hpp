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
        if constexpr(match_option<condition_key, O, ignore_none_>) return constant_value;
        else  return detail::mask_op(opts[condition_key], detail::return_2nd, 0, constant_value);
      }
    }
  };
}
