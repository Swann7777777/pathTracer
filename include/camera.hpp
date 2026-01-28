class cameraClass {
    public :

    vector3 position;
    vector3 angle;
    float fieldOfView;
    float d;

    cameraClass(vector3 position, float fieldOfView, float d, vector3 roll) {

        this->position = position;
        this->fieldOfView = fieldOfView*M_PI/180;
        this->d = d;
    };
};