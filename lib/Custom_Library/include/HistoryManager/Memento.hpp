#pragma once

#include "GraphLib.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace CUST_SL
{
    class Memento
    {
        Memento ();
        Memento(const SL::Image &image);

        void save(boost::archive::binary_oarchive & ar, const unsigned int version) const;

        void load(boost::archive::binary_iarchive & ar, const unsigned int version);

        BOOST_SERIALIZATION_SPLIT_MEMBER()

        friend class boost::serialization::access;
        friend class HistoryManager;

        int x_;
        int y_;
        SL::Image state_;
    };
}