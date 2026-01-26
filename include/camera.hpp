class cameraClass {
    public :

    vector3 position_;
    vector3 angle_;
    float fieldOfView_;
    float d;

    cameraClass(vector3 position, vector3 angle, int fieldOfView) {

        position_ = position;
        angle_ = angle;
        fieldOfView_ = fieldOfView*M_PI*180;
        d = 1/tan(fieldOfView_/2);
    };
};