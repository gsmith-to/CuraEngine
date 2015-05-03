/** Copyright (C) 2013 David Braam - Released under terms of the AGPLv3 License */
#ifndef SUPPORT_H
#define SUPPORT_H

#include "sliceDataStorage.h"
#include "modelFile/modelFile.h"

namespace cura {

class AreaSupport {
public:

    /*!
     * Joins the layerpart outlines of all meshes and collects the overhang points (small areas).
     * \param storage input layer outline information
     * \param overhang_points stores overhang_points along with the layer index at which the overhang point occurs
     * \param layer_count total number of layers
     * \param supportMinAreaSqrt diameter of the minimal area which can be supported without a specialized strut
     * \param extrusionWidth extrusionWidth
     */
    static void joinMeshesAndDetectOverhangPoints(
        SliceDataStorage& storage,
        std::vector<Polygons>& joinedLayers,
        std::vector<std::pair<int, std::vector<Polygons>>>& overhang_points, 
        int layer_count,
        int supportMinAreaSqrt,
        int extrusionWidth
    );
    
    /*!
     * Adds tower pieces to the current support layer.
     * From below the roof, the towers are added to the normal support layer and handled as normal support area.
     * \param supportLayer_this The support areas in the layer for which we are creating towers/struts
     * \param towerRoofs The parts of roofs which need to expand downward until they have the required diameter
     * \param overhang_points stores overhang_points along with the layer index at which the overhang point occurs
     * \param overhang_points_pos Index into \p overhang_points for the overhang points in the next layer
     * \param layer_idx The index of the layer at which to handle towers
     * \param towerRoofExpansionDistance The offset distance which determines the angle of the tower roof tops
     * \param supportTowerDiameter The diameter of the eventual tower, below the roof
     * \param supportMinAreaSqrt diameter of the minimal area which can be supported without a specialized strut
     * \param layer_count total number of layers
     * \param z_layer_distance_tower The number of layers between an overhang point and the top of a support tower
     */
    static void handleTowers(
        Polygons& supportLayer_this,
        std::vector<Polygons>& towerRoofs,
        std::vector<std::pair<int, std::vector<Polygons>>>& overhang_points,
        int& overhang_points_pos,
        int layer_idx,
        int towerRoofExpansionDistance,
        int supportTowerDiameter,
        int supportMinAreaSqrt,
        int layer_count,
        int z_layer_distance_tower
    );
    
    /*!
     * Adds struts (towers against a wall) to the current layer.
     * \param supportLayer_this The areas of the layer for which to handle the wall struts.
     * \param supportMinAreaSqrt The minimal diameter of a wall which doesn't need a strut for reinforcement
     * \param suportTowerDiameter The diameter of the strut
     */
    static void handleWallStruts(
        Polygons& supportLayer_this,
        int supportMinAreaSqrt,
        int supportTowerDiameter
    );
};

        
/*!
* Generate support polygons over all layers.
* 
* This function also handles small overhang areas (creates towers with larger diameter than just the overhang area) and single walls which could otherwise fall over.
* 
* \param storage data storage containing the input layer outline data and containing the output support storage per layer
* \param object The object for which to generate support areas
* \param layer_count total number of layers
*/
void generateSupportAreas(SliceDataStorage& storage, SliceMeshStorage* object, int layer_count);


}//namespace cura

#endif//SUPPORT_H
