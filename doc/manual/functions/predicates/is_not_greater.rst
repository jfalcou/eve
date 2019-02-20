.. _function-is_not_greater:

is_not_greater
============

**Required header** ``#include <eve/function/is_not_greater.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_greater( Value lhs, Value rhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its first parameter is not greater than the second.


.. seealso::  :ref:`is_not_greater_equal <function-is_not_greater_equal>`,  :ref:`is_less_equal <function-is_less>`

Parameters
----------

  - ``lhs``, ``rhs`` : values to compare of the same type

Return value
------------

The logical values ``lhs`` greater than ``rhs`` for every elements of each parameter. 
The return value can differ from those of :ref:`is_less_equal <function-is_less_equal>` only in case of :ref:`Nans <constant-nan>` 
in floating point parameters.

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_greater.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_greater.txt
  :literal:

