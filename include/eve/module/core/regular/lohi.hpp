/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/shuffle.hpp>
#include <eve/module/core/zip.hpp>
#include <bit>

namespace eve
{
template<typename Options>
struct lohi_t : elementwise_callable<lohi_t, Options>
{
  template<typename T>
  struct result
  {
    using base = as_wide_as_t<detail::downgrade_t<as_integer_t<element_type_t<T>,unsigned>>,T>;
    using type = zipped<base, base>;
  };

  template<eve::value T>
  constexpr EVE_FORCEINLINE typename result<T>::type operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(lohi_t, lohi_);
};

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var lohi
//!   @brief Computes the the lohi pair of values.
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
//!      template< eve::value T >
//!      auto lohi(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes the [elementwise](@ref glossary_elementwise) the lower and higher parts of
//!        the input values, as a pair of unsigned integers
//!
//!      * The call lohi(x) is_semantically equivalent to [eve::lo(x), eve::hi(x)]
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/lo.cpp}
//! @}
//================================================================================================
inline constexpr auto lohi = functor<lohi_t>;

namespace detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto
  lohi_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr( sizeof(elt_t) == 1 ) // nibbles extraction
    {
      using ui_t = as_integer_t<T, unsigned>;
      auto uia0  = bit_cast(a0, as<ui_t>());
      return zip(ui_t(uia0 & ui_t(0xF)), ui_t((uia0 & ui_t(0xF0)) >> 4));
    }
    else
    {
      using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;

      constexpr auto is_le  = (std::endian::native == std::endian::little);
      constexpr auto lo_idx = is_le ? 0 : 1;
      constexpr auto hi_idx = is_le ? 1 : 0;

      if constexpr( simd_value<T> )
      {
        using ui_t = wide<si_t, typename cardinal_t<T>::combined_type>;
        using vi_t = wide<si_t, cardinal_t<T>>;
        auto constexpr p = as_pattern([](auto i, auto c) { return (i < c/2) ? 2*i : 2*(i - c/2) + 1; });

        auto uia0 = bit_cast(a0, as<ui_t>());
        auto z    = eve::shuffle(uia0, p).slice();
        return zip(bit_cast(z[lo_idx], as<vi_t>()), bit_cast(z[hi_idx], as<vi_t>()));
      }
      else
      {
        using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;
        using r_t  = std::array<si_t, 2>;
        auto z     = bit_cast(a0, as<r_t>());
        return zip(z[lo_idx], z[hi_idx]);
      }
    }
  }
}

}
