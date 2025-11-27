#pragma once

#include <raylib.h>
#include "Structs.h"

class GameObject
{
protected:
    Vec2 Pos = {0.0f, 0.0f};
    Rectangle hitbox = {0, 0, 0, 0};

public:
    GameObject() = default;
    GameObject(const GameObject &) = default;

    Color color;
    void Draw()
    {
        DrawRectangle(hitbox.x + GetScreenWidth() * 0.5, hitbox.y + GetScreenHeight() * 0.5, hitbox.width, hitbox.height, color);
    }

    Rectangle Hitbox() const
    {
        return hitbox;
    }

    virtual Vec2 getPosition() { return Pos; }

    void DrawOrigin()
    {
        DrawCircle(Pos.x + GetScreenWidth() * 0.5, Pos.y + GetScreenHeight() * 0.5, 3.0, BLACK);
    }
};

class Rect : public GameObject
{
private:
    struct Position
    {
        Rect *parent;
        float x;
        float y;

        Position() : parent(nullptr), x(0.0f), y(0.0f) {}

        Position(Rect *r) : parent(r), x(r ? r->Pos.x : 0.0f), y(r ? r->Pos.y : 0.0f) {}

        operator Vec2() const
        {
            return parent->Pos;
        }

        Position &operator=(const Vec2 &other)
        {
            parent->Pos = other;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }

        Position &operator=(const Position &other)
        {
            parent->Pos = other;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }

        Position &operator*=(float &scalar)
        {
            parent->Pos.x *= scalar;
            parent->Pos.y *= scalar;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator/=(float scalar)
        {
            parent->Pos.x /= scalar;
            parent->Pos.y /= scalar;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator+=(const Vec2 &other)
        {
            parent->Pos.x += other.x;
            parent->Pos.y += other.y;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator-=(const Vec2 &other)
        {
            parent->Pos.x -= other.x;
            parent->Pos.y -= other.y;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }

        Vec2 operator-(float other[2])
        {
            return {this->x - other[0], this->y - other[1]};
        }

        Vec2 operator-(const Vec2 &other)
        {
            return {this->x - other.x, this->y - other.y};
        }
    };

public:
    double Width, Height;
    Position position;
    Vec2 velocity;

    Rect(Vec2 _position, double _Width, double _Height, Color _color = {255, 255, 255, 255});

    Rect(const Rect &other);

    void UpdateHitbox();
    Vec2 getPosition() override;
    Rect getNext();

    Rect &operator=(const Rect &other);
};