.. _function-is_eqz:

is_eqz
============

**Required header** ``#include <eve/function/is_eqz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_eqz( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is equal to :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_equal <function-is_equal>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Equivalent to `is_equal(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_eqz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_eqz.txt
  :literal:

