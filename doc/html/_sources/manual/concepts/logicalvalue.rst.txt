.. _concept-logicalvalue:

LogicalValue
============

A :ref:`concept-logicalvalue` type is a type which refines :ref:`concept-vectorizable` or
:ref:`concept-vectorized` while providing a boolean-like semantic.

Requirements
------------

A type ``T`` satisfies :ref:`concept-logicalvalue` if it refines :ref:`concept-vectorizable`
or :ref:`concept-vectorized` and if :

  - ``eve::scalar_of_t<T>`` satisfies :ref:`concept-logical`

Example
-------

  - ``eve::logical<double>``
  - ``eve::wide<eve::logical<std::uint8_t>>``
