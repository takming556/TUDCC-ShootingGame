#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const double KurageAmeShot::GRAVITY_CONSTANT = 300;
const unsigned int KurageAmeShot::WAITTIME_UNTIL_MODECHANGE = 700;
const unsigned int KurageAmeShot::COLLIDANT_SIZE = 20;
const unsigned int KurageAmeShot::DURABILITY = 1;
const double KurageAmeShot::DRAW_EXTRATE = 1.0;


KurageAmeShot::KurageAmeShot(double init_pos_x, double init_pos_y) :
	Bullet(2 * pi / 360 * DxLib::GetRand(359), DxLib::GetRand(100) + 150),
	Offensive(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE), DURABILITY),
	mode(KurageAmeShotMode::STRAIGHT),
	generated_clock(DxLib::GetNowCount())
{
}


void KurageAmeShot::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	switch (mode) {
	case KurageAmeShotMode::STRAIGHT:
	{
		int elapsed_time_since_generated = DxLib::GetNowCount() - generated_clock;
		if (elapsed_time_since_generated > WAITTIME_UNTIL_MODECHANGE) {
			arg = -(1.0 / 2.0 * pi);
			speed = 0;
			mode = KurageAmeShotMode::FALL;
		}
		break; 
	}

	case KurageAmeShotMode::FALL:
		speed += update_delta_time * GRAVITY_CONSTANT / 1000 / 1000;
		break;
	}
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;

	collidant->update(position);

	last_updated_clock = DxLib::GetNowHiPerformanceCount();

}


void KurageAmeShot::draw() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0, -arg, ImageHandles::BLUE_MARBLE, TRUE);
	if (DebugParams::DEBUG_FLAG == true) collidant->draw();
}