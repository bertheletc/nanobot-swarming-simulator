#include "nest.h"

Nest::Nest(int id, int size, float bias, int pilePieces)
{
    _type = EntityType::kNest;
    _visualState = VisualState::kSeen;
    _id = id;
    _sizeRadius = size;
    _bias = bias;
    _timeOn = 0;
    _color = cv::Scalar(0,128,255); // ORANGE (b,g,r)
    _piecesCollected = 0;
    _piecesToCollect = pilePieces;
    _flag = false;
}