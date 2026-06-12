#include "_collisioncheck.h"

_collisionCheck::_collisionCheck()
{
}

_collisionCheck::~_collisionCheck()
{
}

bool _collisionCheck::isLinearCol(vec3, vec3)
{
    return false;
}

bool _collisionCheck::isRadialCol(vec3 p1, vec3 p2, float r1, float r2, float thrld)
{
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float dz = p1.z - p2.z;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);

    return distance <= (r1 + r2 + thrld);
}

bool _collisionCheck::isPlanoCol(vec3, vec3)
{
    return false;
}

bool _collisionCheck::isAABBCol(vec3 pos1, vec3 scale1, vec3 pos2, vec3 scale2)
{
    float aLeft = pos1.x - fabs(scale1.x);
    float aRight = pos1.x + fabs(scale1.x);
    float aBottom = pos1.y - fabs(scale1.y);
    float aTop = pos1.y + fabs(scale1.y);

    float bLeft = pos2.x - fabs(scale2.x);
    float bRight = pos2.x + fabs(scale2.x);
    float bBottom = pos2.y - fabs(scale2.y);
    float bTop = pos2.y + fabs(scale2.y);

    return aLeft < bRight && aRight > bLeft && aBottom < bTop && aTop > bBottom;
}
