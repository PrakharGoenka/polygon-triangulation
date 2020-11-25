#ifndef FACERECORD_H
#define FACERECORD_H


/*! Class that abstracts a record in the face table */
class FaceRecord {
public:
    int index;
    int inner_component;
    int outer_component;

    /*! Constructor for the class FaceRecord */
    FaceRecord(int i) {
        index = i;
        inner_component = -1;
        outer_component = -1;
    }
};

#endif /*FACERECORD_H*/
