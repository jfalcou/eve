.. _function-bitwise_mask:

##############
bitwise_mask
##############

**Required header:** ``#include <eve/function/bitwise_mask.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitwise_mask = {};
   }

Function object computing a mask of bits for each input element. This mask has all its bit set if the input element
is not equal to zero and all its bits unset otherwise.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename N> wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s ) noexcept;

* [1] Computes a mask of bits for each element of **v**. This mask has all its bit set if the input element
  is not equal to zero and all its bits unset otherwise. The computation is equivalent to ``if_else(is_nez(v),Allbits(as(v)),Zero(as(v))``.

* [2] Computes a mask of bits for **s**. TThis mask has all its bit set if **s** is not equal to zero
  and all its bits unset otherwise. The computation is equivalent to ``s ? Allbits(as(s)) : Zero(as(s))``.


.. rubric:: Parameters

* **v**, **w**: Instance of :ref:`type-wide` .
* **s**, **t**: Scalar value.

.. rubric:: Return value

* [1,2,3] A value with the same type as the parameter.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/bitwise_mask.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_mask.txt
  :literal:
