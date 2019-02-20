.. _function-is_negative:

is_negative
============

**Required header** ``#include <eve/function/is_negative.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_negative( Value lhs ) noexcept
   }

For  :ref:`Integral Values <concept-integervalue>` this function is strictly equivalent
to :ref:`is_equal <function-is_ltz>`, but for floating point inputs it only tests the bit of sign.
In particular iput of :ref:`Mzero <constant-mzero>` returns :ref:`True <constant-true_>`
and of  :ref:`Zero <constant-zero>` returns :ref:`False <constant-true_>`.


.. seealso::  :ref:`is_ltz <function-is_ltz>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

 - for  :ref:`Integral Values <concept-integervalue>` as  :ref:`is_ltz <function-is_ltz>`
 - for floating point inputs : is the bit of sign set ?

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_negative.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_negative.txt
  :literal:

