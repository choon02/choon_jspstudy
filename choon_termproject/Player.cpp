#include "Player.h"
#include "Game.h"

std::default_random_engine Player::random_engine(time(nullptr));
std::uniform_int_distribution<unsigned int> Player::ability_range(0, 100);
std::uniform_real_distribution<float> Player::possibility(0.f, 1.f);

float PlayerRLGL::fallDownRate = 0.1f;

Player::Player(int number)
{
	this->number = number;

	agility = ability_range(random_engine);
	fearlessness = ability_range(random_engine);
}

Player::Player(int number, int agility, int fearlessness)
{
	this->number = number;
	this->agility = agility;
	this->fearlessness = fearlessness;
}





bool PlayerRLGL::act()
{
	std::uniform_int_distribution<int> random1(0, 10); // for random_distance
	std::uniform_int_distribution<int> random2(0, 100);
	int random_distance = random1(random_engine);
	int fearlessbonus_distance;
	int random_bonus = random2(random_engine);
	int random_number = random2(random_engine);
	if (random_bonus <= fearlessness && random_number <= (int)RedLightGreenLight::fallDownRate * 100) 
		// fearlessness�� Ŭ���� if���� ������ ������ Ȯ�� ����// 25%�� Ȯ�� fallDownRate 1%���� ���� ����
		return false;
	else if(random_bonus <= fearlessness && random_number > (int)RedLightGreenLight::fallDownRate * 100)
	{
		fearlessbonus_distance = agility * (fearlessness * 0.01);
		this->current_distance = agility + random_distance + fearlessbonus_distance;
		Player::total_distance += this->current_distance;
		return true;
	}
	else 
	{
		fearlessbonus_distance = 0;
		this->current_distance = agility + random_distance + fearlessbonus_distance;
		Player::total_distance += this->current_distance;
	}
}

void PlayerRLGL::dyingMessage()
{ 
	if (isPlaying())
	{
		printStatus();
		std::cout << " is still on the ground and died." << std::endl;
	}
		
	else
	{
		printStatus();
		std::cout << " fell down and died." << std::endl;
	}
};
void PlayerRLGL::escapeMessage()
{
		printStatus();
		std::cout << " safely escaped from the ground." << std::endl;
}





bool PlayerRPS::act()
{
	enum rpsType { Rock, Paper, Scissors };
	auto rps = [] {
		float p = possibility(random_engine);

		if (p < float(1.f / 3.f))
			return rpsType::Rock;
		else if (p < float(2.f / 3.f))
			return rpsType::Paper;
		else
			return  rpsType::Scissors;
	};

	rpsType myRPS, yourRPS;
	do {
		myRPS = rps();
		yourRPS = rps();
	}
	while(myRPS == yourRPS);
	
	if (myRPS == Rock)
	{
		if (yourRPS == Paper)
			return false;
		else
			return true;
	}
	else if (myRPS == Paper)
	{
		if (yourRPS == Scissors)
			return false;
		else
			return true;
	}
	else
	{
		if (yourRPS == Rock)
			return false;
		else
			return true;
	}
}


void PlayerRPS::dyingMessage()
{
	printStatus();
	std::cout << " died." << std::endl;
};

bool PlayerSS::act()
{
	std::uniform_int_distribution<int> random(0, 1);
	
	for (int i = 0; i < 5; i++)
	{
		choice[i] = random(random_engine); //���� �����Լ� ����ؾ��� ���� ���ڶ�� �ν��� ������ �ٸ� class�� �� �� ������
		answer[i] = random(random_engine);
	}
	for (int i = 0; i < 5 ; i++)//sizeof(choice) / sizeof(int); i++)
	{
		choice[i] = _choice[i]; //������ ������ ��� ���� ���� �����ϴ� ������ ���� + fearlessness�� 50 �ʰ��̾�� ��
		answer[i] = _answer[i];
	}
	if (agility + fearlessness >= 120) // agility + fearlessness�� 120������ ��� ���� �����ϰų� ������
		return true;
	else 
		return false;
}
void PlayerSS::dyingMessage()
{
	printStatus();
	std::cout << " died." << std::endl;
}