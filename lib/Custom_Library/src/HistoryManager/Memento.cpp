#include "Memento.hpp"

namespace CUST_SL
{
    Memento::Memento () {}
    Memento::Memento(const SL::Image &image):
        x_(image.getSize().x_),
        y_(image.getSize().y_),
        state_(image)
    {}

    void Memento::save(boost::archive::binary_oarchive & ar, const unsigned int version) const
    {
        ar & x_;
        ar & y_;

        void *ptr = const_cast<void *>(reinterpret_cast<const void *>(state_.getPixelsPtr()));
        ar.save_binary(ptr, x_ * y_ * 4);
    }

    void Memento::load(boost::archive::binary_iarchive & ar, const unsigned int version)
    {
        ar & x_;
        ar & y_;

        state_.create(SL::Vector2d(x_, y_), SL::Color(0.f, 0.f, 0.f));
        void *ptr = const_cast<void *>(reinterpret_cast<const void *>(state_.getPixelsPtr()));
        ar.load_binary(ptr, x_ * y_ * 4);
    }
}