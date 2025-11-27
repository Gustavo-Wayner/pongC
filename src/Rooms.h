#pragma once

#include <ctime>
#include <cstdlib>

#include "Objects.h"
#include "Static.h"

bool collide(const Rect &a, const Rect &b);

enum State
{
    Unpaused,
    Paused
};

struct Room
{
    bool pressedPause = false;
    State state = State::Unpaused;
    Color BackgroundColor;
    virtual void Setup() {}
    virtual void Step() {}
};

struct RoomManager
{
    Room *current = nullptr;

    template <typename T>
    void SwitchTo()
    {
        static T roomInstance;
        roomInstance.Setup();
        current = &roomInstance;
    }

    void Update();
};

struct MainMenu : public Room
{
    void Setup() override;
    void Step() override;
};

struct Game : public Room
{
    int player_score;
    int other_score;
    Rect player;
    Rect other;
    Rect ball;
    Vec2 ballSpeed;

    float increment;
    unsigned ballMaxSpeed;
    float difficulty;

    Game();

    void Setup() override;
    void Step() override;
};