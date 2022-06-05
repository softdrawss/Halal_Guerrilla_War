#ifndef __MODULE_POWERUP_H__
#define __MODULE_POWERUP_H__

#include "Module.h"


#define MAX_POWERUPS 100

//same structure than in ModuleEnemies, falta editar

enum class PowerUp_Type
{
	NO_TYPE,
	PRISONER,
	WEAPON
};

struct PowerUpSpawnpoint
{
	PowerUp_Type type = PowerUp_Type::NO_TYPE;
	int x, y;
};


class PowerUp;
struct SDL_Texture;

class ModulePowerUp : public Module
{
public:
	// Constructor
	ModulePowerUp(bool startEnabled);

	// Destructor
	~ModulePowerUp();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddPowerUp(PowerUp_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandlePowerUpSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandlePowerUpDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnPowerUp(const PowerUpSpawnpoint& info);


private:
	// A queue with all spawn points information
	PowerUpSpawnpoint spawnQueue[MAX_POWERUPS];

	// All spawned enemies in the scene
	PowerUp* powerups[MAX_POWERUPS] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texturePRISONER = nullptr;
	SDL_Texture* textureWEAPON = nullptr;
	

	// The audio fx for destroying an enemy
	int powerUpsound = 0;
};

#endif // __MODULE_POWERUP_H__