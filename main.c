#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h> // for Sleep() and GetTickCount()

#define MAX_H 21
#define MAX_W 42

typedef struct Vector2
{
    int x;
    int y;
} Vector2;

typedef struct Player
{
    Vector2 pos;
    int Level;
} Player;

Player player1;
int game_loop = 1;

Vector2 dir = {0};
Vector2 collectible = {-1, -1}; // initialize as invalid

char Maze[MAX_H][MAX_W];
int visited[(MAX_H / 2) * (MAX_W / 2)];

// Initialize Maze with walls ('#')
void init_Maze()
{
    for (int y = 0; y < MAX_H; y++)
    {
        for (int x = 0; x < MAX_W - 1; x++)
        {
            Maze[y][x] = '#';
        }
        Maze[y][MAX_W - 1] = '\0'; // terminate each row
    }
}
// Generate Maze using Aldous-Broder algorithm
void aldous_broder()
{
    int MAX_W_minas = MAX_W - 1;
    init_Maze();
    int currX = 1, currY = 1; // Start position
    Maze[currY][currX] = ' '; // Mark start as passage

    int remaining = (MAX_H / 2) * (MAX_W_minas / 2) - 1; // Unvisited cells

    while (remaining > 0)
    {
        // Possible moves: right, left, down, up (2 steps to skip walls)
        int directions[4][2] = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
        int r = rand() % 4; // Pick random direction

        int nextX = currX + directions[r][0];
        int nextY = currY + directions[r][1];

        // Ensure the new cell is inside Maze bounds
        if (nextX > 0 && nextX < MAX_W_minas - 1 && nextY > 0 && nextY < MAX_H - 1)
        {
            if (Maze[nextY][nextX] == '#')
            {
                // Open the wall between current and next cell
                Maze[(currY + nextY) / 2][(currX + nextX) / 2] = ' ';
                Maze[nextY][nextX] = ' ';
                remaining--; // One less unvisited cell
            }
            // Move to the next cell
            currX = nextX;
            currY = nextY;
        }
    }
}

// Print the Maze to the console
void print_Maze()
{
    for (int y = 0; y < MAX_H; y++)
    {
        printf("%s\n", Maze[y]);
    }
}

void read_dir()
{
    dir.x = 0;
    dir.y = 0;

    if (_kbhit())
    {
        int input = getch();

        if (input == 0 || input == 224) // special key (arrows, F1..F12)
        {
            input = getch(); // read the real code
            switch (input)
            {
            case 72:
                dir.y = -1;
                break; // Up arrow
            case 80:
                dir.y = 1;
                break; // Down arrow
            case 75:
                dir.x = -1;
                break; // Left arrow
            case 77:
                dir.x = 1;
                break; // Right arrow
            default:
                break;
            }
        }
        else
        {
            switch (input)
            {
            case 'a':
            case 'A':
                dir.x = -1;
                break;
            case 'd':
            case 'D':
                dir.x = 1;
                break;
            case 'w':
            case 'W':
                dir.y = -1;
                break;
            case 's':
            case 'S':
                dir.y = 1;
                break;
            case 'q':
            case 'Q':
                game_loop = 0;
                break;
            default:
                break;
            }
        }
    }
}

void load_level()
{
    aldous_broder(); // Generate Maze
    Maze[MAX_H - 2][MAX_W - 3] = '*';
}
void end()
{
    printf("END (^-^)\n");
}

void move_player()
{
    int nx = player1.pos.x + dir.x;
    int ny = player1.pos.y + dir.y;

    // bounds check to avoid out-of-range access
    if (nx < 0 || nx >= MAX_W || ny < 0 || ny >= MAX_H)
    {
        return;
    }

    if (Maze[ny][nx] != '#')
    {
        player1.pos.x = nx;
        player1.pos.y = ny;
    } // else blocked by wall (stay)

    // picked up collectible?
    if (collectible.x == player1.pos.x && collectible.y == player1.pos.y)
    {
        player1.Level++;
        player1.pos.x = player1.pos.y = 1;
        if (player1.Level > 100)
        {
            end();
        }
        load_level(player1.Level);
    }

    // if walked on a '*' from level file:
    if (Maze[player1.pos.y][player1.pos.x] == '*')
    {
        player1.Level++;
        player1.pos.x = player1.pos.y = 1;
        load_level();
        // switch color
        char color[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
        char CMD_color[20];
        sprintf(CMD_color, "COLOR 0%c", color[rand() % 15]);
        system(CMD_color);
    }
}

int main()
{
    srand((unsigned)time(NULL));

    player1.pos.x = 1;
    player1.pos.y = 1;
    player1.Level = 1;

    load_level();
    DWORD lastTime = GetTickCount();

    while (game_loop)
    {
        DWORD currentTime = GetTickCount();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        Vector2 player_shadow = player1.pos;

        read_dir();
        move_player();

        // render
        system("cls");

        // clear previous shadow (only if inside bounds)
        if (player_shadow.x >= 0 && player_shadow.x < MAX_W &&
            player_shadow.y >= 0 && player_shadow.y < MAX_H)
        {
            // if the map char is '\n' from file or other, ensure we set a space if it was passage
            if (Maze[player_shadow.y][player_shadow.x] == 'O')
                Maze[player_shadow.y][player_shadow.x] = ' ';
        }

        // place player char (do not overwrite walls)
        if (Maze[player1.pos.y][player1.pos.x] != '#')
            Maze[player1.pos.y][player1.pos.x] = 'O';

        // place collectible if valid and location is passage
        if (collectible.x >= 0 && collectible.y >= 0 &&
            Maze[collectible.y][collectible.x] == ' ')
        {
            Maze[collectible.y][collectible.x] = '*';
        }

        printf("LV : %d\n", player1.Level);
        print_Maze();

        printf("Delta Time: %.3f s\n", dt);
        if (dt > 0)
        {
            float fps = 1.0f / dt;
            printf("FPS: %.1f\n", fps);
        }

        Sleep(16); // ~60 FPS
    }

    return 0;
}
