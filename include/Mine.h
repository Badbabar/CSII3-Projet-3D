#ifndef MINE_H
#define MINE_H

#include <SDL/SDL.h>

#define MINE_STATE_ARMED_NORMAL     0
#define MINE_STATE_ARMED_BLINK      1
#define MINE_STATE_EXPLOSE1         2
#define MINE_STATE_EXPLOSE2         3
#define MINE_STATE_EXPLOSE3         4
#define MINE_STATE_EXPLOSED         5

#define MINE_STATE_EXPLOSE_RAYON1   40
#define MINE_STATE_EXPLOSE_RAYON2   70
#define MINE_STATE_EXPLOSE_RAYON3   140

class Mine
{
    public:
        Mine();
        Mine(double x, double y);
        virtual ~Mine();
        double GetX();
        double GetY();
        int GetState();
        void Draw();
        void UpdateState();
        bool Collision(double x, double y);
        bool IsArmed();
    protected:
        double x;
        double y;
        int state;
        Uint32 timer;
        Uint32 armed_counter;
    private:
};

#endif // MINE_H
