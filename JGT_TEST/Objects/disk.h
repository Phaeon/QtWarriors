#ifndef DISK_H
#define DISK_H

#include "library.h"

class Disk
{
private:
    float _innerRadius;
    float _outerRadius;

public:
    Disk() = default;
    Disk(const Disk & c) = default;
    ~Disk() = default;

    GLvoid createDisk(float innerRadius, float outerRadius);
};

#endif // DISK_H
