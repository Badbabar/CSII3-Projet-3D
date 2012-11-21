#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/Mine.h"

#include <stdlib.h>
#include <time.h>

Mine::Mine()
{
    //ctor
}

Mine::Mine(double x, double y):
    x(x), y(y)
{
    state = MINE_STATE_ARMED_NORMAL;
    timer = SDL_GetTicks();
    armed_counter = 0;
}

Mine::~Mine()
{
    //dtor
}

void Mine::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x, y, 0);

    GLUquadricObj* quadric = gluNewQuadric();

    switch (state) {
        case MINE_STATE_ARMED_NORMAL:
            // Bordure noire
            glColor3ub(40, 40, 40);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, 8, 16, 8);

            // Centre rouge
            glColor3ub(250, 150, 150);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, 4, 16, 8);
            break;
        case MINE_STATE_ARMED_BLINK:
            // Bordure noire
            glColor3ub(40, 40, 40);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, 8, 16, 8);

            // Centre rouge
            glColor3ub(250, 0, 0);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, 4, 16, 8);
            break;
        case MINE_STATE_EXPLOSE1:
            // Centre jaune
            glColor3ub(245, 165, 17);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON1, 16, 8);
            break;
        case MINE_STATE_EXPLOSE2:
            // Centre jaune
            glColor3ub(245, 165, 17);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON2, 32, 8);

            // Centre orange
            glColor3ub(232, 122, 5);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON1, 16, 8);
            break;
        case MINE_STATE_EXPLOSE3:
            // Centre jaune
            glColor3ub(245, 165, 17);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON3, 48, 8);

            // Centre orange
            glColor3ub(232, 122, 5);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON2, 32, 8);

            // Centre rouge
            glColor3ub(242, 60, 2);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluDisk(quadric, 0, MINE_STATE_EXPLOSE_RAYON1, 16, 8);
            break;
    }

    // Remise en état du repère
    glPopMatrix();
}

double Mine::GetY()
{
    return y;
}

double Mine::GetX()
{
    return x;
}

int Mine::GetState()
{
    return state;
}

void Mine::UpdateState()
{
    Uint32 diff = SDL_GetTicks() - timer;

    if (diff < 2000) {
        if (armed_counter > 5)
        {
            switch (state)
            {
                case MINE_STATE_ARMED_NORMAL:
                    state = MINE_STATE_ARMED_BLINK;
                    break;
                case MINE_STATE_ARMED_BLINK:
                    state = MINE_STATE_ARMED_NORMAL;
                    break;
            }

            armed_counter = 0;
        } else {
            armed_counter++;
        }
    } else if (diff < 2200) {
        state = MINE_STATE_EXPLOSE1;
    } else if (diff < 2400) {
        state = MINE_STATE_EXPLOSE2;
    } else if (diff < 2800) {
        state = MINE_STATE_EXPLOSE3;
    } else {
        state = MINE_STATE_EXPLOSED;
    }
}

bool Mine::Collision(double x, double y)
{
    double rayon;

    switch (state)
    {
        case MINE_STATE_EXPLOSE1:
            rayon = MINE_STATE_EXPLOSE_RAYON1;
            break;
        case MINE_STATE_EXPLOSE2:
            rayon = MINE_STATE_EXPLOSE_RAYON2;
            break;
        case MINE_STATE_EXPLOSE3:
            rayon = MINE_STATE_EXPLOSE_RAYON3;
            break;
        default:
            return false;
            break;
    }

    double d = (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y);

    if (d > rayon*rayon)
        return false;
    else
        return true;
}

bool Mine::IsArmed()
{
    return (state == MINE_STATE_ARMED_BLINK || state == MINE_STATE_ARMED_NORMAL);
}
