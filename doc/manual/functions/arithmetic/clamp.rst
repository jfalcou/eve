.. _function-clamp:

#####
clamp
#####

**Required header:** ``#include <eve/function/clamp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ clamp = {};
   }

Function object clamping a :ref:`Values <concept-value>` btween two other


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w , wide<T,N> const& x ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v U s, U t ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w , U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s , wide<T,N> const& w)
   template<typename U>                       constexpr T operator()( U r, U s, U t ) noexcept;

* [1] performs element-wise clamp of the firdt parameter between the two other ones
* [2:4] convert the scalar type U to the wide type and perform element-wise element-wise clamp of the firdt parameter between the two other ones
* [5]  performs  clamp of the firdt parameter between the two other ones

.. rubric:: Parameters

* **v**, **w**, **x**: Instances of **wide<T,N>**
* **r**, **s**, **t**: Scalar value  of type **U**


.. rubric:: Return value

* [1:4] A value of the type **wide<T,N>**
* [5]     A value of type **U**


*****
Notes
*****

  - the second and third parameters (respectively x and y) must satisfy x<y or the result has undefined behaviour 

*******
Example
*******

.. include:: ../../../../test/doc/core/clamp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/clamp.txt
  :literal:
