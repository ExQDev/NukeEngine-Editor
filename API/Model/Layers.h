#pragma once
#ifndef NUKEE_LAYERS_H
#define NUKEE_LAYERS_H

const unsigned int  	NUKEE_LAYER_DEFAULT	= 1,
                        NUKEE_LAYER_EDITOR	= 2,
                        NUKEE_LAYER_SKY		= 4,
                        NUKEE_LAYER_WATER		= 8,
                        NUKEE_LAYER_CUSTOM	= 16;

//--------------------------- USAGE -------------------------------
// enum MyLayers
// {
//	  MY_LAYER = NUKEE_LAYER_CUSTOM << 1,
//	  My_NEXT_LAYER = MY_LAYER << 1,
//	  ...
// }
//-----------------------------------------------------------------

enum Layer 
{
    L_DEFAULT = NUKEE_LAYER_DEFAULT,
    L_EDITOR = NUKEE_LAYER_EDITOR,
    L_SKY	= NUKEE_LAYER_SKY,
    L_WATER = NUKEE_LAYER_WATER,
    L_CUSTOM = NUKEE_LAYER_CUSTOM
};
#endif
