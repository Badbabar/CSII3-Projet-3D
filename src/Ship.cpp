#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>

#include "../include/Ship.h"
#include "../include/Shoot.h"
#include "../include/Point.h"
#include "../include/Mine.h"

Ship::Ship()
{
    //ctor
}

Ship::Ship(double x, double y):
    x(x), y(y)
{
    angle = 90;
    speed = 0;
}

Ship::~Ship()
{
    //dtor
}

void Ship::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x,y,0);

    // Rotation du plan;
    glRotated(angle, 0, 0, 1);

    // Dessin du vaisseau ici
    glColor3ub(255, 255, 255);

    // Carlingue
    glBegin(GL_QUADS);
        glVertex2d(-10, 10);
        glVertex2d(10, 10);
        glVertex2d(10, -10);
        glVertex2d(-10, -10);
    glEnd();

    // Aile gauche
    glBegin(GL_TRIANGLES);
        glVertex2d(-8, 0);
        glVertex2d(30, 10);
        glVertex2d(-8, 20);
    glEnd();

    // Aile droite
    glBegin(GL_TRIANGLES);
        glVertex2d(-8, 0);
        glVertex2d(30, -10);
        glVertex2d(-8, -20);
    glEnd();

    // Queue
    glBegin(GL_TRIANGLES);
        glVertex2d(-15, 5);
        glVertex2d(-15, -5);
        glVertex2d(-5, 0);
    glEnd();

    // Remise en état du repère
    glPopMatrix();
}

void Ship::UpdatePositions(double minX, double maxX, double minY, double maxY)
{
    x += cos(angle*M_PI/180)*speed/15;
    y += sin(angle*M_PI/180)*speed/15;

    if (x < minX)
        x = maxX;

    if (x > maxX)
        x = minX;

    if (y < minY)
        y = maxY;

    if (y > maxY)
        y = minY;
}

double Ship::IncrementAngle()
{
    return angle += 2;
}

double Ship::DecrementAngle()
{
    return angle -= 2;
}

double Ship::IncrementSpeed()
{
    ++speed;

    if (speed > 150)
        speed = 150;

    return speed;
}

double Ship::DecrementSpeed()
{
    --speed;

    if (speed < -50)
        speed = -50;

    return speed;
}

double Ship::GetAngle()
{
    return angle;
}

double Ship::GetY()
{
    return y;
}

double Ship::GetX()
{
    return x;
}

Shoot * Ship::Fire(int side)
{
    double shootAngle = angle;

    switch (side)
    {
        case FIRE_LEFT:
            shootAngle += 45;
            break;
        case FIRE_RIGHT:
            shootAngle -= 45;
            break;
    }

    return new Shoot(x, y, shootAngle);
}

Mine * Ship::Drop()
{

    return new Mine(x, y);
}

bool Ship::Collision(double x, double y)
{
    // Box normale quand angle = 0
    Point points[] = {
        Point(-60, 30),
        Point(-60, -30),
        Point(60, -30),
        Point(60, 30),
    };

    int nbPoints = 4;

    Point A, B, D, T;
    double d, theta, x2, y2;

    // Calcul de points selon l'angle
    for(int i = 0; i < nbPoints; i++)
    {
        theta = angle * M_PI / 180;
        x2 = cos(theta) * points[i].x - sin(theta) * points[i].y;
        y2 = sin(theta) * points[i].x + cos(theta) * points[i].y;
        points[i].x = x2 + this->x;
        points[i].y = y2 + this->y;
    }

    // Vérification de la collision
    for(int i = 0; i < nbPoints; i++)
    {
        A = points[i];

        if (i == nbPoints - 1) // si c'est le dernier point, on relie au premier
            B = points[0];
        else // sinon on relie au suivant.
            B = points[i+1];

        D.x = B.x - A.x;
        D.y = B.y - A.y;
        T.x = x - A.x;
        T.y = y - A.y;

        d = D.x*T.y - D.y*T.x;

        if (d < 0)
            return false;  // un point à droite et on arrête tout.
    }

    return true;
}
