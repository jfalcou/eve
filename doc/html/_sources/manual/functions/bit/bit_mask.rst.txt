.. _function-bit_mask:

##############
bit_mask
##############

**Required header:** ``#include <eve/function/bit_mask.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_mask = {};
   }

Function object computing a mask of bits for each input element. This mask has all its bit set if the input element
is not equal to zero and all its bits unset otherwise.

Synopsis
********

.. code-block:: c++

   template<typename T> auto operator()( T const& x ) noexcept;

* Computes a mask of bits for each element of ``x``. This mask has all its bit set if the input element
  is not equal to zero and all its bits unset otherwise. 
  The computation is equivalent to ``if_else(is_nez(v),Allbits(as(v)),Zero(as(v))``,but optimized.


Parameter
*********

 Instance of a :ref:`Value <concept-value>`.

Return value
************

* ``x``: A value with the same type as the parameter.

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_mask.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_mask.txt
  :literal:
