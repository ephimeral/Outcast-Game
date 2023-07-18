#pragma once
#include "stage.h"

class StageBuilder
{
public:
	Stage stageInstance;

public:
	StageBuilder();
	void setDebugRoom(Stage& stage);
};