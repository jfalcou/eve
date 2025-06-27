//======================================================================================================================
//! @file
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/as_translation.hpp>

//======================================================================================================================
//! @addtogroup simd
//! @{
//!   @defgroup extensions Extensions points
//!   @brief Macros, classes and functions designed to extend EVE externally.
//! @}
//======================================================================================================================

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @concept callable_object
  //!   @brief **EVE** callable object
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   A type `T` satisfies eve::callable_object if and only if it is tagged as such manually.
  //!
  //!   @tparam T  T type for the @callable to check
  //! @}
  //====================================================================================================================
  template<typename T, typename...>
  concept callable_object = requires(T const&) { typename T::callable_tag_type; };
}

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def   EVE_CALLABLE_OBJECT_FROM
//!   @brief Generate the generic function interface for any EVE-compatible @callable
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Use inside a @callable definition to generate the required EVE protocol of function's resolution based on type
//!   and architecture informations.
//!
//!   @param NS   Namespace in which specialization of the @callable will be found. This namespace must have been
//!               registered via EVE_CALLABLE_NAMESPACE.
//!   @param TYPE Current @callable type
//!   @param NAME Function identifier for overloads. Calls to `NS::NAME` are supposed to succeed.
//!
//!   @see EVE_CALLABLE_OBJECT
//!   @see EVE_CALLABLE_NAMESPACE
//!
//!   @groupheader{Usage}
//!
//!   @ref EVE_CALLABLE_OBJECT_FROM generates the expected code for defining a EVE @callable. EVE @callable are function
//!   object which supports decorators and use an external function to specify its implementation.
//!
//!   @ref EVE_CALLABLE_OBJECT_FROM relies on its enclosing type to provide at least one declaration of a member function
//!   named `call` which represent the expected prototype of the function object, including potential constraints, and
//!   its associated return type. @ref EVE_CALLABLE_OBJECT also relies on the existence of an appropriate number of
//!   function overloads named `NAME` defined in the `NS` namespace. Those function contains the implementation
//!   of the @callable overload for each pre-defined function.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object_from.cpp}
//! @}
//======================================================================================================================
#define EVE_CALLABLE_OBJECT_FROM(NS,TYPE,NAME)                                                                         \
template<typename... Args>                                                                                             \
static EVE_FORCEINLINE constexpr auto deferred_call(auto arch, Args&&...args) noexcept                                 \
-> decltype(NAME(NS::adl_helper, arch, EVE_FWD(args)...))                                                              \
{                                                                                                                      \
  return NAME( NS::adl_helper, arch, EVE_FWD(args)...);                                                                \
}                                                                                                                      \
using callable_tag_type     = TYPE                                                                                     \
/**/

// THIS MACRO IS DUPLICATED TO ENSURE ERROR MESSAGE QUALITY
//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def   EVE_CALLABLE_OBJECT
//!   @brief Generate the generic function interface for an actual eve::callable
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Use inside a @callable definition to generate the required EVE protocol of function's resolution based on type
//!   and architecture informations using overload from the `eve::detail` namespace.
//!
//!   @warning @ref EVE_CALLABLE_OBJECT is mostly used for EVE @callable definition. If you want to use EVE's overload
//!   facility for your own library, use @ref EVE_CALLABLE_OBJECT_FROM.
//!
//!   @param TYPE Current @callable type
//!   @param NAME Function identifier for overloads. Calls to `eve::detail::NAME` are supposed to succeed.
//!
//!   @groupheader{Usage}
//!
//!   @ref EVE_CALLABLE_OBJECT generates the expected code for defining a EVE @callable. EVE @callable are function
//!   object which supports decorators and use an external function to specify its implementation.
//!
//!   @ref EVE_CALLABLE_OBJECT relies on its enclosing type to provide at least one declaration of a member function
//!   named `call` which represent the expected prototype of the function object, including potential constraints, and
//!   its associated return type. @ref EVE_CALLABLE_OBJECT also relies on the existence of an appropriate number of
//!   function overloads named `NAME` defined in the eve::detail namespace. Those function contains the implementation
//!   of the @callable overload for each pre-defined function.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object.cpp}
//! @}
//======================================================================================================================
#define EVE_CALLABLE_OBJECT(TYPE,NAME)                                                                                 \
template<typename... Args>                                                                                             \
static EVE_FORCEINLINE constexpr auto deferred_call(auto arch, Args&&...args) noexcept                                 \
-> decltype(NAME(eve::detail::adl_helper, arch, EVE_FWD(args)...))                                                     \
{                                                                                                                      \
  return NAME(eve::detail::adl_helper, arch, EVE_FWD(args)...);                                                        \
}                                                                                                                      \
using callable_tag_type     = TYPE                                                                                     \
/**/

namespace eve::detail
{
  template<typename Callable, typename... Args>
  EVE_FORCEINLINE constexpr auto dispatch_call_impl(Callable const& c, Args&&... args)
  {
    using r_t = decltype(c(EVE_FWD(args)...));

    if (std::same_as<r_t, void>)
    {
      c.behavior(eve::current_api, c.options(), eve::translate(EVE_FWD(args))...);
    }
    else
    {
      auto res = c.behavior(eve::current_api, c.options(), eve::translate(EVE_FWD(args))...);
      return std::bit_cast<r_t>(res);
    }
  }
}

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def EVE_DISPATCH_CALL
//!   @brief Generate the proper call to current EVE's @callable implementation
//! @}
//======================================================================================================================
#define EVE_DISPATCH_CALL(...) eve::detail::dispatch_call_impl(*this, __VA_ARGS__)
/**/

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def EVE_CALLABLE_NAMESPACE
//!   @brief Register a namespace as suitable for containing eve::callable overloads.
//! @}
//======================================================================================================================
#define EVE_CALLABLE_NAMESPACE()                                                                                       \
struct adl_helper_t {};                                                                                                \
inline constexpr auto adl_helper = adl_helper_t {}                                                                     \
/**/

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def EVE_REQUIRES
//!   @brief Flag a function to support delayed calls on given architecture
//! @}
//======================================================================================================================
#define EVE_REQUIRES(ARCH) adl_helper_t const &, ARCH const &
#define EVE_TARGETS(ARCH)   adl_helper_t{}, ARCH{}

// Register eve::detail as the deferred namespace by default
namespace eve::detail { EVE_CALLABLE_NAMESPACE(); }

namespace eve
{
  template<auto Func, typename... Ts>
  using result_t = decltype(Func(std::declval<Ts>()...));
}
