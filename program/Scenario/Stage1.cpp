#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;

Stage1::Stage1() :
	stage1_progress(Stage1Progress::START)
{
}


void Stage1::update() {

	elapsed_time = DxLib::GetNowCount() - kept_clock;

	switch (stage1_progress) {
	case Stage1Progress::START:
		if (elapsed_time > 5000) {//5
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_1;
		}
		break;

	case Stage1Progress::A_LEFT_1:
		if (elapsed_time > 2000) {//7
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_2;
		}
		break;

	case Stage1Progress::A_LEFT_2:
		if (elapsed_time > 2000) {//9
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(-10, 630, 0, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_LEFT_3;
		}
		break;

	case Stage1Progress::A_LEFT_3:
		if (elapsed_time > 4000) {//13
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_1;
		}
		break;

	case Stage1Progress::A_RIGHT_1:
		if (elapsed_time > 2000) {//15
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_2;
		}
		break;

	case Stage1Progress::A_RIGHT_2:
		if (elapsed_time > 2000) {//17
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv1>(630, 630, pi, 100.0));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::A_RIGHT_3;
		}
		break;

	case Stage1Progress::A_RIGHT_3:
		if (elapsed_time > 5000) {//22
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B1;
		}
		break;

	case Stage1Progress::B1:
		if (elapsed_time > 8000) {//30
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(-10, 650, 0, 65, -(1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv2>(630, 400, pi, 65, 1.0 / 6.0 * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::B2;
		}
		break;

	case Stage1Progress::B2:
		if (elapsed_time > 10000) {//40
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(80, 540));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(230, 610));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(390, 610));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3S>(540, 540));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(155, 575, (1.0 / 6.0) * pi));
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv3L>(465, 575, -(1.0 / 6.0) * pi));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::C;
		}
		break;

	case Stage1Progress::C:
		if (elapsed_time > 20000) {//60
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(80, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D1;
		}
		break;

	case Stage1Progress::D1:
		if (elapsed_time > 2000) {//62
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(230, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D2;
		}
		break;

	case Stage1Progress::D2:
		if (elapsed_time > 2000) {//64
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(390, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D3;
		}
		break;

	case Stage1Progress::D3:
		if (elapsed_time > 2000) {//66
			Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv4>(540, 640));
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::D4;
		}
		break;

	case Stage1Progress::D4:
		if (elapsed_time > 8000) {//74
			//Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(135, 480, 1.0 / 8.0 * pi));
			//Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5S>(485, 480, -(1.0 / 8.0) * pi));
			//Field::ENEMY_CHARACTERS->push_back(make_unique<ZkChrStg1Wv5L>(310, 550));
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5S_L) = make_unique<ZkChrStg1Wv5S>(135, 480, 1.0 / 8.0 * pi);
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5S_R) = make_unique<ZkChrStg1Wv5S>(485, 480, -(1.0 / 8.0) * pi);
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5L) = make_unique<ZkChrStg1Wv5L>(310, 550);
			kept_clock = DxLib::GetNowCount();
			stage1_progress = Stage1Progress::E;
		}
	case Stage1Progress::E:
		bool mofu_advent_ready_flag =
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5S_L) == true &&
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5S_R) == true &&
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5L) == true;
		if (mofu_advent_ready_flag == true) {
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::MOFU) = make_unique<Mofu>();
			stage1_progress = Stage1Progress::MOFU;
		}
		if (Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5S_L)->is_dead() == true) {
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5S_L) = true;
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5S_L);
		}
		if (Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5S_R)->is_dead() == true) {
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5S_R) = true;
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5S_R);
		}
		if (Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::ZKCHRSTG1WV5L)->is_dead() == true) {
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::ZKCHRSTG1WV5L) = true;
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::ZKCHRSTG1WV5L);
		}
		break;
	case Stage1Progress::MOFU:
		if (Field::IDENTIFIABLE_ENEMY_CHARACTERS->at(CharacterID::MOFU)->is_dead() == true) {
			Field::IDENTIFIABLE_ENEMY_CHARACTERS_DEAD_FLAGS->at(CharacterID::MOFU) = true;
			Field::IDENTIFIABLE_ENEMY_CHARACTERS->erase(CharacterID::MOFU);
		}
		break;
	}


}