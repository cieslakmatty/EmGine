#pragma once

const int TILE_WIDTH = 64;
const float TILE_RADIUS = TILE_WIDTH / 2;

const int AGENT_WIDTH = 64;
const float AGENT_RADIUS = AGENT_WIDTH / 2;

const int BULLET_RADIUS = 5;

const float MIN_WALL_COLLISION_DISTANCE = AGENT_RADIUS + TILE_RADIUS;
const float MIN_AGENT_COLLISION_DISTANCE = AGENT_RADIUS * 2;
const float MIN_AGENT_BULLET_COLLISION_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

const float HUMAN_SPEED = 5.0f;
const float HUMAN_HEALTH = 40.0f;

const float ZOMBIE_SPEED = 3.0f;
const float ZOMBIE_HEALTH = 200.0f;

const float PLAYER_SPEED = 14.0f;

//pistol
const int PISTOL_BULLET_SPEED = 30;
const int PISTOL_FIRERATE = 10;
const int PISTOL_BULLETS_PER_SHOT = 1;
const float PISTOL_SPREAD = 10.0f;
const float PISTOL_DAMAGE = 30.0f;
//shotgun
const int SHOTGUN_BULLET_SPEED = 30;
const int SHOTGUN_FIRERATE = 20;
const int SHOTGUN_BULLETS_PER_SHOT = 40;
const float SHOTGUN_SPREAD = 10.0f;
const float SHOTGUN_DAMAGE = 2.0f;
//machinegun
const int MACHINEGUN_BULLET_SPEED = 30;
const int MACHINEGUN_FIRERATE = 1;
const int MACHINEGUN_BULLETS_PER_SHOT = 1;
const float MACHINGUN_SPREAD = 15.0f;
const float MACHINEGUN_DAMAGE = 10.0f;