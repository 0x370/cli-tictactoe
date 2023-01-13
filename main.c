#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"

/*
        define windows if you're on a windows machine, otherwise feel free to uncomment
        used when cleaning the screen
*/
#define WINDOWS

/*
        Draws tic-tac-toe to console

        @param board: multidimensional array representing the game
        @return nothing
*/
void draw_game(const u8 board[static 3][3])
{
#ifdef WINDOWS
        /* using system is bad practice, but it's also the simplest...*/
        system("cls");
#else
        printf("\e[1;1H\e[2J");
#endif /* WINDOWS */

        for (u8 row = 0; row < 3; ++row)
        {
                for (u8 column = 0; column < 3; ++column)
                {
                        if (board[row][column] == 1)
                                printf("x");
                        else if (board[row][column] == 2)
                                printf("o");
                        else
                                printf("_");
                }
                printf("\n");
        }
}

/*
        Sanity check and places the pieces

        @param team: 0 = none, 1 = player, 2 = bot
        @param x: row to check
        @param y: column to check
        @param board: multidimensional array representing the game
        @return 1 if failed, 0 if succeeded
*/
u8 handle_game(u8 team, u32 x, u32 y, u8 board[static 3][3])
{
        if (x > 2 || y > 2 || team > 2 || team == 0)
                return 1;

        if (board[x][y] == 0)
        {
                board[x][y] = team;
                return 0;
        }

        return 1;
}

/*
        Game logic of tic-tac-toe

        @param board: multidimensional array representing the game
        @return 0 victory, 1 unfinished, 2 tie
*/
u8 check_result(const u8 board[static 3][3])
{
        /* top row */
        if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] > 0)
                return 0;

        /* middle row */
        if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] > 0)
                return 0;

        /* bottom row */
        if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] > 0)
                return 0;

        /* left column */
        if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] > 0)
                return 0;

        /* middle column */
        if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] > 0)
                return 0;

        /* right column */
        if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] > 0)
                return 0;

        /* diagonal left right */
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] > 0)
                return 0;

        /* diagonal right left */
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] > 0)
                return 0;

        /* tie check */
        u8 counter = 0;
        for (u8 x = 0; x < 3; ++x)
        {
                for (u8 y = 0; y < 3; ++y)
                {
                        if (board[x][y] == 0)
                                ++counter;
                }
        }

        if (counter == 0)
                return 2;

        return 1;
}

i32 main(i32 argc, u8 **argv)
{
        u8 board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        u32 x = 0, y = 0;
        u32 bot_x = 0, bot_y = 0;
        u8 result = 1;

        time_t t;
        srand((unsigned)time(&t));

        while (1)
        {
                draw_game(board);

                /* handle player input */
                do
                {
                        printf("\nenter row: ");
                        scanf(" %u", &x);

                        printf("\nenter column: ");
                        scanf(" %u", &y);

                        result = handle_game(1, x, y, board);
                } while (result > 0);

                u8 state = check_result(board);
                if (state == 0)
                {
                        printf("\n\nyou won!!");
                        break;

                        /* player will always have the last move */
                }
                else if (state == 2)
                {
                        printf("\n\nTIE!!!!");
                        break;
                }

                /* handle bot */
                do
                {
                        bot_x = rand() % 3;
                        bot_y = rand() % 3;

                        result = handle_game(2, bot_x, bot_y, board);
                } while (result > 0);

                state = check_result(board);
                if (state == 0)
                {
                        printf("\n\nyou lost!");
                        break;
                }
        }

        return EXIT_SUCCESS;
}
