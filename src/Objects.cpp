#include "Objects.h"

Rect::Rect(Vec2 _position, double _Width, double _Height, Color _color) : Width(_Width), Height(_Height), position(this)
{
    color = _color;
    Pos = _position;
    position = Position(this);

    hitbox.height = Height;
    hitbox.width = Width;
    UpdateHitbox();
}

Rect::Rect(const Rect &other) : Width(other.Width), Height(other.Height), position(this)
{
    Pos = other.Pos;
    color = other.color;

    velocity = other.velocity;

    hitbox = other.hitbox;
    UpdateHitbox();
}

Vec2 Rect::getPosition() { return position; }

void Rect::UpdateHitbox()
{
    hitbox.x = position.x - Width * 0.5f;
    hitbox.y = position.y - Height * 0.5f;
}

Rect &Rect::operator=(const Rect &other)
{
    Width = other.Width;
    Height = other.Height;
    color = other.color;
    Pos = other.Pos;

    velocity = other.velocity;

    hitbox = other.hitbox;
    UpdateHitbox();
    return *this;
}

Rect Rect::getNext()
{
    Vec2 pos = (Vec2)position + velocity;
    return Rect(pos, hitbox.width, hitbox.height, color);
}