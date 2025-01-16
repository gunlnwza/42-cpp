#ifndef ENTITY_H
# define ENTITY_H

class Entity
{
    public:
        Entity(void);
        Entity(const Entity& other);
        Entity& operator=(const Entity& other);
        ~Entity(void);

        void moveX(int dx);
        void moveY(int dy);
        void move(int dx, int dy);

        int getX(void);
        int getY(void);

    private:
        int x;
        int y;
};

#endif
