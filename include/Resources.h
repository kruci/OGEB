#ifndef RESOURCES_H
#define RESOURCES_H


class Resources
{
    private:
        int M, C, D;
    public:
        Resources(int metal, int crystal, int deuterium);
        virtual ~Resources();

        inline int getMetal();
        inline int getCrystal();
        inline int getDeuterium();

        inline bool setMetal(int M);
        inline bool setCrystal(int C);
        inline bool setDeuterium(int D);
};

#endif // RESOURCES_H
