#pragma once
#include "GameComponent.h"
#include <list>
#include<memory>
#include <SDL2/SDL.h>
#include "Player.h"
#include "AITank.h"

using namespace std;

namespace Game1
{
	class Game :public GameComponent
	{
	public:
		Game(void);
		~Game(void);

		list<shared_ptr<GameComponent>> children;

		shared_ptr<Player> player;
		shared_ptr<AITank> enemy;

		static Game * instance;
		static Game * Instance();

		// SDL Stuff
		SDL_Renderer * renderer;
		bool running;

		bool Initialise();
		bool InitialiseSDL();
		void Update(float timeDelta);
		void Draw();
		void Cleanup();
		void Start();

	};
}
