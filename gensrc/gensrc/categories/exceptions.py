
"""
 Copyright (C) 2007 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
"""

"""Exceptions encountered when processing categories."""

from gensrc.exceptions import exceptions

class CategoryException(exceptions.GensrcException):
    """Exceptions encountered when processing categories."""

class DuplicateNameException(CategoryException):

    DUPLICATE_NAME_ERROR = """
Cannot create category with name %(categoryName)s
because another category has already been defined with that name."""

    def __init__(self, categoryName):
        """Initialize the DuplicateNameException object."""
        self.value_ = DuplicateNameException.DUPLICATE_NAME_ERROR % {
            'categoryName' : categoryName }

