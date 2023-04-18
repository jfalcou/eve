#include <eve/module/fft.hpp>
#include <iostream>
#include <vector>

using e_t =  double;
using c_t =  eve::complex<e_t>;
using aos_vc_t =  std::vector<c_t>;
using ve_t=  std::vector<e_t>;
using soa_vc_t =  eve::algo::soa_vector<c_t>;

constexpr size_t N = 1 << 3;

auto pr = [](auto title, auto v){
  std::cout << title << " = (";
  for(size_t i=0; i < v.size() ; ++i) std::cout << eve::read(v.data()+i) << " ";
  std::cout << ")\n";
};

int main()
{
  aos_vc_t aosv(N);
  for(size_t i = 0; i < N; ++i) aosv[i] = c_t(i+1, i+2);
  pr("original data                aosv", aosv);
  eve::aos(eve::fft_dit4)(aosv, e_t(1));
  pr("after performing fft         aosv", aosv);
  eve::aos(eve::ifft)(eve::aos(eve::fft_dit4), aosv, e_t(1)/N);
  pr("after performing inverse fft aosv", aosv);
  std::cout << std::endl;
  soa_vc_t soav(N);
  for(size_t i = 0; i < N; ++i) soav.set(i, c_t(i+1, i+2));
  pr("original data                soav", soav);
  eve::soa(eve::fft_dit4)(soav, e_t(1));
  pr("after performing fft         soav", soav);
  eve::soa(eve::ifft)(eve::soa(eve::fft_dit4), soav, e_t(1)/N);
  pr("after performing inverse fft soav", soav);

  return 0;
}
