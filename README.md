# UE5 FPS Game Demo

This project contains the C++ source code for a First Person Shooter demo in Unreal Engine 5.

## Project Structure
- **Source/MyFPSGame**: Contains the C++ classes.
  - `MyFPSCharacter`: Player character with Health, Shooting (Server RPC), and Damage handling.
  - `FPSEnemyCharacter`: Enemy character with AI support, Health, and Attack logic.
  - `FPSEnemyController`: AI Controller that chases the nearest player.
  - `MyFPSGameMode`: Manages game rules, scoring, and win conditions.
  - `MyFPSProjectile`: Projectile logic.

## Setup Instructions

Since this is a C++ project, you need to compile it.

1.  **Generate Project Files**:
    - Right-click `MyFPSGame.uproject` and select **Generate Visual Studio project files**.
2.  **Compile**:
    - Open the generated `.sln` file in Visual Studio.
    - Build the solution (Development Editor configuration).
3.  **Open Unreal Engine**:
    - Open `MyFPSGame.uproject`.

## Blueprint Setup

To use the C++ classes, you should create Blueprints that inherit from them:

1.  **Game Mode**:
    - Create a Blueprint class inheriting from `MyFPSGameMode` (e.g., `BP_MyGameMode`).
    - Set `ScoreToWin` in the Details panel (default is 5).
    - Assign `BP_MyGameMode` as the default GameMode in **Project Settings -> Maps & Modes**.

2.  **Player Character**:
    - Create a Blueprint inheriting from `MyFPSCharacter` (e.g., `BP_Player`).
    - Add a Skeletal Mesh (Arms) to the `Mesh1P` component.
    - Set up the **Enhanced Input** actions in the Event Graph (Assign Mapping Context).
    - Set `BP_Player` as the **Default Pawn Class** in your GameMode.

3.  **Enemy Character**:
    - Create a Blueprint inheriting from `FPSEnemyCharacter` (e.g., `BP_Enemy`).
    - Add a Skeletal Mesh (e.g., Mannequin).
    - Place `BP_Enemy` instances in the level.

## Features

- **Combat**: Players can shoot enemies. Enemies chase and attack players.
- **Health System**: Both players and enemies have health. Replicated over network.
- **Scoring**: Killing an enemy grants 1 point. Reaching the target score wins the game (Restarts).
- **Multiplayer**: Supports network replication. Test by setting "Number of Players" to 2 and Net Mode to "Play as Listen Server".
