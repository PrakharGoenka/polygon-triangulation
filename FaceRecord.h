#ifndef FACERECORD_H
#define FACERECORD_H

#include "EdgeRecord.h"

class FaceRecord {
public:
    EdgeRecord inner_component;
    EdgeRecord outer_component;

    void updateInnerComponent(EdgeRecord edge) {
        inner_component = edge;
    }

    void updateOuterComponent(EdgeRecord edge) {
        outer_component = edge;
    }
};

#endif /*FACERECORD_H*/
