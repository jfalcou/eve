//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex/regular/traits.hpp>
#include <eve/module/core.hpp>
#include <eve/traits/as_floating_point.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var i
  //!
  //! @brief Callable object computing the pure imaginary (\f$i\f$) value.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the i constant                                    |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate<eve::floating_value T> T operator()(eve::as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::i(as<T>())` is semantically equivalent to  `eve::complex{0,T{1}`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/regular/i.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(i_, i);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto i_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return eve::as_complex_t<as_real_t<T>>{0,1};
    }

    // Integration with other elements
    template<value Z> EVE_FORCEINLINE auto operator+(Z lhs, callable_i_ const& ii) noexcept
    {
      if constexpr( is_complex_v<Z> ) return lhs += ii;
      else
      {
        as_complex_t<as_floating_point_t<Z>> that(lhs,0);
        return that += ii;
      }
    }

    template<value Z> EVE_FORCEINLINE auto operator+(callable_i_ const& ii, Z rhs ) noexcept
    {
      return rhs + ii;
    }

    template<value Z> EVE_FORCEINLINE auto operator-(Z lhs, callable_i_ const& ii) noexcept
    {
      if constexpr( is_complex_v<Z> ) return lhs -= ii;
      else
      {
        as_complex_t<as_floating_point_t<Z>> that(lhs,0);
        return that -= ii;
      }
    }

    template<value Z> EVE_FORCEINLINE auto operator-(callable_i_ const&, Z rhs ) noexcept
    {
      if constexpr( is_complex_v<Z> )
      {
        auto [r,i] = rhs;
        return Z{-r, 1 - i};
      }
      else
      {
        return as_complex_t<as_floating_point_t<Z>>(-rhs,1);
      }
    }

    template<value Z> EVE_FORCEINLINE auto operator*(Z lhs, callable_i_ const& ii) noexcept
    {
      if constexpr( is_complex_v<Z> ) return lhs *= ii;
      else                            return as_complex_t<as_floating_point_t<Z>>(0, lhs);
    }

    template<value Z> EVE_FORCEINLINE auto operator*(callable_i_ const& ii, Z rhs ) noexcept
    {
      return rhs * ii;
    }

    template<value Z> EVE_FORCEINLINE auto operator/(Z lhs, callable_i_ const& ii) noexcept
    {
      if constexpr( is_complex_v<Z> ) return lhs /= ii;
      else                            return as_complex_t<as_floating_point_t<Z>>(0, -lhs);
    }

    template<value Z> EVE_FORCEINLINE auto operator/(callable_i_ const&, Z rhs ) noexcept
    {
      if constexpr( is_complex_v<Z> )
      {
        auto [r,i] = rhs;
        auto m = r*r+i*i;
        return Z(i/m, r/m);
      }
      else
      {
        using f_t = as_floating_point_t<Z>;
        return as_complex_t<f_t>(0,f_t{1}/rhs);
      }
    }
  }

  namespace detail
  {
    template<value T0> auto add_(EVE_SUPPORTS(cpu_), T0 a0, callable_i_) noexcept
    {
      return a0 + eve::i;
    }

    template<value T0> auto sub_(EVE_SUPPORTS(cpu_), T0 a0, callable_i_) noexcept
    {
      return a0 - eve::i;
    }

    template<value T0> auto mul_(EVE_SUPPORTS(cpu_), T0 a0, callable_i_) noexcept
    {
      return a0 * eve::i;
    }

    template<value T0> auto div_(EVE_SUPPORTS(cpu_), T0 a0, callable_i_) noexcept
    {
      return a0 / eve::i;
    }

    template<value T0> auto add_(EVE_SUPPORTS(cpu_), callable_i_, T0 a0) noexcept
    {
      return eve::i + a0;
    }

    template<value T0> auto sub_(EVE_SUPPORTS(cpu_), callable_i_, T0 a0) noexcept
    {
      return eve::i - a0;
    }

    template<value T0> auto mul_(EVE_SUPPORTS(cpu_), callable_i_, T0 a0) noexcept
    {
      return eve::i * a0;
    }

    template<value T0> auto div_(EVE_SUPPORTS(cpu_), callable_i_, T0 a0) noexcept
    {
      return eve::i / a0;
    }
  }

  template<typename T>  struct as_wide_as<T, callable_i_> { using type = T; };
  template<typename U>  struct as_wide_as<callable_i_, U> { using type = U; };
}
