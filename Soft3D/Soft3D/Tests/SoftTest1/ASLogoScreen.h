#pragma once
#include <AppState.h>

class nodeEntity;
class sceneGraph;
class nodeCamera;
class pixelMap;
class QuickDraw;
class Texture2D;
class nodeLight;


class ASLogoScreen :
    public AppState
{
public:

    void Init();
    void Update();
    void Render();

private:

    nodeEntity* worldMap;
    nodeEntity* logoMesh;
    sceneGraph* g1;
    nodeCamera* cam;
    pixelMap* tex1;

    QuickDraw* m_Draw;
    Texture2D* m_Title;
    nodeLight* l1;
};

