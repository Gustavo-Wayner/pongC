#include "Rooms.h"

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

using namespace global;

#pragma region RoomManager

bool collide(const Rect &a, const Rect &b)
{
    Rectangle aHitbox = a.Hitbox();
    Rectangle bHitbox = b.Hitbox();

    return CheckCollisionRecs(aHitbox, bHitbox);
}

void RoomManager::Update()
{
    if (current)
        current->Step();
}
#pragma endregion

#pragma region MainMenu
void MainMenu::Setup()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
}
void MainMenu::Step()
{
    bool over = false;
    bool switchRooms = false;
    BeginDrawing();
    ClearBackground(WHITE);
    if (GuiButton({GetScreenWidth() * 0.5f - 120, GetScreenHeight() * 0.5f - 30 - 50, 240, 60}, "Play"))
        switchRooms = true;
    if (GuiButton({GetScreenWidth() * 0.5f - 120, GetScreenHeight() * 0.5f - 30 + 50, 240, 60}, "Quit"))
    {
        over = true;
        closed = true;
    }
    EndDrawing();
    if (switchRooms)
        manager.SwitchTo<Game>();
    if (over)
        CloseWindow();
}
#pragma endregion

#pragma region Game

Game::Game() : player(Vec2{0, 0}, 0, 0), other(Vec2{0, 0}, 0, 0), ball(Vec2{0, 0}, 0, 0) {}

void Game::Setup()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    BackgroundColor = {50, 100, 150, 255};
    increment = 1.5f;
    ballMaxSpeed = 20;
    difficulty = 7;
    SetRandomSeed(time(0));
    player_score = 0;
    other_score = 0;

    player = Rect(Vec2{-400, 0}, 20, 80);
    other = Rect(Vec2{400, 0}, 20, 80);
    ball = Rect(Vec2{0, 0}, 20, 20);

    // initial speed of the ball
    ballSpeed = {-7.0f, (float)GetRandomValue(-3, 3)};
    ballSpeed.SetMagnitude(7);

    ball.velocity = {ballSpeed.x, ballSpeed.y};
    state = State::Unpaused;
}

void Game::Step()
{
    bool switchRooms = false;
    BeginDrawing();
    switch (state)
    {
    case State::Unpaused:
        ClearBackground(BackgroundColor);
        player.velocity = {0, ((float)GetMouseY() - GetScreenHeight() * 0.5f) - player.position.y};
        other.velocity = {0, ball.position.y - other.position.y};
        Vec2::LimitMagnitude(other.velocity, difficulty);
        if (player.getNext().position.y > ScreenHeight * 0.5f + player.Height)
        {
            player.velocity = {0, 0};
        }
        else if (player.getNext().position.y < -ScreenHeight * 0.5f - player.Height)
        {
            player.velocity = {0, 0};
        }
        if (collide(player.getNext(), ball.getNext()))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + increment);
            if (ballSpeed.Magnitude() > ballMaxSpeed)
            {
                ballSpeed.SetMagnitude(ballMaxSpeed);
            }
            ball.velocity = (ball.position - player.position).GetUnitVector();
            ball.velocity.SetMagnitude(ballSpeed.Magnitude());
        }
        else if (collide(other.getNext(), ball.getNext()))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + increment);
            if (ballSpeed.Magnitude() > ballMaxSpeed)
            {
                ballSpeed.SetMagnitude(ballMaxSpeed);
            }
            ball.velocity = (ball.position - other.position).GetUnitVector();
            ball.velocity.SetMagnitude(ballSpeed.Magnitude());
        }

        if (absolute(ball.position.y) + ball.Height > absolute(float(ScreenHeight * 0.5)))
        {
            ball.velocity.y = -ball.velocity.y;
        }
        if (absolute(ball.position.x) > absolute(float(ScreenWidth * 0.5)))
        {
            if (ball.position.x >= ScreenWidth * 0.5)
                player_score++;
            else
                other_score++;

            ball.position = {0, 0};
            ballSpeed = {-3.0, (float)GetRandomValue(-3, 3)};
            ball.velocity = ballSpeed;
        }

        player.position = player.getNext().position;
        other.position = other.getNext().position;
        ball.position = ball.getNext().position;

        ball.Draw();
        other.Draw();
        player.Draw();

        DrawText(TextFormat("%d : %d\n", player_score, other_score), 450, 10, 21, BLACK);
        break;

    case State::Paused:
        if (GuiButton({GetScreenWidth() * 0.5f - 120, GetScreenHeight() * 0.5f - 30 - 50, 240, 60}, "Resume"))
        {
            state = State::Unpaused;
            SetMousePosition(GetMouseX(), player.position.y + GetScreenHeight() * 0.5);
        }
        if (GuiButton({GetScreenWidth() * 0.5f - 120, GetScreenHeight() * 0.5f - 30 + 50, 240, 60}, "Return to main menu"))
            switchRooms = true;
        break;
    }

    EndDrawing();

    if (IsKeyDown(KEY_ESCAPE))
    {
        if (!pressedPause)
        {
            switch (state)
            {
            case State::Unpaused:
                state = State::Paused;
                break;
            case State::Paused:
                state = State::Unpaused;
                SetMousePosition(GetMouseX(), player.position.y + GetScreenHeight() * 0.5);
                break;
            }
        }
        pressedPause = true;
    }
    else
    {
        pressedPause = false;
    }

    if (switchRooms)
    {
        state = State::Unpaused;
        manager.SwitchTo<MainMenu>();
    }
}
#pragma endregion