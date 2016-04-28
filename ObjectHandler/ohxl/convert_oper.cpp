/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2008 Plamen Neykov

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

#include <ohxl/convert_oper.hpp>
#include <ohxl/callingrange.hpp>

namespace ObjectHandler {

    ConvertOper::ConvertOper(const OPER &xIn, const bool &decayVectorToScalar) {

        if (decayVectorToScalar && xIn.xltype & xltypeMulti) {
            if (xIn.val.array.rows == 1 && xIn.val.array.columns == 1) {
                oper_ = &xIn.val.array.lparray[0];
            } else {
                OH_FAIL("input value is vector or matrix, expected scalar");
            }
        } else {
            oper_ = &xIn;
        }        
    }

    ConvertOper::operator long() const {
        if (oper_->xltype & xltypeNum)
            return static_cast<long>(oper_->val.num);
        else {
            OPER xLong;
            Excel(xlCoerce, &xLong, 2, oper_, TempInt(xltypeInt));
            return xLong.val.w;
        }
    }

    ConvertOper::operator unsigned int() const {
        if (oper_->xltype & xltypeNum)
            return static_cast<unsigned int>(oper_->val.num);
        else {
            OPER xLong;
            Excel(xlCoerce, &xLong, 2, oper_, TempInt(xltypeInt));
            return xLong.val.w;
        }
    }

    ConvertOper::operator double() const {
        if (oper_->xltype & xltypeNum)
            return oper_->val.num;
        else {
            OPER xDouble;
            Excel(xlCoerce, &xDouble, 2, oper_, TempInt(xltypeNum));
            return xDouble.val.num;
        }
    }

    ConvertOper::operator bool() const {
        if (oper_->xltype & xltypeBool)
            //return oper_->val.boolean != 0;
            return oper_->val.xbool != 0;
        else {
            OPER xBool;
            Excel(xlCoerce, &xBool, 2, oper_, TempInt(xltypeBool));
            //return xBool.val.boolean != 0;
            return xBool.val.xbool != 0;
        }
    }

    ConvertOper::operator std::string() const {
        const OPER *xString;
        Xloper xTemp;
        if (oper_->xltype & xltypeStr) {
            xString = oper_;
        } else {
            Excel(xlCoerce, &xTemp, 2, oper_, TempInt(xltypeStr));
            xString = &xTemp;
        }
        return strConv(xString);
    }

    const std::type_info& ConvertOper::type() const {
        if(oper_->xltype & xltypeNum)
            return typeid(double);
        else if(oper_->xltype & xltypeBool)
            return typeid(bool);
        else if(oper_->xltype & xltypeStr)
            return typeid(std::string);
        else if(missing() || error())
            return typeid(empty_property_tag);
        else
            OH_FAIL("ConvertOper: unexpected datatype: " << oper_->xltype);
    }

    ConvertOper::operator property_t() const {
        if (missing()) {
            return empty_property_tag();
        } else if (error()) {
            return empty_property_tag();
        } else if (oper_->xltype & xltypeNum) {
            return oper_->val.num;
        } else if (oper_->xltype & xltypeBool) {
            //return oper_->val.boolean != 0;
            return oper_->val.xbool != 0;
        } else if (oper_->xltype & xltypeStr) {
            return strConv(oper_);
        } else {
            OH_FAIL("ConvertOper: unexpected datatype: " << oper_->xltype);
        }
    }

    bool ConvertOper::missing() const {
        return (oper_->xltype & xltypeNil
        ||  oper_->xltype & xltypeMissing
        ||  oper_->xltype & xltypeErr && oper_->val.err == xlerrNA);
    }

    bool ConvertOper::error() const {
        return (oper_->xltype & xltypeErr && oper_->val.err != xlerrNA);
    }

    /*Type ConvertOper::type() const {
        if (missing()) {
            return Null;
        } else if (error()) {
            return Error;
        } else if (oper_->xltype & xltypeNum) {
            return Double;
        } else if (oper_->xltype & xltypeBool) {
            return Boolean;
        } else if (oper_->xltype & xltypeStr) {
            return String;
        } else if (oper_->xltype & xltypeMulti) {
            return Array;
        } else {
            OH_FAIL("unknown type");
        }
    }*/

    std::string ConvertOper::strConv(const OPER *xString) {
        std::string ret;
        if (xString->val.str) {
            // Must use type unsigned char (BYTE) to inspect the 0th byte of Excel byte-counted string
            unsigned char len = xString->val.str[0];
            if (len)
                ret.assign(xString->val.str + 1, len);
        }

        // FIXME - We have converted an OPER to a std::string.  Certain callers
        // of this function have passed in an Excel format object ID e.g.
        // "my_object#00123" and need us to strip off the trailing "#00123",
        // so we call getStub().  This conversion should be done only when
        // it's definitely required.
        //return ret;
        return CallingRange::getStub(ret);
    }

}
