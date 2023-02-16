#ifndef MODALITE_H
#define MODALITE_H

typedef enum {CM, TD, TP} mod;

class Modalite {

    private:
        mod m;
        int he;
        int capacite;
        bool distanciel;

    public:
        Modalite();
        Modalite(mod m, int he, int capacite);
        Modalite(const Modalite &modalite);

        mod Get_mod() const;
        int Get_he() const;
        int Get_capacite() const;
        bool Get_distanciel() const;

        void covid();
};

#endif