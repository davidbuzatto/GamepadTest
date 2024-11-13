/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

bool l1Down;
bool l2Down;
bool r1Down;
bool r2Down;

bool leftDown;
bool upDown;
bool rightDown;
bool downDown;

bool middleLeftDown;
bool middleRightDown;
bool leftThumbDown;
bool rightThumbDown;

bool squareDown;
bool triangleDown;
bool circleDown;
bool xDown;

float lx;
float ly;
float rx;
float ry;
float z;
float leftTriggerPressure;
float rightTriggerPressure;

int buttons[] = {
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,
    GAMEPAD_BUTTON_LEFT_FACE_UP,
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_MIDDLE_LEFT,
    GAMEPAD_BUTTON_MIDDLE_RIGHT,
    GAMEPAD_BUTTON_LEFT_THUMB,
    GAMEPAD_BUTTON_RIGHT_THUMB,
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
    GAMEPAD_BUTTON_RIGHT_FACE_UP,
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2
};

char* labels[] = {
    "left", "up", "right", "down", "select", "start", "left thumb", "right thumb",
    "Square/X", "Triangle/Y", "Circle/B", "Cross/A", "L1/LB", "L2/LT", "R1/RB", "R2/RT"
};

bool states[16][4] = {0};

int currentGamepad = 0;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->dummy = 0;

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    l1Down = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1 );
    l2Down = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2 );
    r1Down = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1 );
    r2Down = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2 );
    
    leftDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT );
    upDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_FACE_UP );
    rightDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT );
    downDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN );
    
    middleLeftDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_MIDDLE_LEFT );
    middleRightDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT );
    leftThumbDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_LEFT_THUMB );
    rightThumbDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_THUMB );
    
    triangleDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP );
    circleDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT );
    xDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN );
    squareDown = IsGamepadButtonDown( currentGamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT );
    
    lx = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_LEFT_X );
    ly = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_LEFT_Y );
    rx = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_RIGHT_X );
    ry = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_RIGHT_Y );
    leftTriggerPressure = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_LEFT_TRIGGER );
    rightTriggerPressure = GetGamepadAxisMovement( currentGamepad, GAMEPAD_AXIS_RIGHT_TRIGGER );
    
    for ( int i = 0; i < 16; i++ ) {
        states[i][0] = IsGamepadButtonPressed( currentGamepad, buttons[i] );
        states[i][1] = IsGamepadButtonReleased( currentGamepad, buttons[i] );
        states[i][2] = IsGamepadButtonDown( currentGamepad, buttons[i] );
        states[i][3] = IsGamepadButtonUp( currentGamepad, buttons[i] );
    }
    
    if ( IsKeyPressed( KEY_SPACE ) ) {
        if ( currentGamepad == 0 ) {
            currentGamepad = 1;
        } else {
            currentGamepad = 0;
        }
    }

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    DrawRectangle( 40, 60, 60, 30, l2Down ? GOLD : GRAY );
    DrawRectangle( 40, 90 - 30 * leftTriggerPressure, 60, 30 * leftTriggerPressure, BLUE );
    DrawRectangle( 40, 110, 60, 30, l1Down ? GOLD : GRAY );
    DrawText( TextFormat( "%.3f", leftTriggerPressure ), 40, 40, 14, BLACK );
    
    DrawRectangle( 320, 60, 60, 30, r2Down ? GOLD : GRAY );
    DrawRectangle( 320, 90 - 30 * rightTriggerPressure, 60, 30 * rightTriggerPressure, BLUE );
    DrawRectangle( 320, 110, 60, 30, r1Down ? GOLD : GRAY );
    DrawText( TextFormat( "%.3f", rightTriggerPressure ), 320, 40, 14, BLACK );
    
    DrawRectangle( 160, 60, 100 * ( z + 1 ) / 2, 30, BLUE );
    DrawRectangleLines( 160, 60, 100, 29, BLACK );
    DrawText( TextFormat( "%+.3f", z ), 175, 68, 20, BLACK );
    
    DrawRectangle( 10, 210, 40, 40, leftDown ? GOLD : GRAY );
    DrawRectangle( 50, 170, 40, 40, upDown ? GOLD : GRAY );
    DrawRectangle( 90, 210, 40, 40, rightDown ? GOLD : GRAY );
    DrawRectangle( 50, 250, 40, 40, downDown ? GOLD : GRAY );
    
    DrawRectangle( 160, 220, 40, 20, middleLeftDown ? GOLD : GRAY );
    DrawRectangle( 220, 220, 40, 20, middleRightDown ? GOLD : GRAY );
    
    DrawCircle( 135, 340, 40, LIGHTGRAY );
    DrawCircle( 135, 340, 20, leftThumbDown ? GOLD : GRAY );
    DrawCircle( 135 + 25 * lx, 340 + 25 * ly, 15, BLACK );
    
    DrawCircle( 285, 340, 40, LIGHTGRAY );
    DrawCircle( 285, 340, 20, rightThumbDown ? GOLD : GRAY );
    DrawCircle( 285 + 25 * rx, 340 + 25 * ry, 15, BLACK );
    
    DrawCircle( 310, 230, 20, squareDown ? PINK : GRAY );
    DrawCircle( 350, 190, 20, triangleDown ? LIME : GRAY );
    DrawCircle( 390, 230, 20, circleDown ? RED : GRAY );
    DrawCircle( 350, 270, 20, xDown ? BLUE : GRAY );
    
    DrawPoly( (Vector2) { 310, 230 }, 4, 15, 45, BLACK );
    DrawPoly( (Vector2) { 350, 190 }, 3, 12, 30, BLACK );
    DrawCircleLines( 390, 228, 12, BLACK );
    DrawLine( 342, 262, 358, 278, BLACK );
    DrawLine( 342, 278, 358, 262, BLACK );
    
    int xt = 530;
    int yt = 60;
    int w = 20;
    DrawText( "pressed", xt+5, yt-10, -45, BLACK );
    DrawText( "released", xt+25, yt-10, -45,  BLACK );
    DrawText( "down", xt+45, yt-10, -45, BLACK );
    DrawText( "up", xt+65, yt-10, -45, BLACK );
    for ( int i = 0; i < 16; i++ ) {
        DrawText( labels[i], xt - 10 - MeasureText( labels[i], 14 ), yt + 5 + w * i, 14, BLACK );
        for ( int j = 0; j < 4; j++ ) {
            DrawRectangle( xt + w * j, yt + w * i, w, w, states[i][j] ? GOLD : GRAY );
            DrawRectangleLines( xt + w * j, yt + w * i, w, w, BLACK );
        }
    }
    
    DrawFPS( 10, 10 );

    EndDrawing();

}