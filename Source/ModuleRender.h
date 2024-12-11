#pragma once
#include "Module.h"
#include "Globals.h"

#include <limits.h>

class ModuleRender : public Module
{
public:
	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

    void SetBackgroundColor(Color color);
<<<<<<< Updated upstream
	bool Draw(Texture2D texture, int x, int y, const Rectangle* section = NULL, double angle = 0, int pivot_x = 0, int pivot_y = 0, Color tint = WHITE) const;
    bool DrawText(const char* text, int x, int y, Font font, int spacing, Color tint) const;
=======
	bool Draw(Texture2D texture, int x, int y, const Rectangle* section = NULL, double angle = 0, float scale =1, int pivot_x = 0, int pivot_y = 0, Color tint = WHITE) ;
    bool DrawText(const char* text, int x, int y, Font font, int spacing, Color tint);

	///Layers

	void SelectRenderLayer(RenderLayer layer);
	RenderLayer GetCurrentRenderLayer();

	void BlockRenderLayer(RenderLayer layer);
	void BlockRenderLayer();
	void UnlockRenderLayer();
	bool IsRenderLayerBlocked();

	void ResetRenderLayer();

>>>>>>> Stashed changes

public:

	Color background;
    Rectangle camera;
};