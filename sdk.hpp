#include "sdk_structure.hpp"
#include "engine_library.hpp"

bool player_structure::local_player_data::ensure() {





    return false;
}

inline bool player_structure::local_player_data::update() {





    return false;
}

void engine_structure::engine_objects::init(uobject* engine) {
    engine_structure::engine_objects::gameplaystatistics = reinterpret_cast<ugameplaystatistics*>(engine->find_object(L"Engine.GameplayStatics"));


}


bool player_structure::world_structure::world() {
    gworld = (UWorld*)uintptr_t(game_address + 0x000000);
    if (!gworld) {
        return invalid_check = false;
    }

    auto Game = gworld->GameInstance();
    if (!Game) {
        return invalid_check = false;
    }

    auto LocalPlayers = Game->LocalPlayers();
    auto LocalPlayer = LocalPlayers->LocalPlayer();
    if (!LocalPlayer) {
        return invalid_check = false;
    }

    auto Controller = LocalPlayer->PlayerController();
    if (!Controller) {
        return invalid_check = false;
    }

    auto Viewport = LocalPlayer->ViewPortClient();
    if (!Viewport) {
        return invalid_check = false;
    }

    return invalid_check = true;
}
