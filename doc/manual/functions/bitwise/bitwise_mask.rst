.. _function-bitwise_mask:

bitwise_mask
============

**Required header** ``#include <eve/function/bitwise_mask.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value bitwise_mask( Value lhs ) noexcept
   }

This function object returns a mask of bits. This mask is full of ones if the
input element is not equal to zero else full of zeros.


The result type is the one of the parameter.


Parameters
----------

  - ``lhs`` : input value

Return value
------------

Semantically equivalent to ``if_else(is_nez(a0),Allbits(as(a0)),Zero(as(a0))``.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_mask.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_mask.txt
  :literal:

