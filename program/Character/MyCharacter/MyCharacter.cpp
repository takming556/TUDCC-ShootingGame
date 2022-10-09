#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include "DxLib.h"
#include "class.h"

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::sin;
using std::cos;


const double MyCharacter::SLOW_MOVE_SPEED_EXTRATE = 0.5;


MyCharacter::MyCharacter(string character_name) :
	name(character_name),
	life(100),
	shot_frequency(10.0),
	move_speed(300.0),
	last_launch_ticked_clock(DxLib::GetNowCount()),
	last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
}


void MyCharacter::update() {
	respond_to_keyinput();
	collidant->update(position);
	last_updated_clock = DxLib::GetNowHiPerformanceCount();
}


void MyCharacter::respond_to_keyinput() {

	//Zキー
	if (KeyPushFlags::Z == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していなかったが、押し始めた瞬間
		KeyPushFlags::Z = true;
		launch();
		last_launch_ticked_clock = DxLib::GetNowCount();
	}
	if (KeyPushFlags::Z == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 0) {	//Zキーを今まで押していたが、離した瞬間
		KeyPushFlags::Z = false;
	}
	if (KeyPushFlags::Z == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {	//Zキーを今まで押していたし、今も押している
		int launch_wait = 1.0 / shot_frequency * 1000;
		if (DxLib::GetNowCount() > last_launch_ticked_clock + launch_wait) {
			launch();
			last_launch_ticked_clock = DxLib::GetNowCount();
		}
	}


	//Xキー
	if (KeyPushFlags::X == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 1) {
		KeyPushFlags::X = true;
	}
	if (KeyPushFlags::X == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_X] == 0) {
		KeyPushFlags::X = false;
	}


	if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_UP] == 1) {
		if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_uprightward(true);
			}
			else {
				move_uprightward();
			}
		}
		else if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_upleftward(true);
			}
			else {
				move_upleftward();
			}
		}
		else {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_upward(true);
			}
			else {
				move_upward();
			}
		}
	}
	else if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_DOWN] == 1) {
		if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_downrightward(true);
			}
			else {
				move_downrightward();
			}
		}
		else if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_downleftward(true);
			}
			else {
				move_downleftward();
			}
		}
		else {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_downward(true);
			}
			else {
				move_downward();
			}
		}
	}
	else {
		if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_RIGHT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_rightward(true);
			}
			else {
				move_rightward();
			}
		}
		else if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LEFT] == 1) {
			if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_LSHIFT] == 1) {
				move_leftward(true);
			}
			else {
				move_leftward();
			}
		}
	}

}


void MyCharacter::move_upward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->y += distance;
}


void MyCharacter::move_downward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->y -= distance;
}


void MyCharacter::move_rightward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->x += distance;
}


void MyCharacter::move_leftward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	position->x -= distance;
}


void MyCharacter::move_uprightward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(1.0 / 4.0 * pi);
	double distance_y = distance * sin(1.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_downrightward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(1.0 / 4.0) * pi);
	double distance_y = distance * sin(-(1.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_upleftward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(3.0 / 4.0 * pi);
	double distance_y = distance * sin(3.0 / 4.0 * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::move_downleftward(bool slow_flag) {
	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance;
	if (slow_flag == true) {
		distance = move_speed * SLOW_MOVE_SPEED_EXTRATE * update_delta_time / 1000 / 1000;
	}
	else {
		distance = move_speed * update_delta_time / 1000 / 1000;
	}
	double distance_x = distance * cos(-(3.0 / 4.0) * pi);
	double distance_y = distance * sin(-(3.0 / 4.0) * pi);
	position->x += distance_x;
	position->y += distance_y;
}


void MyCharacter::launch() {
	unique_ptr<Offensive> straight_shot = make_unique<StraightShot>(position->x, position->y + 30.0, pi / 2, 2000, 20, 1, SkinID::ICHIGO_CHAN);
	Field::MY_OFFENSIVES->push_back(move(straight_shot));
}


void MyCharacter::damaged() {
	life += -1;
}


void MyCharacter::draw_life() {
	Position draw_pos = position->get_draw_position();
	DxLib::DrawFormatString(draw_pos.x, draw_pos.y, Colors::BLUE, "%d", life);
}


bool MyCharacter::is_collided_with_enemy_offensives() {
	bool collided_with_no_less_than_one_enemy_offensive_flag = false;
	for (const auto& enemy_offensive : *Field::ENEMY_OFFENSIVES) {
		if (collidant->is_collided_with(enemy_offensive->collidant)) collided_with_no_less_than_one_enemy_offensive_flag = true;
	}
	return collided_with_no_less_than_one_enemy_offensive_flag;
}