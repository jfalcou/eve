.. _function-bitwise_ornot:

##############
bitwise_ornot
##############

**Required header:** ``#include <eve/function/bitwise_ornot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitwise_ornot = {};
   }

Function object performing a bitwise OR between a :ref:`Value <concept-value>` and the COMPLEMENT of
another :ref:`Value <concept-value>` of the same bit size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U>             wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename U> constexpr               T         operator()( T s, U t ) noexcept;

* [1] Performs a bitwise OR between **v** and the COMPLEMENT of **w**.
* [2] Performs a bitwise OR between each elements of **v** and the COMPLEMENT of **s**.
* [3] Performs a bitwise OR between **s** and the COMPLEMENT of **t**.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``.
* **s**, **t**: Scalar values of type **U** satisfying ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.

.. rubric:: Notes

* There is no type restriction between operands of :ref:`function-bitwise_ornot` as long as the number
  of bits between them are equals. This implies that calls to :ref:`function-bitwise_ornot` on
  :ref:`concept-ieeevalue` are possible as long as they are performed with a
  second parameters of proper size.

* There is no cardinal restriction on the :ref:`concept-vectorized` operands of :ref:`function-bitwise_ornot`
  as long as the number of bits between them are equals.  This implies that calls to :ref:`function-bitwise_ornot`
  on :ref:`concept-vectorized` values of different cardinals are allowed as long at their total size
  in bits are equal.


*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/bitwise_ornot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_ornot.txt
  :literal:
