//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle
#define VERTICAL 540


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
    
    // ball speed
    double sidemove = drand48() + 3;
    double vertmove = drand48() + 3;

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // mouse controls paddle's horizontal movement
        GEvent event = getNextEvent(MOUSE_EVENT); 
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - 25;
                setLocation(paddle, x, VERTICAL);
            }
        }
        
        //   move the ball
        move(ball, sidemove, vertmove);
        
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            sidemove = -sidemove;
        }
        
        if (getX(ball) <= 0)
        {
            sidemove = -sidemove;
        }    
        
        if (getY(ball) <= 0)
        {
            vertmove = -vertmove;
        }
       
        if (getY(ball) + getWidth(ball) >= 600)
        {   
            lives = lives - 1; 
                
                    if (lives < 1)
                    {
                        waitForClick();
                        closeGWindow(window);
                        return 0;
                    }
                              
            waitForClick();
            setLocation(ball, 190, 290);  
        }
        
        pause(10);
        
        // bounce off bricks and paddle
        GObject object = detectCollision(window, ball); 
        
        if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            vertmove = -vertmove;
        }
        
        // remove bricks hit
        if (object != paddle && object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            removeGWindow(window, object);
            bricks = bricks - 1;
            points = points + 1;
            updateScoreboard(window, label, points);
        }
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{ 
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            GRect brick = newGRect(j * 40 + 5, i * 30 + 50, 30, 20);
            setColor(brick, "yellow");
            setFilled(brick, true);
            add(window, brick);
        }        
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(190, 290,20,20);
    setColor(ball, "orange");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    GRect Paddle = newGRect(175, VERTICAL, 50, 5);
    setColor(Paddle, "blue");
    setFilled(Paddle, true);
    add(window, Paddle);
    return Paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-20");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window,label);   
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
