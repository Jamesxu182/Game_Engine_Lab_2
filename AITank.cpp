#include "AITank.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <glm/gtc/constants.hpp>
#include "Game.h"
#include "Bullet.h"

using namespace Game1;
using namespace std;

AITank::AITank(void) :GameComponent()
{
	position = glm::vec2(540, 380);
	look = glm::vec2(0, -1);
	speed = 50.0f;
	elapsed = 1.0f;
	fireRate = 10.0f;
}

bool AITank::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("tank.bmp");
	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);

	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	center.x = rect.w / 2;
	center.y = rect.h / 2;

	return true;
}


AITank::~AITank(void)
{

}


void AITank::Update(float timeDelta)
{

  player_position = Game::Instance()->player->position;


  if ((position.x < 50) || (position.x > 590) || (position.y < 50) || (position.y > 430))
	{
    glm::vec2 face = (player_position - position) / glm::distance(player_position, position);
    float cos_a = glm::dot(look, face);

    //avoid cos_a greater than 1.

    cout << "cos_a: " << cos_a << endl;

    if(cos_a > 1.0f)
    {
      cos_a = 1.0f;
    }

    else if(cos_a < - 1.0f)
    {
      cos_a = - 1.0f;
    }

    float a = glm::acos(cos_a);

    if((look.x * face.y - look.y * face.x) > 0)
    {
      rotation += a;
    }

    else
    {
      rotation -= a;
    }


    cout <<"a: "<< glm::degrees(a) <<endl;

    look = face;

	}

  position += look * speed * timeDelta;
}

void AITank::Draw()
{
	rect.x = position.x;
	rect.y = position.y;

	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, &rect, glm::degrees(rotation), &center, SDL_FLIP_NONE);
}
