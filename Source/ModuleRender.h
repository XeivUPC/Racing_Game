#pragma once
#include "Module.h"
#include "Globals.h"
#include "CursorChanger.h"

#include <limits.h>
#include <vector>

class ModuleRender : public Module
{
public:
	enum RenderLayer {
		SUB_LAYER_5,
		SUB_LAYER_4,
		SUB_LAYER_3,
		SUB_LAYER_2,
		SUB_LAYER_1,
		DEFAULT,
		OVER_LAYER_1,
		OVER_LAYER_2,
		OVER_LAYER_3,
		OVER_LAYER_4,
		OVER_LAYER_5,
		DEBUG_LAYER_DO_NOT_USE
	};

	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

    void SetBackgroundColor(Color color);
	bool Draw(Texture2D texture, Vector2 position, Vector2 offset, const Rectangle* section = NULL, double angle = 0, float scale =1, int pivot_x = 0, int pivot_y = 0, Color tint = WHITE);

	bool DrawSimpleRectangle(Rectangle bounds, Color tint = WHITE);
	bool DrawSimpleCircle(Vector2 position, float radius, Color tint = WHITE);
	bool DrawSimpleLine(Rectangle bounds, Color tint = WHITE);
	bool DrawSimpleCircleLine(Vector2 position, float radius, Color tint = WHITE);


	bool DrawText(const char* text, Vector2 position, Vector2 offset, Font font, int fontSize, int spacing, Color tint);

	///Layers

	void SelectRenderLayer(RenderLayer layer);
	RenderLayer GetCurrentRenderLayer();

	void BlockRenderLayer(RenderLayer layer);
	void BlockRenderLayer();
	void UnlockRenderLayer();
	bool IsRenderLayerBlocked();

	void ResetRenderLayer();


public:

	Color background;
	Camera2D camera;
	CursorChanger cursor;

private:

	struct Layer {
		RenderLayer layer;
		RenderTexture2D data;
	};

	void RenderLayerToScreen(Layer layer);
	void CreateLayer(RenderLayer layer);
	void CleanRenderLayer(Layer layer);
	

	std::vector<Layer> layers;
	RenderLayer currentRenderLayer = DEFAULT;
	bool blockRenderLayer = false;
};