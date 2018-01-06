#include <stdio.h>
#include <cstdlib>
#include<ctime>
#include<iostream>
#include <SDL.h>
#include <algorithm>

#include <Windows.h>
struct cell{
    int x;
    int y;
    bool visited;
    bool hasLeft;
    bool hasRight;
    bool hasDown;
    bool hasUp;
};
using namespace std;
cell * backToUnvisitedCell(cell grid [10][10]);

int main(int argc, char* argv[]) {
    cell grid [10][10];

    SDL_Window *window;                    // Declare a pointer

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Maze Generation",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }else{
        screenSurface = SDL_GetWindowSurface( window );
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) ); //white background
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                grid[i][j].x=j;
                grid[i][j].y=i;
                grid[i][j].visited=false;
                grid[i][j].hasDown=true;
                grid[i][j].hasLeft=true;
                grid[i][j].hasRight=true;
                grid[i][j].hasUp=true;

                SDL_Rect bigSquare;
                bigSquare.h=10;
                bigSquare.w=10;
                bigSquare.x=320+j*9;
                bigSquare.y=240+i*9;

                SDL_FillRect(screenSurface,&bigSquare,SDL_MapRGB( screenSurface->format, 0x00+i*10+j*10, 0x00+i*10+j*10, 0x00+i*10+j*10 ));

                SDL_Rect smallSquare;
                smallSquare.h=8;
                smallSquare.w=8;
                smallSquare.x=321+j*9;
                smallSquare.y=241+i*9;

                SDL_FillRect(screenSurface,&smallSquare,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
            }
        }
        SDL_Rect verticalLine;
        verticalLine.h=10;
        verticalLine.w=1;

        SDL_Rect horizontalLine;
        horizontalLine.h=1;
        horizontalLine.w=10;

        SDL_UpdateWindowSurface( window );
        cell *currentCell=&grid[5][5];
        cell *compare;
        int nextDirection[4]={1,2,3,4};
        srand (time (0)); //we use this to override the default random shuffle seed
        random_shuffle(&nextDirection[0],&nextDirection[3]);

            while((*currentCell).visited==false){
                    (*currentCell).visited=true;
                    cout << "We are at "<<(*currentCell).x << ", " << (*currentCell).y<<endl;
            random_shuffle(&nextDirection[0],&nextDirection[4]);
            for(int i=0;i<4;i++){
                    cout << "Try "<<i<<endl;
                    if(nextDirection[i]==1 && (*currentCell).hasUp && (*currentCell).y>=1 && grid[(*currentCell).y-1][(*currentCell).x].visited==false){
                                cout << "We go up"<< endl;
                                (*currentCell).hasUp=false;

                                horizontalLine.x=320+(*currentCell).x*9;
                                horizontalLine.y=240+(*currentCell).y*9;
                                SDL_FillRect(screenSurface,&horizontalLine,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));

                                currentCell=&grid[(*currentCell).y-1][(*currentCell).x];
                                (*currentCell).hasDown=false;
                                break;
                            }
                    else if(nextDirection[i]==2 && (*currentCell).hasRight && (*currentCell).x<=8 && grid[(*currentCell).y][(*currentCell).x+1].visited==false){
                                cout << "We go right"<< endl;
                                (*currentCell).hasRight=false;

                                verticalLine.x=320+(*currentCell).x*9+9;
                                verticalLine.y=240+(*currentCell).y*9;
                                SDL_FillRect(screenSurface,&verticalLine,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));

                                currentCell=&grid[(*currentCell).y][(*currentCell).x+1];
                                (*currentCell).hasLeft=false;
                                break;
                            }
                    else if(nextDirection[i]==3 && (*currentCell).hasDown && (*currentCell).y<=8 && grid[(*currentCell).y+1][(*currentCell).x].visited==false){
                                cout << "We go down"<< endl;

                                (*currentCell).hasDown=false;

                                horizontalLine.x=320+(*currentCell).x*9;
                                horizontalLine.y=240+(*currentCell).y*9+9;
                                SDL_FillRect(screenSurface,&horizontalLine,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));

                                currentCell=&grid[(*currentCell).y+1][(*currentCell).x];
                                (*currentCell).hasUp=false;
                                break;
                            }
                    else if(nextDirection[i]==4 && (*currentCell).hasLeft && (*currentCell).x>=1 && grid[(*currentCell).y][(*currentCell).x-1].visited==false){
                                cout << "We go left"<< endl;

                                (*currentCell).hasLeft=false;

                                verticalLine.x=320+(*currentCell).x*9;
                                verticalLine.y=240+(*currentCell).y*9;
                                SDL_FillRect(screenSurface,&verticalLine,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));


                                currentCell=&grid[(*currentCell).y][(*currentCell).x-1];
                                (*currentCell).hasRight=false;
                                break;

                    }else if(i==3){
                            cout << "Dead end reached"<< endl;
                            compare=currentCell;
                            currentCell=backToUnvisitedCell(grid);
                            if(!(compare==currentCell)){
                                (*currentCell).visited=false;   //we can explore more cells from here so we read it as unvisited
                            }
                            break;
                    }

                     SDL_UpdateWindowSurface( window );
                }
            }
    }
    int x;
    cin>>x;
    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
cell * backToUnvisitedCell(cell grid [10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(grid[i][j].visited&&((!(grid[i+1][j].visited)&&i<=8)||(!(grid[i-1][j].visited)&&i>=1)||(!(grid[i][j+1].visited)&&j<=8)||(!(grid[i][j-1].visited)&&j>=1)))
            {
                //we still have areas to explore here
                return &grid[i][j];
            }
        }
    }
    //returning the first visited cell
    return &grid[0][0];
}
