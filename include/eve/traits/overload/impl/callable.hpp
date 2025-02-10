//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct callable
  //!   @brief CRTP base class defining an EVE's @callable.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   All EVE @callable use a similar protocol to find and call proper architecture or type specific implementation.
  //!   This protocol includes options checks and management and proper level of error reporting.
  //!   eve::callable is the most general base class for defining such a @callable without having to manually handles
  //!   all these details.
  //!
  //!   @tparam Func          Type of current @callable being implemented.
  //!   @tparam OptionsValues Type of stored options.
  //!   @tparam Options       List of supported option specifications.
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_object.cpp}
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct callable : decorated_with<OptionsValues, Options...>
  {
    using base = decorated_with<OptionsValues, Options...>;

    template<callable_options O> EVE_FORCEINLINE constexpr auto operator[](O const& opts) const
    {
      return Func<O>{opts};
    }

    template<typename T>
    EVE_FORCEINLINE constexpr auto operator[](T t) const requires( requires(base const& b) { b[t];} )
    {
      auto new_traits = base::operator[](t);
      return  Func<decltype(new_traits)>{new_traits};
    }

    // TEMPORARY - Map old decorator to the new ones
    template<typename T> EVE_FORCEINLINE auto operator[](T const& t) const requires(decorator<T>)
    {
      return (*this)[as_option(t)];
    }

    template<typename T> EVE_FORCEINLINE void operator[](T const& t) const
    // This requires is also TEMPORARY
    requires( !callable_options<T> && !requires(base const& b) { b[t];} && !decorator<T>) =delete;

    template<typename... Args>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, Args&&... args) const
    {
      return Func<OptionsValues>::deferred_call(arch, EVE_FWD(args)...);
    }

    protected:
    EVE_FORCEINLINE constexpr
    Func<OptionsValues> const& derived() const { return static_cast<Func<OptionsValues>const&>(*this); }

    //! Checks if two callable are instances of the same function
    template<template<typename> class F2, typename OV2, typename... O2>
    friend constexpr bool operator==(callable const&, callable<F2,OV2,O2...> const&)  { return false; }

    friend constexpr bool operator==(callable const&, callable const&)                { return true;  }
  };

  namespace detail
  {
    inline constexpr struct { EVE_FORCEINLINE auto operator()(auto, auto x) const { return x; } } return_2nd = {};
  }
}
