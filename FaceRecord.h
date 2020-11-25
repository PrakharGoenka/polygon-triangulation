#ifndef FACERECORD_H
#define FACERECORD_H


class FaceRecord {
public:
    int index;
    int inner_component;
    int outer_component;

    FaceRecord(int i) {
        index = i;
        inner_component = -1;
        outer_component = -1;
    }
};

#endif /*FACERECORD_H*/
