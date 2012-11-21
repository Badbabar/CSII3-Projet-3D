#ifndef PERSON_H
#define PERSON_H

#include <vector>

#include "Color.h"
#include "Blood.h"

#define PERSON_WALK_STEP_NONE_LEFT   0
#define PERSON_WALK_STEP_NONE_RIGHT   3
#define PERSON_WALK_STEP_LEFT   1
#define PERSON_WALK_STEP_RIGHT  2
#define PERSON_WALK_STEP_FREQUENCY   10

class Person
{
    public:
        Person();
        Person(double x, double y, double angle);
        Person(double minX, double maxX, double minY, double maxY);
        virtual ~Person();
        void Draw();
        void UpdatePositions(double minX, double maxX, double minY, double maxY);
        void SetAlive(bool alive);
        bool IsAlive();
        double GetX();
        double GetY();
        bool Collision(double x, double y);
        void InitColor();
        void InitBloods();
    protected:
        double x;
        double y;
        double angle;
        bool alive;
        Color color;
        std::vector<Blood *> bloods;
        int walk_step;
        int walk_counter;
    private:
};

#endif // PERSON_H
