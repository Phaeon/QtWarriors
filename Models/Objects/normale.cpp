#include "normale.h"


n normale(float s0x, float s0y, float s0z, float s1x, float s1y, float s1z, float s2x, float s2y, float s2z)
{
    n normale;

    float v0x = s2x - s1x;
    float v0y = s2y - s1y;
    float v0z = s2z - s1z;
    float v1x = s0x - s1x;
    float v1y = s0y - s1y;
    float v1z = s0z - s1z;

    normale.x = (v0y * v1z) - (v0z *v1y);
    normale.y = (v0z * v1x) - (v0x *v1z);
    normale.z = (v0x * v1y) - (v0y *v1x);

    float norme = sqrtf(normale.x * normale.x + normale.y * normale.y + normale.z * normale.z);
    normale.x = normale.x / norme;
    normale.y = normale.y / norme;
    normale.z = normale.z / norme;

    return normale;
}
