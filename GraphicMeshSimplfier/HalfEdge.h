#pragma once
class HalfEdge
{
public:
    int origin, target;
    int opposite, incface;

    HalfEdge()
    {
    }

    ~HalfEdge()
    {
    }
};

