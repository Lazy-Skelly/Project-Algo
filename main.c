#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

int main(int argc, char *argv[]) {
	
	 const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Testing RayLib");

    // TODO: Load resources / Initialize variables at this point

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            // TODO: Draw everything that requires to be drawn at this point:

            DrawText("YEPEE YAY! There will be no wedding bells for today!", 130, 200, 20, LIGHTGRAY);  // Example

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow(); 
    
	return 0;
}
