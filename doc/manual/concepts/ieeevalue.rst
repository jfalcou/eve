.. _concept-ieeevalue:

IEEEValue
=========

An :ref:`concept-ieeevalue` type is a type which satisfies either :ref:`concept-vectorizable` or
``Vectorized`` and which underlying scalar type behaves like a IEEE754 floating point value.

Requirements
------------

A type ``T`` satisfies :ref:`concept-ieeevalue` if:

  - ``T``  satisfies :ref:`concept-vectorizable` or  ``Vectorized``
  - ``std::is_floating_point_v<eve::scalar_of_t<T>>`` evaluates to ``true``

Example
-------

  - ``float``
  - ``double``
  - ``eve::wide<double>``
