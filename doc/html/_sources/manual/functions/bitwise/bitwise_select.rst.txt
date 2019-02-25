.. _function-bitwise_select:

##############
bitwise_select
##############

**Required header:** ``#include <eve/function/bitwise_select.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitwise_select = {};
   }

Function object performing a bit selection between two :ref:`Values <concept-value>` of same bit size according to a
mask.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w , wide<U,M> const& x ) noexcept;
   template<typename T, typename N, typename U>             wide<T,N> operator()( wide<T,N> const& v, U s, U t ) noexcept;
   template<typename T, typename U> constexpr               T         operator()( T r, U s, U t ) noexcept;

* [1] Performs a bit selection between *w* and *x* equivalent to  ``bitwise_or(bitwise_and(w, v), eve::bitwise_andnot(x, v))``.
* [2] Performs a bit selection between *s* and *t* equivalent to  ``bitwise_select(v, wide<T,N>(s), wide<T,N>(t))``.
* [3] Performs a bit selection between *s* and *t* equivalent to  ``bitwise_or(bitwise_and(s, r), eve::bitwise_andnot(t, r))``.

.. rubric:: Parameters

* **v**, **w**, **x**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``, *w* and *x* sharing the same type.
* **r**: Scalar value  of type **T**
* **s**, **t**: Scalar values of type **U**. **U** must satisfy ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1-3] A value of the type shared by the second and third parameter.


*******
Options
*******

*******
Example
******* 

.. include:: ../../../../test/doc/bitwise_select.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_select.txt
  :literal:
