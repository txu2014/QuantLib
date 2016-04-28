/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Eric Ehlers

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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif
#include <qlo/exercise.hpp>
#include <ql/exercise.hpp>

namespace QuantLibAddin {

    AmericanExercise::AmericanExercise(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& earliestDate,
            const QuantLib::Date& latestDate,
            const bool payoffAtExpiry,
            bool permanent) : Exercise(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::Exercise>(new
            QuantLib::AmericanExercise(earliestDate,
                                       latestDate,
                                       payoffAtExpiry));
    }

    EuropeanExercise::EuropeanExercise(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& expiryDate,
            bool permanent) : Exercise(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::Exercise>(new
            QuantLib::EuropeanExercise(expiryDate));
    }

    BermudanExercise::BermudanExercise(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::vector<QuantLib::Date>& dates,
            const bool payoffAtExpiry,
            bool permanent) : Exercise(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::Exercise>(new
            QuantLib::BermudanExercise(dates,
                                       payoffAtExpiry));
    }

}

