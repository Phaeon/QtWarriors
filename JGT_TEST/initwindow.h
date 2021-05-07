#ifndef INITWINDOW_H
#define INITWINDOW_H

#include "library.h"
#include "actions.h"

void InitializeScene();

int InitWindow(int argc, char** argv, void (*DrawGLScene)());

#endif // INITWINDOW_H
