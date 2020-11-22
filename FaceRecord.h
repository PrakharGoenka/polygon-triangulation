#ifndef FACERECORD_H
#define FACERECORD_H


class FaceRecord {
public:
    int index;
    int inner_component;
    int outer_component;

    FaceRecord(int i) {
        index = i;
    }

    void updateInnerComponent(int edge) {
        inner_component = edge;
    }

    void updateOuterComponent(int edge) {
        outer_component = edge;
    }
};

#endif /*FACERECORD_H*/
