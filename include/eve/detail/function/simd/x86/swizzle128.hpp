//   //------------------------------------------------------------------------------------------------
//   // Unary swizzle for (u)int16
//   template<typename T, typename N, typename P, int S, typename Escape>
//   EVE_FORCEINLINE auto swizzle_i16( wide<T,N,sse_> const& v,
//                                     swizzler_t<P,S> p,
//                                     Escape ef
//                                   ) noexcept
//   {

//     else if constexpr( match_pattern<sz>(p, merger<1,1,0>) )
//     {
//       return that_t(_mm_unpacklo_epi16(v,v));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,0,0>) )
//     {
//       return that_t(_mm_unpacklo_epi16(v,that_t{0}));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<0,1,0>) )
//     {
//       return that_t(_mm_unpacklo_epi16(that_t{0},v));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,1,sz/2>) )
//     {
//       if constexpr( sz == 8)
//       {
//         return that_t(_mm_unpackhi_epi16(v,v));
//       }
//       else
//       {
//         auto const w = _mm_bsrli_si128(v,sz);
//         return that_t(_mm_unpacklo_epi16(w,w));
//       }
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,0,sz/2>) )
//     {
//       if constexpr( sz == 8)
//       {
//         return that_t(_mm_unpackhi_epi16(v,that_t{0}));
//       }
//       else
//       {
//         return that_t(_mm_unpacklo_epi16(_mm_bsrli_si128(v,sz),that_t{0}));
//       }
//     }
//     else if constexpr( match_pattern<sz>(p, merger<0,1,sz/2>) )
//     {
//       if constexpr( sz == 8)
//       {
//         return that_t(_mm_unpackhi_epi16(that_t{0},v));
//       }
//       else
//       {
//         return that_t(_mm_unpacklo_epi16(that_t{0},_mm_bsrli_si128(v,sz)));
//       }
//     }
//   }

//   //------------------------------------------------------------------------------------------------
//   // Unary swizzle for (u)int8
//   template<typename T, typename N, typename P, int S, typename Escape>
//   EVE_FORCEINLINE auto swizzle_i8( wide<T,N,sse_> const& v,
//                                     swizzler_t<P,S> p,
//                                     Escape ef
//                                   ) noexcept
//   {
//     constexpr auto sz = swizzler_t<P,S>::size(N::value);
//     using that_t      = wide<T,fixed<sz>>;

//     if constexpr( match_pattern<sz>(p, merger<1,1,0>) )
//     {
//       return that_t(_mm_unpacklo_epi8(v,v));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,0,0>) )
//     {
//       return that_t(_mm_unpacklo_epi8(v,that_t{0}));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<0,1,0>) )
//     {
//       return that_t(_mm_unpacklo_epi8(that_t{0},v));
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,1,sz/2>) )
//     {
//       if constexpr( sz == 16)
//       {
//         return that_t(_mm_unpackhi_epi8(v,v));
//       }
//       else
//       {
//         constexpr auto shift = sz/2;
//         auto const w = _mm_bsrli_si128(v,shift);
//         return that_t(_mm_unpacklo_epi8(w,w));
//       }
//     }
//     else if constexpr( match_pattern<sz>(p, merger<1,0,sz/2>) )
//     {
//       if constexpr( sz == 16)
//       {
//         return that_t(_mm_unpackhi_epi8(v,that_t{0}));
//       }
//       else
//       {
//         constexpr auto shift = sz/2;
//         return that_t(_mm_unpacklo_epi8(_mm_bsrli_si128(v,shift),that_t{0}));
//       }
//     }
//     else if constexpr( match_pattern<sz>(p, merger<0,1,sz/2>) )
//     {
//       if constexpr( sz == 16)
//       {
//         return that_t(_mm_unpackhi_epi8(that_t{0},v));
//       }
//       else
//       {
//         constexpr auto shift = sz/2;
//         return that_t(_mm_unpacklo_epi8(that_t{0},_mm_bsrli_si128(v,shift)));
//       }
//     }
//   }
