/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/* 
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
*/

#include <oh/utilities.hpp>
#include <ohxl/utilities/xlutilities.hpp>
#include <ohxl/conversions/vectortooper.hpp>
#include <ohxl/convert_oper.hpp>

DLL_API void freeOper(XLOPER *px) {
    if ((px->xltype == (xltypeStr | xlbitDLLFree))              // If this is a string allocated by the DLL
        && px->val.str) {                                       // .And if the pointer is not null...
        delete [] px->val.str;                                  // ..Then delete the pointer and return.
    } else if ((px->xltype == (xltypeMulti | xlbitDLLFree))     // If this is an array allocated by the DLL
        && px->val.array.lparray) {                             // .And if the pointer is not null...
        int size = px->val.array.rows * px->val.array.columns;
        for (int i=0; i<size; ++i) {                            // ..Then iterate through the array...
            if (px->val.array.lparray[i].xltype & xltypeStr     // ...If this element is a string...
                &&  px->val.array.lparray[i].val.str) {         // ....And if the pointer is not null...
                delete [] px->val.array.lparray[i].val.str;     // .....Then delete the string...
            }
        }
        delete [] px->val.array.lparray;                        // ..Now delete the array and return.
    }
}

DLL_API bool isList(const OPER *xValue) {
    if (xValue->xltype == xltypeStr) {
        // Must use type unsigned char (BYTE) to process the 0th byte of Excel byte-counted string
        for (unsigned char i=1; i<=xValue->val.str[0]; i++) {
            if (xValue->val.str[i] == ',' || xValue->val.str[i] == ';')
                return true;
        }
    }
    return false;
}

DLL_API void splitOper(const OPER *xFrom, OPER *xTo) {
    std::string text = ObjectHandler::ConvertOper(*xFrom);
    std::vector<std::string> vec = ObjectHandler::split(text, ",;", false);
    ObjectHandler::vectorToOper(vec, *xTo);
}

