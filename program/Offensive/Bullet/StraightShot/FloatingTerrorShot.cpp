#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


const unsigned int FloatingTerrorShot::MODE_SWITCH_Y = 690;
const double FloatingTerrorShot::FLOATING_SPEED = 70;
const double FloatingTerrorShot::TERROR_SPEED = 350;
const unsigned int FloatingTerrorShot::COLLIDANT_SIZE = 10;
const unsigned int FloatingTerrorShot::DURABILITY = 1;



FloatingTerrorShot::FloatingTerrorShot(
	double init_pos_x,
	double init_pos_y
) :
	Bullet(1.0 / 2.0 * pi, FLOATING_SPEED),
	Offensive(init_pos_x, init_pos_y, make_unique<CollideCircle>(init_pos_x, init_pos_y, COLLIDANT_SIZE), DURABILITY),
	StraightShot(SkinID::NORMAL_BLUE),
	status(FloatingTerrorShotMode::FLOATING)
{
}


void FloatingTerrorShot::update() {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);

	if (status == FloatingTerrorShotMode::FLOATING) {
		if (position->y > MODE_SWITCH_Y) {
			InFieldPosition my_chr_pos = *(Field::MY_CHARACTER->position);
			double delta_x_mychr = my_chr_pos.x - position->x;
			double delta_y_mychr = my_chr_pos.y - position->y;
			double arg_toward_mychr = atan2(delta_y_mychr, delta_x_mychr);
			arg = arg_toward_mychr;
			status = FloatingTerrorShotMode::TERROR;
			skin_id = SkinID::KUNAI_RED;
			speed = TERROR_SPEED;
			DxLib::PlaySoundMem(SoundHandles::ENEMYSHOT, DX_PLAYTYPE_BACK);
		}
	}
}