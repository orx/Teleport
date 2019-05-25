/* Orx - Portable Game Engine
 *
 * Copyright (c) 2008-2019 Orx-Project
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

/**
 * @file Teleport.cpp
 * @date 7-Apr-2019
 *
 * Orx Game Template
 */


#include "orx.h"


/** Update function, is called every time the core clock ticks (ie. once per game frame)
 */
void orxFASTCALL Update(const orxCLOCK_INFO *_pstInfo, void *_pContext)
{
    // Gets MainCamera's size & boundaries
    orxVECTOR Size, TL, BR;
    orxConfig_PushSection("MainCamera");
    orxConfig_GetVector("Size", &Size);
    orxConfig_GetVector("TL", &TL);
    orxConfig_GetVector("BR", &BR);
    orxConfig_PopSection();

    // For all "Character" objects
    orxSTRINGID CharacterID = orxString_ToCRC("Character");
    for(orxOBJECT *Object = orxObject_GetNext(orxNULL, CharacterID);
        Object;
        Object = orxObject_GetNext(Object, CharacterID))
    {
        orxVECTOR Pos;

        // Gets its position
        orxObject_GetPosition(Object, &Pos);

        // Wrap its position inside the camera's boundaries
        while(Pos.fX < TL.fX)
        {
            Pos.fX += Size.fX;
        }
        while(Pos.fX > BR.fX)
        {
            Pos.fX -= Size.fX;
        }
        while(Pos.fY < TL.fY)
        {
            Pos.fY += Size.fY;
        }
        while(Pos.fY > BR.fY)
        {
            Pos.fY -= Size.fY;
        }

        // Updates its position
        orxObject_SetPosition(Object, &Pos);
    }
}

/** Init function, is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
    // Display a small hint in console
    orxLOG("\n* This template creates a viewport/camera couple and an object"
    "\n* You can play with the config parameters in ../data/config/Teleport.ini"
    "\n* After changing them, relaunch the template to see the changes.");

    // Init the random seed based on current system time
    orxMath_InitRandom((orxU32)orxSystem_GetRealTime());

    // Create all the viewports (Main + Teleport Overlays)
    orxConfig_PushSection("Teleport");
    for(orxS32 i = 0; i < orxConfig_GetListCount("ViewportList"); i++)
    {
        orxViewport_CreateFromConfig(orxConfig_GetListString("ViewportList", i));
    }
    orxConfig_PopSection();

    // Create the Scene
    orxObject_CreateFromConfig("Scene");

    // Register our update function
    orxClock_Register(orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE), &Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

    // Done!
    return orxSTATUS_SUCCESS;
}

/** Run function, is called every clock cycle
 */
orxSTATUS orxFASTCALL Run()
{
    orxSTATUS eResult = orxSTATUS_SUCCESS;

    // Should quit?
    if(orxInput_IsActive("Quit"))
    {
        // Update result
        eResult = orxSTATUS_FAILURE;
    }

    // Done!
    return eResult;
}

/** Exit function, is called before exiting from orx
 */
void orxFASTCALL Exit()
{
    // Let Orx clean all our mess automatically. :)
}

/** Bootstrap function, called before config is initialized, allowing for early resource storage definition
 */
orxSTATUS orxFASTCALL Bootstrap()
{
    // Add a config storage to find the initial config file
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
    return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
    // Set the bootstrap function to provide at least one resource storage before loading any config files
    orxConfig_SetBootstrap(Bootstrap);

    // Execute our game
    orx_Execute(argc, argv, Init, Run, Exit);

    // Done!
    return EXIT_SUCCESS;
}
