#include "Interpolator.h"

Vector2d Interpolator::operator()(float t, Vector2d point_0, Vector2d point_1, Vector2d point_2, Vector2d point_3)
{
    Vector2d new_point(0.f, 0.f);

    if (type_ == CATMULL_ROM)
    {
        float coeff_0 = -t * pow(1.f - t, 2.f);
        float coeff_1 = (2.f - 5.f*pow(t, 2.f) + 3.f*pow(t, 3.f));
        float coeff_2 = t * (1.f + 4.f*t - 3.f*pow(t, 2.f));
        float coeff_3 = pow(t, 2.f) * (1.f - t);

        new_point.x_ = 0.5f * (coeff_0 * point_0.x_ + coeff_1 * point_1.x_ + coeff_2 * point_2.x_ - coeff_3 * point_3.x_);
        new_point.y_ = 0.5f * (coeff_0 * point_0.y_ + coeff_1 * point_1.y_ + coeff_2 * point_2.y_ - coeff_3 * point_3.y_);
    }

    return new_point;
}