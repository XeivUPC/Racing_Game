#pragma once
#include "MapObject.h"
#include <string>
#include <vector>
#include <raymath.h>

using namespace std;

class PhysBody;
class MapLapSensor;

class RaceTrack : public MapObject
{
public:

	RaceTrack(Module* moduleAt, string trackPath);
	~RaceTrack();
	vector<MapLapSensor*>GetTrackSensors();
	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void LoadTrack();
	string ResolvePath(string basePath, string relativePath);

	void FromStringToVertices(std::string stringData, std::vector<Vector2>& vector);

	string trackPath;

	Texture* trackTexture = nullptr;
	vector<PhysBody*> trackColliders;
	vector<MapLapSensor*> mapLapSensor;





    // Funci�n para calcular el producto cruzado entre dos vectores 2D
    float CrossProduct(const Vector2& v1, const Vector2& v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    // Funci�n para verificar si un punto est� dentro de un tri�ngulo
    bool IsPointInTriangle(const Vector2& p, const Vector2& p0, const Vector2& p1, const Vector2& p2) {
        float c1 = CrossProduct(Vector2Subtract(p1, p0), Vector2Subtract(p, p0));
        float c2 = CrossProduct(Vector2Subtract(p2, p1), Vector2Subtract(p, p1));
        float c3 = CrossProduct(Vector2Subtract(p0, p2), Vector2Subtract(p, p2));

        return (c1 >= 0 && c2 >= 0 && c3 >= 0) || (c1 <= 0 && c2 <= 0 && c3 <= 0);
    }
    // Funci�n que encuentra un "ear" (un tri�ngulo v�lido)
    bool IsEar(const std::vector<Vector2>& polygon, int i, int j, int k) {
        Vector2 p0 = polygon[i];
        Vector2 p1 = polygon[j];
        Vector2 p2 = polygon[k];

        // Comprobar si el tri�ngulo es convexo
        if (CrossProduct(Vector2Subtract(p1, p0), Vector2Subtract(p2, p0)) < 0) {
            return false; // Si el tri�ngulo es c�ncavo, no es un "ear"
        }

        // Comprobar que no haya otros puntos dentro del tri�ngulo
        for (size_t m = 0; m < polygon.size(); m++) {
            if (m != i && m != j && m != k) {
                if (IsPointInTriangle(polygon[m], p0, p1, p2)) {
                    return false;
                }
            }
        }

        return true;
    }

    // Algoritmo de Ear Clipping para dividir el pol�gono en tri�ngulos
    std::vector<std::vector<Vector2>> Triangulate(const std::vector<Vector2>& polygon) {
        std::vector<std::vector<Vector2>> triangles;
        std::vector<Vector2> tempPolygon = polygon;

        while (tempPolygon.size() > 3) {
            bool earFound = false;

            // Buscar una "oreja" (un tri�ngulo v�lido)
            for (size_t i = 0; i < tempPolygon.size(); i++) {
                int prev = (i == 0) ? tempPolygon.size() - 1 : i - 1;
                int next = (i == tempPolygon.size() - 1) ? 0 : i + 1;

                if (IsEar(tempPolygon, prev, i, next)) {
                    triangles.push_back({ tempPolygon[prev], tempPolygon[i], tempPolygon[next] });
                    tempPolygon.erase(tempPolygon.begin() + i); // Eliminar el v�rtice de la oreja
                    earFound = true;
                    break;
                }
            }

            // Si no se encuentra ninguna oreja, el pol�gono no es simple
            if (!earFound) {
                 printf("Error: No se pudo dividir el pol�gono en tri�ngulos");
                break;
            }
        }

        // Agregar el �ltimo tri�ngulo
        if (tempPolygon.size() == 3) {
            triangles.push_back({ tempPolygon[0], tempPolygon[1], tempPolygon[2] });
        }

        return triangles;
    }


};