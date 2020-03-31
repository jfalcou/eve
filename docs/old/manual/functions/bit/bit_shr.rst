.. _function-bit_shr:

##############
bit_shr
##############

**Required header:** ``#include <eve/function/bit_shr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_shr = {};
   }

Function object performing a bit shift  to the right of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>` with the same number of elements and same element size.

Synopsis
********

  template<typename I, typename J> auto operator()( I const& x, J const& y ) noexcept;

* Computes an element-wise arithmetic left shift of each element of ``x`` by each element of ``y``.


Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of :ref:`Value <concept-integralvalue>`.
* All  :ref:`concept-vectorized` parameters must share the same cardinal
* If the first parameter is  :ref:`concept-vectorizable`, so must be the second

Return value
**************

* a value of the type of the first parameter.

Notes
*****

* ``bit_shr`` is a 'logical' shift that does not preserve the sign of the input : zeros are pushed at 
  the left as the shift process to the right.
* All shift are to be greater or equal to zero and not greater or equal to the size in bit of the element shifted 
  or an assert is issued.

*******
Options
*******

.. seealso::  :ref:`shr <function-shr>`

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_shr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_shr.txt
  :literal:
