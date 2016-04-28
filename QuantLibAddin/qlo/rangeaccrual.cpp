/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Giorgio Facchinetti

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email 
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif

#include <qlo/rangeaccrual.hpp>

#include <ql/cashflows/rangeaccrual.hpp>

using ObjectHandler::LibraryObject;
using ObjectHandler::ValueObject;
using boost::shared_ptr;

namespace QuantLibAddin {
    
   RangeAccrualFloatersCoupon::RangeAccrualFloatersCoupon(
                const shared_ptr<ValueObject>& p,
                QuantLib::Real nominal,
                const QuantLib::Date& paymentDate,
                const shared_ptr<QuantLib::IborIndex>& index,
                const QuantLib::Date& startDate,                                  
                const QuantLib::Date& endDate,                                   
                QuantLib::Integer fixingDays,
                const QuantLib::DayCounter& dayCounter,
                QuantLib::Real gearing,
                QuantLib::Rate spread,
                const QuantLib::Date& refPeriodStart,
                const QuantLib::Date& refPeriodEnd,    
                const shared_ptr<QuantLib::Schedule>&  observationsSchedule,
                QuantLib::Real lowerTrigger,                                    
                QuantLib::Real upperTrigger,
                bool permanent)
    : LibraryObject<QuantLib::RangeAccrualFloatersCoupon>(p, permanent)
    {
        libraryObject_ = shared_ptr<QuantLib::RangeAccrualFloatersCoupon>(new
            QuantLib::RangeAccrualFloatersCoupon(paymentDate,
                                                 nominal,
                                                 index,
                                                 startDate,
                                                 endDate,
                                                 fixingDays,
                                                 dayCounter,
                                                 gearing,
                                                 spread,
                                                 refPeriodStart,
                                                 refPeriodEnd,
                                                 observationsSchedule,
                                                 lowerTrigger,
                                                 upperTrigger));
    }

    RangeAccrualFloatersCoupon::RangeAccrualFloatersCoupon(
                const shared_ptr<ValueObject>& properties,
                const QuantLib::Leg& rangeAccrualLeg,
                QuantLib::Size i,
                bool permanent)
    : LibraryObject<QuantLib::RangeAccrualFloatersCoupon>(properties, permanent)
    {
        QL_REQUIRE(i<rangeAccrualLeg.size(), "i>=rangeAccrualLeg.size()");
        libraryObject_ =
            boost::dynamic_pointer_cast<QuantLib::RangeAccrualFloatersCoupon>(rangeAccrualLeg[i]);
    }

    RangeAccrualPricerByBgm::RangeAccrualPricerByBgm(
            const shared_ptr<ValueObject>& properties,
            QuantLib::Real correlation,
            const shared_ptr<QuantLib::SmileSection>& smilesOnExpiry,
            const shared_ptr<QuantLib::SmileSection>& smilesOnPayment,
            bool isClosedFormula,
            bool byCallSpread,
            bool permanent)
    : RangeAccrualPricer(properties, permanent)
    {
      libraryObject_ = shared_ptr<QuantLib::RangeAccrualPricerByBgm>(new
          QuantLib::RangeAccrualPricerByBgm(correlation,
                                            smilesOnExpiry,
                                            smilesOnPayment,
                                            isClosedFormula,
                                            byCallSpread));
    }

}
