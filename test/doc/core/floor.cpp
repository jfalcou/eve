// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> floor(wf)                = " << eve::floor(wf) << "\n";
   std::cout << "-> floor(wi)                = " << eve::floor(wi) << "\n";
   std::cout << "-> floor(wu)                = " << eve::floor(wu) << "\n";
   std::cout << "-> floor[ignore_last(2)](wf)= " << eve::floor[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> floor[ignore_last(2)](wi)= " << eve::floor[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> floor[ignore_last(2)](wu)= " << eve::floor[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> floor[wf != 0](wf)       = " << eve::floor[wf != 0](wf) << "\n";
   std::cout << "-> floor[wi != 0](wi)       = " << eve::floor[wi != 0](wi) << "\n";
   std::cout << "-> floor[wu != 0](wu)       = " << eve::floor[wu != 0](wu) << "\n";
   std::cout << "-> floor[almost](wf)        = " << eve::floor[eve::almost](wf) << "\n";
}
