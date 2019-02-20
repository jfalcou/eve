.. _function-is_not_less_equal:

is_not_less_equal
============

**Required header** ``#include <eve/function/is_not_less_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_less_equal( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is not less or equal to the second.


.. seealso::  :ref:`is_not_less <function-is_not_less>`,  :ref:`is_greater <function-is_greater>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` less_equal than ``rhs`` for every elements of each parameter. 
The return value can differ from those of :ref:`is_less <function-is_greater>` only in case of Nans
in floating point parameters.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_less_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_less_equal.txt
  :literal:

