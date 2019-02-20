.. _function-is_positive:

is_positive
============

**Required header** ``#include <eve/function/is_positive.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_positive( Value lhs ) noexcept
   }

For  :ref:`Integral Values <concept-integralvalue>` this function is strictly equivalent
to :ref:`is_equal <function-is_gtz>`, but for floating point inputs it only tests the bit of sign.
In particular input of :ref:`Mzero <constant-mzero>` returns :ref:`False <constant-true_>`
and of  :ref:`Zero <constant-zero>` returns :ref:`True <constant-true_>`.


.. seealso::  :ref:`is_gtz <function-is_gtz>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

 - for  :ref:`Integral Values <concept-integralvalue>` as  :ref:`is_gtz <function-is_gtz>`
 - for floating point inputs : is the bit of sign not set ?

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_positive.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_positive.txt
  :literal:

