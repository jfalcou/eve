//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/memory.hpp>
#include <eve/traits/overload.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct scatter_t : callable<scatter_t, Options, relative_conditional_no_alternative_option>
{
  template<simd_value T, integral_simd_value Idx, simd_compatible_ptr<T> Ptr>
  requires(T::size() == Idx::size())
  EVE_FORCEINLINE void operator()(T const& v, Ptr ptr, Idx const& idx) const noexcept { EVE_DISPATCH_CALL(v,ptr,idx); }

  EVE_CALLABLE_OBJECT(scatter_t, scatter_);
};

//TODO complete DOC
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var scatter
//!   @brief Store a SIMD register to memory using scattered indexes
//!
//!   Store each element of a given [SIMD value](@ref eve::simd_value) `v`in different memory address computed form a base
//!   SIMD compatible iterator `ptr` and a [SIMD integral value](@ref eve::integral_simd_value) `idx` used as indexes.
//!
//!   A call to `eve::scatter(v,ptr,idx)` is semantically equivalent to:
//!
//!   ```
//!   for(std::size_t i=0;i<v.size();++i)
//!     ptr[idx.get(i)] = v.get(i);
//!   ```
//!
//!   @groupheader{Header file}
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
//!     template<simd_value T, integral_simd_value Idx, simd_compatible_ptr<T> Ptr>
//!     requires(T::size() == Idx::size())
//!     void scatter(T const& v, Ptr ptr, Idx const& idx) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `v`:  [simd value](@ref eve::simd_value) to scatter
//!     * `ptr`: Base pointer to scatter to.
//!     * `idx`:  [Integral simd value](@ref eve::integral_simd_value) containing the index to scatter to.
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!   eve::scatter can be masked using [Relative conditionals](@ref eve::relative_conditional_expr) to skip scattering
//!   of certain elements.
//!
//!   The call `eve::scatter[cond](v,p,i)` is semantically equivalent to:
//!
//!   @code
//!   auto m = cond.mask( as<as_logical_t<T>>{} );
//!   for(std::size_t n=0;n<v.size();++n)
//!   {
//!     if(m.get(n)) write(v.get(n),p+idx.get(n));
//!   }
//!   @endcode
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/scatter.cpp}
//!
//================================================================================================
  inline constexpr auto scatter = functor<scatter_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/scatter.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/scatter.hpp>
#endif
