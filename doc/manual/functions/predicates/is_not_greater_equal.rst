.. _function-is_not_greater_equal:

is_not_greater_equal
====================

**Required header** ``#include <eve/function/is_not_greater_equal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_greater_equal( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is not greater or equal to the second.


.. seealso::  :ref:`is_not_greater <function-is_not_greater>`,  :ref:`is_less <function-is_less>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` greater_equal than ``rhs`` for every elements of each parameter. 
The return value can differ from those of :ref:`is_less <function-is_less>` only in case of  :ref:`Nans <constant-nan>` 
in floating point parameters.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_greater_equal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_greater_equal.txt
  :literal:

