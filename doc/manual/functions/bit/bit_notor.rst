.. _function-bit_notor:

##############
bit_notor
##############

**Required header:** ``#include <eve/function/bit_notor.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_notor = {};
   }

Function object performing a bit OR between the COMPLEMENT of a :ref:`Value <concept-value>` and
another :ref:`Value <concept-value>` of the same bit size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U>             wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename U> constexpr               T         operator()( T s, U t ) noexcept;

* [1] Performs a bit OR between the COMPLEMENT of **v** and **w**.
* [2] Performs a bit OR between each elements of the COMPLEMENT of **v** and **s**.
* [3] Performs a bit OR between the COMPLEMENT of **s** and **t**.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``.
* **s**, **t**: Scalar values of type **U** satisfying ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.

.. rubric:: Notes

* There is no type restriction between operands of :ref:`function-bit_notor` as long as the number
  of bits between them are equals. This implies that calls to :ref:`function-bit_notor` on
  :ref:`concept-ieeevalue` are possible as long as they are performed with a
  second parameters of proper size.

* There is no cardinal restriction on the :ref:`concept-vectorized` operands of :ref:`function-bit_notor`
  as long as the number of bits between them are equals.  This implies that calls to :ref:`function-bit_notor`
  on :ref:`concept-vectorized` values of different cardinals are allowed as long as their total size
  in bits are equal.


*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_notor.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_notor.txt
  :literal:
