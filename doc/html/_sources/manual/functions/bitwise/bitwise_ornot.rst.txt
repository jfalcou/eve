.. _function-bitwise_ornot:

bitwise_ornot
===========

**Required header** ``#include <eve/function/bitwise_ornot.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value0 bitwise_ornot( Value0 lhs, Value1 rhs ) noexcept
   }

Function object for performing bitwise ornot over two :ref:`Values <concept-value>` of possibly different types
but of same bit size, (``lhs | ~rhs``).

The result type is the one of the first operator.


Parameters
----------

  - ``lhs``, ``rhs`` : input values

Return value
------------

The bitwise ornot of  ``lhs`` and``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_ornot.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_ornot.txt
  :literal:

