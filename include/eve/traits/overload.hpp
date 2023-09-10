//======================================================================================================================
//! @file
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/logical.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>

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
  //!   @concept callable
  //!   @brief **EVE** callable
  //!
  //!   A type `T` satisfies eve::callable if and only if it is tagged as such manually.
  //!
  //!   @tparam T  T type for the @callable to check
  //! @}
  //====================================================================================================================
  template<typename T, typename...>
  concept callable = requires(T const&) { typename T::callable_tag_type; };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //    @concept decorated_callable
  //    @brief Concept modelling the fact a eve::callable has decorations
  //!   @tparam T  T type for the @callable to check
  //! @}
  //====================================================================================================================
  template<typename T, typename...>
  concept decorated_callable = requires(T const&)
  {
    typename T::is_decorated_callable;
  };
}

//======================================================================================================================
//! @addtogroup extensions
//! @{
//!   @def   EVE_CALLABLE_OBJECT_FROM
//!   @brief Generate the generic function interface for any EVE-compatible @callable
//!
//!   Use inside a @callable definition to generate the required EVE protocol of function's resolution based on type
//!   and architecture informations.
//!
//!   @param NS   Namespace in which specialization of the @callable will be found. This namespace must have been
//!               registered via EVE_CALLABLE_NAMESPACE.
//!   @param TYPE Current @callable type
//!   @param NAME Function identifier for overloads. Calls to `NS::NAME` are supposed to succeed.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object_from.cpp}
//! @}
//======================================================================================================================
#define EVE_CALLABLE_OBJECT_FROM(NS,TYPE,NAME)                                                                         \
template<typename... Args>                                                                                             \
EVE_FORCEINLINE constexpr auto operator()(Args&&... args) const                                                        \
-> decltype(std::declval<TYPE>().call(std::declval<Args>()...))                                                        \
{                                                                                                                      \
  if constexpr(eve::decorated_callable<TYPE,Args...>)                                                                  \
    return TYPE::deferred_call(eve::current_api, eve::detail::defaults<TYPE,Args...>(), EVE_FWD(args)...);             \
  else                                                                                                                 \
    return TYPE::deferred_call(eve::current_api, EVE_FWD(args)...);                                                    \
}                                                                                                                      \
static EVE_FORCEINLINE auto deferred_call(auto arch, auto&&...args) noexcept                                           \
    -> decltype(NAME(NS::adl_helper, arch, EVE_FWD(args)...))                                                          \
requires(requires { NAME(NS::adl_helper, arch, EVE_FWD(args)...); })                                                   \
{                                                                                                                      \
  return NAME(NS::adl_helper, arch, EVE_FWD(args)...);                                                                 \
}                                                                                                                      \
template<typename... Args>                                                                                             \
static EVE_FORCEINLINE auto deferred_call(auto arch, Args&&...args) noexcept                                           \
requires(!requires { NAME(NS::adl_helper, arch, EVE_FWD(args)...); })                                                  \
{                                                                                                                      \
  return eve::detail::default_behavior<TYPE,Args...>::call(arch, EVE_FWD(args)...);                                    \
}                                                                                                                      \
using callable_tag_type     = TYPE                                                                                     \
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
//!   @def   EVE_CALLABLE_OBJECT
//!   @brief Generate the generic function interface for an actual eve::callable
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
//!   @groupheader{Example}
//!
//!   @godbolt{doc/traits/callable_object.cpp}
//! @}
//======================================================================================================================
#define EVE_CALLABLE_OBJECT(TYPE,NAME) EVE_CALLABLE_OBJECT_FROM(eve::detail,TYPE,NAME)


// Flag a function to support delayed calls on given architecture
#define EVE_EXPECTS(ARCH) adl_helper_t const &, ARCH const &

// Register eve::detail as the deferred namespace by default
namespace eve::detail { EVE_CALLABLE_NAMESPACE(); }

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct decorators
  //!   @brief Wrapper class around bundle of options passed to eve::callable
  //!
  //!   eve::callable can be decorated with options. eve::decorators is used internally to gather all those options
  //!   in a @raberu settings instance for further processing.
  //!
  //!   @tparam Settings @raberu settings type to wrap.
  //! @}
  //====================================================================================================================
  template <rbr::concepts::settings Settings>
  struct decorators : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr EVE_FORCEINLINE explicit decorators(Options && ... options) : Settings(EVE_FWD(options) ...) {}

    template <typename... Options>
    constexpr EVE_FORCEINLINE decorators(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::concepts::option ... Options>
  decorators(Options&& ... options) -> decorators<decltype(rbr::settings(EVE_FWD(options) ...))>;

  template <typename... Options>
  decorators(rbr::settings<Options...> const&)  -> decorators<rbr::settings<Options...>>;
}

//======================================================================================================================
// Overload's helpers
//======================================================================================================================
namespace eve::detail
{
  //====================================================================================================================
  // Delay the access to defaults() to after the proper operator() has been selected.
  //====================================================================================================================
  template<typename T, typename...> EVE_FORCEINLINE constexpr auto defaults() { return T::defaults(); }

  //====================================================================================================================
  // Internal concept checking if a default behavior is defined for a given callable
  //====================================================================================================================
  template<typename T, typename Arch, typename... Args>
  concept supports_default_behavior = requires(Arch const& arch, Args&&... args)
  {
    { T::behavior::call(arch,EVE_FWD(args)...) };
  };

  //====================================================================================================================
  // Internal concept checking if an option is supported by a specification
  //====================================================================================================================
  template<typename Spec, typename O>
  concept supports_option = requires(Spec sp, O const& o) { { sp[o] }; };

  //====================================================================================================================
  // Internal concept checking if an option is supported by a any specification in a given subset
  //====================================================================================================================
  template<typename O, typename... Specs>
  concept is_supported = (supports_option<Specs,O> || ... );

  //====================================================================================================================
  // Aggregates and handle the default behavior of a given callable when no overload are found
  // Reports hard error if no overload nor default behavior are available for T.
  //====================================================================================================================
  template<typename T, typename...>
  struct default_behavior
  {
    template<typename Arch, typename... Args>
    EVE_FORCEINLINE
    static constexpr auto call(Arch const& arch, Args&&... args) requires(supports_default_behavior<T,Arch,Args...>)
    {
      return T::behavior::call(arch,EVE_FWD(args)...);
    }

    template<typename Arch, typename... Args>
    EVE_FORCEINLINE
    static constexpr auto call(Arch const&, Args&&...) requires(!supports_default_behavior<T,Arch,Args...>)
    {
      static_assert(supports_default_behavior<T, Arch, Args...>, "[EVE] - Incomplete callable object implementation");
    }
  };

  //====================================================================================================================
  // Internal option carrying conditional mask or conditional expressions
  //====================================================================================================================
  struct condition_ : rbr::as_keyword<condition_>
  {
    using rbr::as_keyword<condition_>::operator=;
    template<typename T> static constexpr bool check()
    {
      return conditional_expr<std::remove_cvref_t<T>> || logical_value<std::remove_cvref_t<T>>;
    }
  };

  inline constexpr condition_ condition;

  //====================================================================================================================
  // Intermediate type for handling chains of option like in func[opt1 = y][opt2 = x][ignore](...)
  //====================================================================================================================
  template<typename Tag, typename Settings, typename... Specs> struct decorated_fn
  {
    using callable_tag_type = void;

    template<is_supported<Specs...> O>
    EVE_FORCEINLINE auto operator[](O const& o) const
    {
      if constexpr(rbr::concepts::option<O>)
      {
        // Merge new option with current ones
        auto new_opts = decorators{rbr::merge(rbr::settings{o}, opts)};
        return decorated_fn<Tag,decltype(new_opts),Specs...>{new_opts};
      }
      // Wrap conditionals and booleans into a condition option
      else if constexpr(conditional_expr<O> || eve::logical_value<O>)
      {
        return (*this)[condition = o];
      }
      else if constexpr(std::same_as<O,bool>)
      {
        using type = std::conditional_t<std::same_as<bool,O>,std::uint8_t,O>;
        return (*this)[condition = if_(logical<type>(o))];
      }
    }

    // Behave as a callable but pass the current bundle of options to the deferred_call handler
    template<typename... Args>
    EVE_FORCEINLINE constexpr auto operator()(Args&&... args) const
    -> decltype(std::declval<Tag>().call(std::declval<Args>()...))
    {
      return Tag::deferred_call(eve::current_api, opts, EVE_FWD(args)...);
    }

    Settings opts;
  };
}

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct supports
  //!   @brief Helper class to aggregate options handlers
  //!
  //!   eve::callable can be decorated with options. eve::supports is used to list all subset of options a given EVE
  //!   @callable is allowed to support and to handle the default values of such subsets.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!   @tparam Specs List of options specifications to support
  //! @}
  //====================================================================================================================
  template<typename Tag, typename... Specs>
  struct supports
  {
    using is_decorated_callable = void;

    // Aggregate all defaults from all Specs
    EVE_FORCEINLINE static constexpr auto defaults() noexcept
    {
      return  kumi::fold_left ( [](auto const& acc, auto const& e) { return decorators{rbr::merge(e,acc)}; }
                              , kumi::make_tuple(Specs::defaults()...)
                              );
    }

    //==================================================================================================================
    //! @brief Adds an option to current callable
    //!
    //! If the option `o` is supported by one of the specifications `Spec`, build a new @callable that will behave as
    //! an instance of `Tag` except the option `o` is passed inside an eve::decorators as an additional parameter.
    //!
    //! Does not participate in overload resolution if `o` is not support by any option specifications.
    //!
    //! @param o Option to add to current's @callable setup
    //! @return A eve::decorated_callable behaving as `Tag` but with the options `o` set.
    //==================================================================================================================
    template<detail::is_supported<Specs...> O>
    EVE_FORCEINLINE auto operator[](O const& o) const
    {
      if constexpr(rbr::concepts::option<O>)
      {
        auto base = decorators{o};
        auto opts = rbr::merge(base,defaults());
        return detail::decorated_fn<Tag,decltype(decorators{opts}),Specs...>{opts};
      }
      else if constexpr(conditional_expr<O> || eve::logical_value<O>)
      {
        return (*this)[detail::condition = o];
      }
      else if constexpr(std::same_as<O,bool>)
      {
        using type = std::conditional_t<std::same_as<bool,O>,std::uint8_t,O>;
        return (*this)[detail::condition = if_(logical<type>(o))];
      }
    }
  };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct conditional
  //!   @brief Option specification for decoration via conditional value and expressions
  //!
  //!   eve::conditional is an option specification that can be used when defining a eve::callable type to make it
  //!   supports decoration via `bool`, eve::logical, any eve::conditional_expr or any eve::relative_conditional_expr.
  //! @}
  //====================================================================================================================
  struct conditional
  {
    auto operator[](bool)                                                   -> void;
    auto operator[](eve::logical_value auto const&)                         -> void;
    auto operator[](eve::conditional_expr auto const&)                      -> void;
    auto operator[](rbr::concepts::exactly<detail::condition> auto const&)  -> void;

    /// Default settings of eve::conditional is eve::ignore_none
    EVE_FORCEINLINE static constexpr auto defaults() noexcept { return decorators{detail::condition = ignore_none};  }
  };
}
