#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"
#include "extern.h"

using std::make_unique;
using std::sin;
using std::cos;

template<class T>
const double StraightShot<T>::DEFAULT_ARG = 0.0;

template<class T>
const double StraightShot<T>::DEFAULT_SPEED = 150.0;

template<class T>
StraightShot<T>::StraightShot(double init_x, double init_y, double init_arg, double init_speed) :
	Bullet(init_x, init_y),
	Offensive(1, make_unique<CollideCircle>(init_x, init_y, COLLIDANT_SIZE)),
	speed(init_speed),
	arg(init_arg)
{
	//collidant.reset(new CollideCircle(init_x, init_y, COLLIDANT_SIZE));
}


template<class T>
void StraightShot<T>::update() {

	LONGLONG delta_time = DxLib::GetNowHiPerformanceCount() - clock_keeper_for_update;
	double distance = speed * delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	center_pos->x += distance_x;
	center_pos->y += distance_y;
	clock_keeper_for_update = DxLib::GetNowHiPerformanceCount();

	collidant->update(center_pos);
}


//void StraightShot::draw() {
//	Position draw_pos = center_pos->get_draw_position();
//	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 0.1, 0, ImageHandles::HEART, TRUE);
//	collidant->draw();
//}