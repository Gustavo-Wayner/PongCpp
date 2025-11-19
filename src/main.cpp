#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Objects.h"

constexpr unsigned max = 8;
static constexpr int screenWidth = 900;
static constexpr int screenHeight = 600;

int sign(float num) { return ((num > 1) - (num < 1)); }
float abs(float num) { return num * sign(num); }

bool collide(Rect a, Rect b)
{
    gwe::Rectangle aHitbox = a.Hitbox();

    gwe::Rectangle bHitbox = b.Hitbox();

    bool collideX = (aHitbox.left() <= bHitbox.right()) && (aHitbox.right() >= bHitbox.left());
    bool collideY = (aHitbox.top() <= bHitbox.bottom()) && (aHitbox.bottom() >= bHitbox.top());

    return collideX && collideY;
}

int main()
{
    srand(time(0));
    int player_score = 0;
    int other_score = 0;

    const Color darkGreen = {20, 160, 133, 255};

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    Rect player(gwe::Vector2{-400, 0}, 20, 80);
    Rect other(gwe::Vector2{400, 0}, 20, 80);
    Rect ball(gwe::Vector2{0, 0}, 20, 20);

    gwe::Vector2 ballSpeed = {-3.0, (float)GetRandomValue(-4, 4)};

    gwe::Vector2 ballDir = {ballSpeed.x, ballSpeed.y};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        gwe::Vector2 botdir = {0, (ball.position.y - other.position.y)};
        gwe::LimitMagnitude(botdir, 6);
        Rect nextPos = player;
        nextPos.position = {-400.0, (float)GetMouseY() - (float)screenHeight * 0.5f};
        if (nextPos.position.y > screenHeight * 0.5)
        {
            nextPos.position = {-400, screenHeight * 0.5};
        }
        else if (nextPos.position.y < -screenHeight * 0.5)
        {
            nextPos.position = {-400, -screenHeight * 0.5};
        }

        Rect nextBotPos = other;
        nextBotPos.position += botdir;
        Rect nextBallPos = ball;
        if (collide(player, nextBallPos))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + 0.5);
            if (ballSpeed.Magnitude() > max)
            {
                ballSpeed.SetMagnitude(max);
            }
            ballDir = (ball.position - player.position).GetUnitVector();
            ballDir.SetMagnitude(ballSpeed.Magnitude());
        }
        else if (collide(other, nextBallPos))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + 0.5);
            if (ballSpeed.Magnitude() > max)
            {
                ballSpeed.SetMagnitude(max);
            }
            ballDir = (ball.position - other.position).GetUnitVector();
            ballDir.SetMagnitude(ballSpeed.Magnitude());
        }

        if (abs(ball.position.y) > abs(float(screenHeight * 0.5)))
        {
            ballDir.y = -ballDir.y;
        }
        if (abs(ball.position.x) > abs(float(screenWidth * 0.5)))
        {
            if (ball.position.x >= screenWidth * 0.5)
                player_score++;
            else
                other_score++;
            ball.position = {0, 0};
            ballSpeed = {-3.0, (float)GetRandomValue(-3, 3)};
            ballDir = ballSpeed;
        }

        nextBallPos.position += ballDir;

        player.position = nextPos.position;
        other.position = nextBotPos.position;
        ball.position = nextBallPos.position;

        ball.Draw();

        other.Draw();
        player.Draw();

        DrawText(TextFormat("%d : %d\n", player_score, other_score), 450, 10, 21, BLACK);

        EndDrawing();
    }

    CloseWindow();
}