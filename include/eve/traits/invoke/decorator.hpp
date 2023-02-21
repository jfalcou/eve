//====================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//====================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/traits/invoke/protocol.hpp>

#include <ostream>

namespace eve::detail
{
  struct mask_ : rbr::as_keyword<mask_>
  {
    using rbr::as_keyword<mask_>::operator=;
    template<typename T> static constexpr bool check()
    {
      return conditional_expr<std::remove_cvref_t<T>>;
    }

    std::ostream& show(std::ostream& os, auto v) const
    {
      return os << "Mask: " << std::boolalpha << v << std::noboolalpha;
    }
  };

  // This is an internal option to carry around the mask from options
  inline constexpr mask_ mask;
}

namespace eve
{
  //================================================================================================
  //! @addtogroup invoke
  //! @{
  //================================================================================================

  //================================================================================================
  //! @struct decorators
  //! @brief Overloading error reporting helper
  //!
  //! eve::decorators gathers decorators and masks that user could apply on a eve::callable to modify
  //! its semantic.
  //!
  //! @tparam Settings Internal settings type
  //================================================================================================
  template <rbr::concepts::settings Settings>
  struct decorators : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr explicit decorators(Options && ... options) : Settings(EVE_FWD(options) ...) {}

    constexpr decorators(Settings const& options) : Settings(options) {}
  };

  /// Deduction guide for eve::decorators
  template <rbr::concepts::option ... Options>
  decorators(Options&& ... options) -> decorators<decltype(rbr::settings(EVE_FWD(options) ...))>;

  //================================================================================================
  //! @struct support_options
  //! @brief  Make an eve::callable responsive to decorators and masks
  //!
  //! eve::callable can inherits from eve::support_options to gain the ability to supports
  //! user-provided decorators and masks to modify its semantic.
  //!
  //! Decorators and masks are gathered via the overloaded `operator[]` that eve::support_options
  //! provides. Decorators and masks can then be chained via multiple application of said operator.
  //!
  //! The handling of those decorators and masks are left to the implementation of the callable
  //! itself.
  //!
  //! @tparam Tag eve::callable using eve::support_options
  //================================================================================================
  template<typename Tag> struct support_options
  {
    template<typename Settings> struct fn
    {
      using callable_tag_type = void;

      template<typename Options>
      EVE_FORCEINLINE auto operator[](Options&& o) const
      {
        auto new_opts = rbr::merge(rbr::settings{o}, opts);
        return fn<decltype(new_opts)>{new_opts};
      }

      EVE_FORCEINLINE auto operator[](conditional_expr auto m) const
      {
        return (*this)[detail::mask = m];
      }

      template<std::same_as<bool> T>
      EVE_FORCEINLINE constexpr auto operator[](T c) const noexcept
      {
        using type = std::conditional_t<std::same_as<bool,T>,std::uint8_t,T>;
        return (*this)[detail::mask = if_(logical<type>(c))];
      }

      template<typename... Args>
      EVE_FORCEINLINE auto operator()(Args&&... x) const
      -> tag_invoke_result<Tag, current_api_type, decorators<Settings>, Args&&...>
      {
        return tag_invoke(Tag{}, current_api, decorators{opts}, EVE_FWD(x)...);
      }

#if !defined(EVE_ALLOW_VERBOSE_CALLABLE_ERRORS)
      template<typename... T>
      unsupported_call<Tag, Settings, T...> operator()(T&&...x) const noexcept
      requires(!requires(decorators<Settings> const& s)
                { tag_invoke(Tag{}, current_api, s, EVE_FWD(x)...); }
              ) = delete;
#endif

      Settings opts;
    };

    //! @brief Modify the semantic of current eve::callable via a bundle of decorators or masks
    template<rbr::concepts::settings Settings>
    EVE_FORCEINLINE auto operator[](Settings const& s) const
    {
      return fn<decorators<Settings>>{decorators{s}};
    }

    //! @brief Modify the semantic of current eve::callable by a decorator
    template<rbr::concepts::option Options>
    EVE_FORCEINLINE auto operator[](Options const& o) const
    {
      return (*this)[decorators{o}];
    }

    //! @brief Modify the semantic of current eve::callable by a mask
    EVE_FORCEINLINE auto operator[](conditional_expr auto m) const
    {
      return (*this)[detail::mask = m];
    }

    //! @brief Modify the semantic of current eve::callable by a boolean mask
    template<std::same_as<bool> T>
    EVE_FORCEINLINE constexpr auto operator[](T c) const noexcept
    {
      using type = std::conditional_t<std::same_as<bool,T>,std::uint8_t,T>;
      return (*this)[detail::mask = if_(logical<type>(c))];
    }
  };

  //================================================================================================
  //! @}
  //================================================================================================
}

//==================================================================================================
// Basic hook for tag_invoke that just forward to the proper deferred call if possible when dealing
// callable being decorated.
// This specialization lives in eve::tags to be found by ADL as tag themselves will be defines
// in eve::tags.
//==================================================================================================
namespace eve::tags
{
  template<typename S>
  constexpr auto tag_invoke(deferred_callable auto tag, auto arch, decorators<S> opts, auto... x)
  noexcept(noexcept(tag.deferred_call(arch, opts, x...)))
          ->  decltype(tag.deferred_call(arch, opts, x...))
  {
    return tag.deferred_call(arch, opts, x...);
  }
}
