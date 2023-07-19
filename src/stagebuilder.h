#pragma once
#include "stage.h"

class StageBuilder
{
public:
	Stage stageInstance; // <- Esto no es usado en ninguna parte, lo dejo por si en algun momento se debe cambiar la lógica del sistema

public:
	StageBuilder();
	void setDebugRoom(Stage& stage);
};