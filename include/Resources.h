#ifndef RESOURCES_H
#define RESOURCES_H


class Resources
{
    private:
        int M, C, D;
    public:
        Resources(int metal, int crystal, int deuterium);
        virtual ~Resources();

        int getMetal();
        int getCrystal();
        int getDeuterium();

        bool setMetal(int M);
        bool setCrystal(int C);
        bool setDeuterium(int D);
};

#endif // RESOURCES_H
