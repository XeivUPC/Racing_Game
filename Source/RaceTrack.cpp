#include "RaceTrack.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"
#include "MapLapSensor.h"
#include "ConeObstacle.h"
#include "RockObstacle.h"
#include "FenceObstacle.h"

#include <pugixml.hpp>
#include <sstream>
using namespace pugi;

RaceTrack::RaceTrack(Module* moduleAt, string trackPath) : MapObject(moduleAt)
{
	this->trackPath = trackPath;

	LoadTrack();
}

RaceTrack::~RaceTrack()
{
}

vector<MapLapSensor*> RaceTrack::GetTrackSensors()
{
	return mapLapSensors;
}

vector<Vector2> RaceTrack::GetTrackStartingPositions()
{
	return startingPositions;
}

update_status RaceTrack::Update()
{
	for (const auto& sensor : mapLapSensors)
		sensor->Update();

	for (const auto& obstacle : trackObstacles)
		obstacle->Update();
	return UPDATE_CONTINUE;
}

bool RaceTrack::Render()
{
	moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_5);
	Rectangle rect = { 0,0,2440,1272 };
	moduleAt->App->renderer->Draw(*trackTexture, { 0,0 }, { 0,0 },&rect, 0, mapScale);

	for (const auto& obstacle : trackObstacles)
		obstacle->Render();

	return true;
}

bool RaceTrack::CleanUp()
{
	for (const auto& collider : trackColliders) {
		delete collider;
	}

	for (const auto& sensor : mapLapSensors) {
		sensor->CleanUp();
		delete sensor;
	}
	for (const auto& obstacle : trackObstacles){
		obstacle->CleanUp();
		delete obstacle;
	}
	trackColliders.clear();
	mapLapSensors.clear();
	trackObstacles.clear();
	startingPositions.clear();

	return true;
}

float RaceTrack::GetScale()
{
	return mapScale;
}

void RaceTrack::LoadTrack()
{
	pugi::xml_document trackFile;
	pugi::xml_parse_result result = trackFile.load_file(trackPath.c_str());

	ModulePhysics* physics = moduleAt->App->physics;
	const Box2DFactory& factory = physics->factory();

	if (result)
	{
		LOG("config.xml parsed without errors");

		xml_node map_node = trackFile.child("map");


		/*Texture From Tiled*/

		xml_node imageLayer_node = map_node.child("imagelayer");
		xml_node textureId_node = imageLayer_node.child("properties").find_child_by_attribute("property", "name","TextureID");
		string textureId = textureId_node.attribute("value").as_string();
		trackTexture = moduleAt->App->texture->GetTexture(textureId);
		

		/*Other things*/

		xml_node mapScale_node = map_node.child("properties").find_child_by_attribute("property", "name", "MapScale");
		mapScale = mapScale_node.attribute("value").as_float();

		for (xml_node objectGroup_node = map_node.child("objectgroup"); objectGroup_node != NULL; objectGroup_node = objectGroup_node.next_sibling("objectgroup")) {

			string objectGroup_name = objectGroup_node.attribute("name").as_string();

			if (objectGroup_name == "Collisions") {

				///Create Map Colliders
				for (pugi::xml_node collisionNode = objectGroup_node.child("object"); collisionNode != NULL; collisionNode = collisionNode.next_sibling("object"))
				{
					std::string collisionPolygonPoints = collisionNode.child("polygon").attribute("points").as_string();
					vector<Vector2> vertices;
					FromStringToVertices(collisionPolygonPoints, mapScale, vertices);

					float x = PIXEL_TO_METERS(collisionNode.attribute("x").as_float()) * mapScale;
					float y = PIXEL_TO_METERS(collisionNode.attribute("y").as_float()) * mapScale;

					PhysBody* body = factory.CreateChain({ x,y }, vertices);
					body->SetType(PhysBody::BodyType::Static);

					uint16 categoryBits = physics->BOUNDARY_LAYER;
					uint16 maskBits = physics->VEHICLE_LAYER | physics->OBSTACLE_LAYER;
					body->SetFilter(0, categoryBits, maskBits, 0);

					trackColliders.emplace_back(body);
				}

			}
			else if (objectGroup_name == "StartingPositions") {
				for (pugi::xml_node startingPosNode = objectGroup_node.child("object"); startingPosNode != NULL; startingPosNode = startingPosNode.next_sibling("object"))
				{

					float x = PIXEL_TO_METERS(startingPosNode.attribute("x").as_float()) * mapScale;
					float y = PIXEL_TO_METERS(startingPosNode.attribute("y").as_float()) * mapScale;

					xml_node order_node = startingPosNode.child("properties").find_child_by_attribute("property", "name", "Order");
					int order = order_node.attribute("value").as_int();

					startingPositions.emplace(startingPositions.begin() + order, Vector2{ x,y });
				}
			}
			else if (objectGroup_name == "CheckPoints") {
				///Create Map Colliders
				for (pugi::xml_node checkPointNode = objectGroup_node.child("object"); checkPointNode != NULL; checkPointNode = checkPointNode.next_sibling("object"))
				{
					std::string collisionPolygonPoints = checkPointNode.child("polygon").attribute("points").as_string();
					vector<Vector2> vertices;
					FromStringToVertices(collisionPolygonPoints, mapScale, vertices);

					float x = PIXEL_TO_METERS(checkPointNode.attribute("x").as_float()) * mapScale;
					float y = PIXEL_TO_METERS(checkPointNode.attribute("y").as_float()) * mapScale;

					xml_node order_node = checkPointNode.child("properties").find_child_by_attribute("property", "name", "Order");
					int order = order_node.attribute("value").as_int();

					MapLapSensor* sensor = new MapLapSensor(moduleAt, { x,y }, vertices, this, order);

					mapLapSensors.emplace_back(sensor);
				}
			}
			else if (objectGroup_name == "TractionAreas") {
				for (pugi::xml_node tractionAreaNode = objectGroup_node.child("object"); tractionAreaNode != NULL; tractionAreaNode = tractionAreaNode.next_sibling("object"))
				{
					std::string collisionPolygonPoints = tractionAreaNode.child("polygon").attribute("points").as_string();
					vector<Vector2> vertices;
					FromStringToVertices(collisionPolygonPoints, mapScale, vertices);

					float x = PIXEL_TO_METERS(tractionAreaNode.attribute("x").as_float()) * mapScale;
					float y = PIXEL_TO_METERS(tractionAreaNode.attribute("y").as_float()) * mapScale;

					xml_node friction_node = tractionAreaNode.child("properties").find_child_by_attribute("property", "name", "Traction");
					float friction = friction_node.attribute("value").as_float();

					vector<vector<Vector2>> newPolys = factory.Triangulate(vertices);

					for (size_t i = 0; i < newPolys.size(); i++)
					{
						PhysBody* body = factory.CreatePolygon({ x,y }, newPolys[i]);

						uint16 categoryBits = physics->FRICTION_AREA_LAYER;
						uint16 maskBits = physics->VEHICLE_WHEEL_LAYER | physics->VEHICLE_SENSOR_LAYER;
						body->SetFilter(0, categoryBits, maskBits, 0);
						body->SetSensor(0,true);
						body->SetType(PhysBody::BodyType::Static);
						body->SetFriction(0, friction);

						trackColliders.emplace_back(body);
					}
				}
			}
			else if (objectGroup_name == "Objects") {
				for (pugi::xml_node objectNode = objectGroup_node.child("object"); objectNode != NULL; objectNode = objectNode.next_sibling("object"))
				{

					float x = PIXEL_TO_METERS(objectNode.attribute("x").as_float()) * mapScale;
					float y = PIXEL_TO_METERS(objectNode.attribute("y").as_float()) * mapScale;

					xml_node type_node = objectNode.child("properties").find_child_by_attribute("property", "name", "Type");
					string objectType = type_node.attribute("value").as_string();

					if (objectType == "cone") {
						trackObstacles.emplace_back(new ConeObstacle(moduleAt, { x,y }));
					}
					else if (objectType == "rock") {
						trackObstacles.emplace_back(new RockObstacle(moduleAt, { x,y }));
					}
					else if (objectType == "fence") {
						trackObstacles.emplace_back(new FenceObstacle(moduleAt, { x,y }));
					}
				}
			}
		}

	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}
}

string RaceTrack::ResolvePath(string basePath, string relativePath)
{
	string baseDir = basePath.substr(0, basePath.find_last_of('/'));

	while (relativePath.substr(0, 3) == "../") {
		baseDir = baseDir.substr(0, baseDir.find_last_of('/'));
		relativePath = relativePath.substr(3);
	}
	return baseDir + '/' + relativePath;
}

void RaceTrack::FromStringToVertices(string stringData, float scale, vector<Vector2>& vector)
{
	stringstream ss(stringData);
	string vectorValue;

	vector.clear();

	while (getline(ss, vectorValue, ' ')) {
		stringstream ss_vectorValue(vectorValue);

		string x_str, y_str;

		getline(ss_vectorValue, x_str, ',');
		getline(ss_vectorValue, y_str);

		float x_poly = stof(x_str);
		float y_poly = stof(y_str);


		vector.push_back({ PIXEL_TO_METERS((x_poly*scale)),PIXEL_TO_METERS((y_poly*scale)) });
	}
}
