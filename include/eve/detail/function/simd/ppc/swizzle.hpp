// //==================================================================================================
// /**
//   EVE - Expressive Vector Engine
//   Copyright 2020 Joel FALCOU
//   Copyright 2020 Jean-Thierry LAPRESTE
//
//   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//   SPDX-License-Identifier: MIT
// **/
// //==================================================================================================
// #pragma once

// #include <eve/detail/abi.hpp>
// #include <eve/detail/swizzle.hpp>
// #include <eve/traits/as_wide.hpp>
// #include <eve/forward.hpp>

// namespace eve::detail
// {
//   //------------------------------------------------------------------------------------------------
//   // Unary swizzle - logical
//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( ppc_ const&
//                               , logical<wide<T,N,ppc_>> const& v, swizzler_t<P,Size> p
//                               ) noexcept
//   {
//     return bit_cast( v.mask()[p], as(v) );
//   }

//   //------------------------------------------------------------------------------------------------
//   // Unary swizzle - arithmetic
//   template<typename T, typename N, typename P, int Size>
//   EVE_FORCEINLINE auto swizzle( ppc_ const&
//                               , wide<T,N,ppc_> const& v, swizzler_t<P,Size> p
//                               ) noexcept
//   {
//     constexpr auto sz = swizzler_t<P,Size>::size(N::value);
//     using that_t      = wide<T,fixed<sz>>;

//     static_assert ( is_valid_pattern<N::value>(p)
//                   , "[eve::swizzle ppc] - Out of range pattern index"
//                   );

//     //----------------------------------------------------------------------------------------------
//     // Handle common basic cases
//     if constexpr( !std::is_void_v<decltype(basic_swizzle(v,p))> )
//     {
//       return basic_swizzle(v,p);
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for broadcast swizzle
//     else if constexpr( constexpr auto s = match_broadcast<sz>(p); s != -1 )
//     {
//       return that_t( vec_splat(v.storage(),s) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for slide right swizzle
//     else if constexpr( constexpr auto s = match_slide_right<sz>(p); s != -1 )
//     {
//       constexpr auto offset = (s * sizeof(T)) << 3;
//       __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
//       return that_t( vec_sro(v.storage(), shift) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for slide left swizzle
//     else if constexpr( constexpr auto s = match_slide_left<sz>(p); s != -1 )
//     {
//       constexpr auto offset = (s * sizeof(T)) << 3;
//       __vector unsigned char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
//       return that_t( vec_slo(v.storage(), shift) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for self-merge-high swizzle
//     else if constexpr( match_pattern<sz>(p, merger<1,1,0>) )
//     {
//       return that_t( vec_mergeh(v.storage(), v.storage()) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Check for self-merge-low swizzle
//     else if constexpr( match_pattern<sz>(p, merger<1,1,sz/2>) )
//     {
//       return that_t( vec_mergel(v.storage(), v.storage()) );
//     }
//     //----------------------------------------------------------------------------------------------
//     // Other cases
//     else
//     {
//       using bytes_t = typename wide<T,N,ppc_>::template rebind<std::uint8_t>;
//       return that_t ( vec_perm(v.storage(),v.storage(),
//                       as_bytes<wide<T,N,ppc_>>(p,as_<bytes_t>()).storage())
//                     );
//     }
//   }
// }
