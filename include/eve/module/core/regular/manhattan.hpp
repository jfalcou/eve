//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/is_infinite.hpp>

namespace eve
{
  template<typename Options>
  struct manhattan_t : tuple_callable<manhattan_t, Options, pedantic_option, saturated_option>
  {
    template<eve::value T0, eve::value T1, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0,T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept  requires(kumi::size_v<Tup> >= 2)  { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var manhattan
//!   @brief Computes the manhattan norm (\f$l_1\f$)  of its arguments.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value... Ts >
//!      auto manhattan(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` :   [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!    The value of the sum of the absolute value of the arguments is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/manhattan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::manhattan[mask](x, ...)` provides a masked
//!     version of `manhattan` which is
//!     equivalent to `if_else(mask, eve::manhattan(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/manhattan.cpp}
//!
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::manhattan)(...)` computes
//!     a pedantic version of `eve::manhattan`.
//!     returning \f$\infty\f$ as soon as one of its parameter is infinite,
//!     regardless of possible `Nan` values.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/manhattan.cpp}
//! @}
//================================================================================================
  inline constexpr auto manhattan = functor<manhattan_t>;

  namespace detail
  {
    template<typename T0,typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    manhattan_(EVE_REQUIRES(cpu_), O const & , T0 a0, T1 a1, Ts... args) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      auto r = eve::add/*TODO[o]*/(abs(r_t(a0)), abs(r_t(a1)), abs(r_t(args))...);
      if constexpr(O::contains(pedantic2))
      {
        auto inf_found = is_infinite(r_t(a0)) || is_infinite(r_t(a1));
        inf_found =  (inf_found || ... || is_infinite(r_t(args)));
        return if_else(inf_found, inf(as(r)), r);
      }
      else
        return r;
    }
  }
}
