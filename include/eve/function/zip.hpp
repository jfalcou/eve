//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //! @var zip
  //!
  //! @brief Callable object constructing a SoA value
  //!
  //! **Required header:** `#include <eve/function/zip.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                          |
  //! |:-------------|:----------------------------------------------------------------|
  //! | `operator()` | Construct a eve::wide of a given eve::product_type from values  |
  //!                  For scalar types returns a kumi::tuple or a product type
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<simd_value... Ws>
  //!  auto operator()(Ws... ws) const noexcept;
  //!
  //!  template<product_type Target, simd_value... Ws>
  //!  auto operator()(as<Target> t, Ws... ws) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! @param
  //! t: Type to construct. By default, it's equal to `kumi::tuple<``eve::element_type`<Ws>::type>`
  //! ws: Varidiac list of eve::simd_value to zip.
  //!
  //! **Return value**
  //!
  //! Construct an instance of `eve::wide``<Target>` by aggregating each element of each values `ws`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/zip.cpp}
  //!
  //!  @}
  //================================================================================================z
  EVE_MAKE_CALLABLE(zip_, zip);
}

namespace eve::detail
{
  template<kumi::product_type Target, scalar_value... Vs>
  EVE_FORCEINLINE auto zip_(EVE_SUPPORTS(cpu_), as<Target> const&, Vs... vs)
  {
    kumi::tuple ins{vs...};
    Target res;

    // These should inline.
    auto ptrs = kumi::map([](auto& m) { return &m; }, res);
    kumi::for_each( [](auto in, auto* ptr) { *ptr = in; }, ins, ptrs );

    return res;
  }

  template<scalar_value... Vs>
  EVE_FORCEINLINE auto zip_(EVE_SUPPORTS(cpu_), Vs... vs)
  {
    return kumi::tuple{vs...};
  }

  template<kumi::product_type Target, simd_value W0, simd_value... Ws>
  EVE_FORCEINLINE auto zip_(EVE_SUPPORTS(cpu_), as<Target> const&, W0 w0, Ws... ws) noexcept
  requires  (   (sizeof...(Ws) + 1 == std::tuple_size<Target>::value)
            &&  (std::same_as<cardinal_t<W0>,cardinal_t<Ws>> &&  ... )
            )
  {
    return wide<Target,cardinal_t<W0>>{w0,ws...};
  }

  template<simd_value W0, simd_value... Ws>
  EVE_FORCEINLINE auto zip_(EVE_SUPPORTS(cpu_),  W0 w0, Ws... ws) noexcept
    requires( (std::same_as<cardinal_t<W0>,cardinal_t<Ws>> &&  ... ) )
  {
    return wide<kumi::tuple<eve::element_type_t<W0>,eve::element_type_t<Ws>...>, cardinal_t<W0>>{w0, ws...};
  }
}
