#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>

namespace eve::detail
{

  inline void ht_shft_simd_orig(auto ff, auto n)
  // Optimized version,  n must be a power of 2.
  {
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(ff[0])>;
    constexpr i_t cardinal = eve::expected_cardinal_v<e_t>;
    auto phi0 = rec(e_t(n));
    auto phi = zero(as(phi0));
    const i_t nh = n/2;
    if ( n>=4 )
    {
      {
        i_t im=nh/2, jm=3*im;
//                  std::cout << "prolog im " << im << " jm " << jm << std::endl;
        auto fi = ff[im],  fj = ff[jm];
        std::cout << "in prolog fi " << fi << " fj " << fj << std::endl;
        auto cs = invsqrt_2(as(fi));
        std::cout << " cs " << cs << std::endl;
//         ff[im] = (fi + fj) * cs;
//         ff[jm] = (fi - fj) * cs;
      }
      if ( n>=8 )
      {
        using we_t = eve::wide<e_t, eve::fixed<cardinal>>;
        we_t i0([](auto i,  auto ){ return e_t(i); });
        auto wcs = exp_ipi(i0*phi0);
        auto nfp = min(cardinal, n);
        for (i_t i=1, j=n-1, k=nh-1, l=nh+1;  (i < nfp)&&(i<k);  ++i, --j, --k, ++l)
        {
//                  std::cout << "in scal i " << i << " j " << j << " k " << k << " l " << l << std::endl;
          phi += phi0;
          auto [c, s] = exp_ipi(phi);
          auto fi = ff[i];
          auto fj = ff[j];
          auto fk = ff[k];
          auto fl = ff[l];
          std::cout << "in scal fi " << fi << " fj " << fj << " fk " << fk << " fl " << fl << std::endl;
          std::cout << "c " << c <<  " s " <<  s << std::endl;
//           ff[i] = fi * c + fj * s;
//           ff[j] = fi * s - fj * c;
//           ff[k] = fk * s + fl * c;
//           ff[l] = fk * c - fl * s;
        }
        if (n > 4*cardinal)
        {
          auto cs4 = wcs.get(cardinal-1)*wcs.get(1);
          auto siz = n/4-cardinal;
          using idx_t = as_integer_t<e_t>;
          auto is = eve::views::iota(idx_t(nfp), siz);
          auto phis = eve::views::iota_with_step(phi+phi0, phi0, siz);
          auto view = eve::views::zip(is, phis);
          auto doit = [cardinal, ff, n, nh, &wcs, cs4](auto zz, auto ignore){
            auto [ii, phi]= eve::load[ignore](zz);
            auto j = n-ii.get(cardinal-1) ;
            auto i = ii.get(0);
//             auto l = i+nh;
//             auto k = j-nh;
//                  std::cout << "in simd i " << i << " j " << j << " k " << k << " l " << l << std::endl;
            auto fi = load[ignore](ff+i);
            auto fl = load[ignore](ff+i+nh);
            auto fk = reverse(load[ignore](ff+j-nh));
            auto fj = reverse(load[ignore](ff+j));
             std::cout << "in simd" << std::endl
            << " fi " << fi << std::endl
            << " fj " << fj << std::endl
            << " fk " << fk << std::endl
            << " fl " << fl << std::endl;
            wcs*= cs4;
            auto [c, s] = wcs;
            std::cout << "c " << c <<  " s " <<  s << std::endl;
//             auto aa = fi * c + fj * s;
//             auto bb = fi * s - fj * c;
//             auto cc = fk * s + fl * c;
//             auto dd = fk * c - fl * s;
//             eve::store[ignore](aa, ff+i);
//             eve::store[ignore](reverse(bb), ff+j);
//             eve::store[ignore](dd, ff+l);
//             eve::store[ignore](reverse(cc), ff+k);
          };
          eve::algo::for_each[eve::algo::unroll<2>](view, doit);
        }
      }
    }
  }


  inline void ht_shft_simd_new(auto ff, auto n)
  // Optimized version,  n must be a power of 2.
  {
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(ff[0])>;
    constexpr i_t cardinal = eve::expected_cardinal_v<e_t>;
    auto phi0 = rec(e_t(n));
    auto phi = zero(as(phi0));
    const i_t nh = n/2;
    if ( n>=4 )
    {
      {
        i_t im=nh/2, jm=3*im;
//                  std::cout << "prolog im " << im << " jm " << jm << std::endl;
        auto fi = ff[im],  fj = ff[jm];
        std::cout << "in prolog fi " << fi << " fj " << fj << std::endl;
        auto cs = invsqrt_2(as(fi));
        std::cout << " cs " << cs << std::endl;
//         ff[im] = (fi + fj) * cs;
//         ff[jm] = (fi - fj) * cs;
      }
      if ( n>=8 )
      {
        using we_t = eve::wide<e_t, eve::fixed<cardinal>>;
        we_t i0([](auto i,  auto ){ return e_t(i); });
        auto wcs = exp_ipi(i0*phi0);
        auto nfp = min(cardinal, n);
        for (i_t i=1, j=n-1, k=nh-1, l=nh+1;  (i < nfp)&&(i<k);  ++i, --j, --k, ++l)
        {
//                  std::cout << "in scal i " << i << " j " << j << " k " << k << " l " << l << std::endl;
          phi += phi0;
          auto [c, s] = exp_ipi(phi);
          auto fi = ff[i];
          auto fj = ff[j];
          auto fk = ff[k];
          auto fl = ff[l];
          std::cout << "in scal fi " << fi << " fj " << fj << " fk " << fk << " fl " << fl << std::endl;
          std::cout << "c " << c <<  " s " <<  s << std::endl;
//           ff[i] = fi * c + fj * s;
//           ff[j] = fi * s - fj * c;
//           ff[k] = fk * s + fl * c;
//           ff[l] = fk * c - fl * s;
        }
        if (n > 4*cardinal)
        {
          std::cout << "cardinal " << cardinal << std::endl;
//          auto nh  = n/2-cardinal;
//          auto nh2 = n/4-cardinal;
          auto cs4 = wcs.get(cardinal-1)*wcs.get(1);
          auto fi = eve::algo::as_range(ff+cardinal,ff+n/4);
          auto fj = eve::views::reverse(eve::algo::as_range(ff+3*n/4+1, ff+n-cardinal+1));
          auto fk = eve::views::reverse(eve::algo::as_range(ff+n/4+1,ff+n/2-cardinal+1));
          auto fl = eve::algo::as_range(ff+n/2+cardinal, ff+3*n/4l);
//           auto is = eve::algo::views::iota(e_t(phi0), phi0, std::size(fi));
//           auto ex = [](auto i){ return exp_ipi(i); };
// //          eve::soa_vector<c_t> v(std::size(fi));
//          eve::algo::transform_to(is, phs, ex);
//           std::cout << "incise " << std::endl;
//           std::cout << "fi " ;
//           for(int i=0; i < std::ssize(fi) ; ++i){
//             std::cout << read(fi.data()+i) << " ";
//           }
//           std::cout << std::endl;
//           std::cout << "fj " ;
//           for(int i=0; i < std::ssize(fj); i++){
//             std::cout << read(fj.data()+i) << " ";
//           }
//           std::cout << std::endl;
//            std::cout << "fk " ;
//           for(int i=std::ssize(fk)-1; i >= 0; --i){
//             std::cout << read(fk.data()+i) << " ";
//           }
//           std::cout << std::endl;
//            std::cout << "fl " ;
//           for(int i=0; i < std::ssize(fl) ; ++i){
//             std::cout << read(fl.data()+i) << " ";
//           }
//           std::cout << std::endl;
//           std::cout << std::endl;



          auto view = eve::views::zip(fi, fj, fk, fl);
          auto doit = [cs4, &wcs](auto zz, auto ignore){
            auto [fi, fj, fk, fl]= eve::load[ignore](zz);
            wcs *= cs4;
            std::cout << "in simd " << std::endl
            << " fi " << fi  << std::endl
            << " fj " << fj  << std::endl
            << " fk " << fk  << std::endl
            << " fl " << fl << std::endl
            << " wcs " << wcs << std::endl;
          };
          eve::algo::for_each[eve::algo::no_aligning][eve::algo::unroll<2>](view, doit);
        }
      }
    }
  }



}

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  size_t n =  64;
  alignas(64) std::vector < double >  f(n);
  for(size_t i = 0; i < n; ++i) f[i] = i;
  auto ff =  f.data();
  eve::detail::ht_shft_simd_orig(ff, n);
  std::cout << " ================ " << std::endl;
  eve::detail::ht_shft_simd_new(ff, n);
  return 0;
}
