//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/overload.hpp>

#include <functional>

namespace eve
{

//================================================================================================
//! @addtogroup core_conversions
//! @{
//!   @var simd_cast
//!   @brief casting bits between simd values.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   This cast reinterprets one `eve::simd_value` as the other, if such reinterpretation is
//!   available. If the output is smaller in size, the extra bits are dropped. If the output is
//!   bigger, the value of extra bits is unspecified.
//!
//!   What can be simd_cast?
//!    * any eve::plain_simd_value to any other eve::plain_simd_value
//!    * product_simd_value to a product_simd_value iff each fields can be simd_cast to the corresponding
//!      field.
//!    * if is_wide_logical: logical_simd_value behaves same as plain_simd_value
//!    * if !is_wide_logical: any logical_simd_value can cast to any other logical_simd_value,
//!      but semantics changes, based on the representation of the logical.
//!    * on rvv platform allows for an efficient cast between logical and plain_simd_value.
//!
//!   @groupheader{Callable Signatures}
//!   @code
//!   namespace eve
//!   {
//!      template <eve::simd_value T, eve::simd_value Target>
//!        requires /* see documentation*/
//!      Target simd_cast(T x, eve::as<Target> tgt);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [simd_value] to cast
//!    * `tgt`: [Type wrapper](@ref eve::as) instance embedding the type to cast `x` to.
//!
//!    **Return value**
//!
//!    bits from `x` reinterpreted as a new type, accoridng to the rules described earlier.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/simd_cast.cpp}
//! @}
//================================================================================================
template<typename Options> struct simd_cast_t : callable<simd_cast_t, Options>
{
  template<typename T, typename U> static constexpr bool enabled_for(as<T>, as<U>)
  {
    using abi_t = typename T::abi_type;
    if constexpr( plain_simd_value<T> && plain_simd_value<U> ) return true;
    // This just happens to be true now, might not be the case on some future platform.
    else if constexpr( logical_simd_value<T> && logical_simd_value<U> ) return true;
    else if constexpr( abi_t::is_wide_logical && logical_simd_value<T> )
    {
      return enabled_for(as<typename T::mask_type> {}, as<U> {});
    }
    else if constexpr( abi_t::is_wide_logical && logical_simd_value<U> )
    {
      return enabled_for(as<T> {}, as<typename U::mask_type> {});
    }
    else if constexpr( product_simd_value<T> && product_simd_value<U> )
    {
      if constexpr( std::tuple_size_v<T> != std::tuple_size_v<U> ) return false;
      else
      {
        auto make_as = []<typename M>(M) { return as<M> {}; };

        using t_types = kumi::result::map_t<decltype(make_as), T>;
        using u_types = kumi::result::map_t<decltype(make_as), U>;

        return kumi::inner_product(t_types {},
                                   u_types {},
                                   true,
                                   std::logical_and<> {},
                                   [](auto a, auto b) { return enabled_for(a, b); });
      }
    }
    else return false;
  }

  template<simd_value T, simd_value Target>
  EVE_FORCEINLINE constexpr Target operator()(T x, as<Target> tgt) const noexcept
    requires (enabled_for(as<T>{}, as<Target>{}))
  {
    return EVE_DISPATCH_CALL_PT(Target, x, tgt);
  }

  EVE_CALLABLE_OBJECT(simd_cast_t, simd_cast_);
};

inline constexpr auto simd_cast = functor<simd_cast_t>;

namespace detail
{
  // This function is forward declared wrapper around simd_cast,
  // so that internally we can call it anywhere.
  template<typename T, typename Target> EVE_FORCEINLINE Target call_simd_cast(T x, as<Target> tgt)
  {
    return eve::simd_cast(x, tgt);
  }

} // namespace detail

} // namespace eve

#include <eve/module/core/regular/impl/simd_cast.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/simd_cast.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/simd_cast.hpp>
#endif
