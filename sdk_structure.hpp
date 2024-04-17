#include "engine_library.hpp"

struct UCanvas : uobject {
public:
	//__forceinline void ADrawText(Vector2 ScreenPosition, FString RenderText, FLinearColor RenderColor, bool centered, bool bOutlined)
	//{
	//	struct textparams
	//	{
	//		UObject* RenderFont;
	//		FString RenderText;
	//		Vector2 ScreenPosition;
	//		Vector2 Scale;
	//		FLinearColor RenderColor;
	//		double Kerning;
	//		FLinearColor ShadowColor;
	//		Vector2 ShadowOffset;
	//		bool bCentreX;
	//		bool bCentreY;
	//		bool bOutlined;
	//		FLinearColor OutlineColor;
	//	};
	//	static uintptr_t fn = NULL;
	//	static uintptr_t font = NULL;
	//	static bool setonce = false;
	//	if (!setonce)
	//	{
	//		fn = UObject::FindObject(("Function Engine.Canvas.K2_DrawText"));
	//		font = UObject::FindObject(("Font Roboto.Roboto"));
	//		setonce = true;
	//	}
	//	textparams params;
	//	params.RenderFont = (UObject*)font;
	//	params.RenderText = RenderText;
	//	params.ScreenPosition = ScreenPosition;
	//	params.Scale = Vector2{ 1.f, 1.f };
	//	params.RenderColor = RenderColor;
	//	params.Kerning = false;
	//	params.ShadowColor = FLinearColor{ 0.0f, 0.0f, 0.0f, 0.0f };
	//	params.ShadowOffset = ScreenPosition;
	//	if (centered) { params.bCentreX = true; params.bCentreY = true; }
	//	else { params.bCentreX = false; params.bCentreY = false; }
	//	params.bOutlined = bOutlined;
	//	params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };
	//	UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
	//}
	// 
	//void text(UCanvas* canvas, FString content, Vector2 location, FLinearColor color, bool center, bool outline)
	//{
	//	canvas->ADrawText(location, content, color, false, false);
	//}

	auto DrawLine(fvector2d a, fvector2d b, float thickness, flinearcolor rendercolor) -> void {
		uobject* obj = static_find_object(nullptr, nullptr, L"Function Engine.Canvas.K2_DrawLine");	

		struct {
			fvector2d a, b;
			float thickness;
			flinearcolor rendercolor;
		} params = { a, b, thickness, rendercolor };

		process_event(obj, &params);
	}

	__forceinline fvector2d SZE() const {
		return { ScreenX, ScreenY };
	};

private:
	uint8_t Padding_0[0x40];
	double ScreenX;
	double ScreenY;

};

struct SkeletonMeshComponet {
public:
	


};

struct AFortPawn {
public:
	/*ARootComponent* RootComponent()
	{
		return (ARootComponent*)*(uint64_t*)(this + 0x190);
	}
	uint64_t Mesh()
	{
		return *(uint64_t*)(this + 0x310);
	}
	Vector3 GetBoneLocation(int Id)
	{
		auto mesh = Mesh();
		if (!mesh) return { 0, 0, 0 };
		auto function = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(GetBoneMatrix));
		function(mesh, mMatrix, Id);
		return { mMatrix->M[3][0], mMatrix->M[3][1], mMatrix->M[3][2] };
	}*/
};

struct APlayerController {
public:
	//AFortPawn* AcknowledgedPawn()
	//{
	//	return (AFortPawn*)*(uintptr_t*)(this + 0x330);
	//}
	// 
	//bool w2s(Vector3 world, Vector2* screen)
	//{
	//	static uintptr_t fn = NULL;

	//	if (!fn)
	//	{
	//		fn = UObject::FindObject(("Function Engine.PlayerController.ProjectWorldLocationToScreen"));
	//	}

	//	struct
	//	{
	//		Vector3 world;
	//		Vector2 screen;
	//		bool relative_viewport;
	//		bool return_value;
	//	}
	//	params = { world, Vector2(), true };
	//	UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
	//	*screen = params.screen;
	//	return params.return_value;
	//}
	//bool IsInputKeyDown(const struct FKey& Key)
	//{
	//	static uintptr_t fn = NULL;
	//	if (!fn)
	//		fn = UObject::FindObject(("Function Engine.PlayerController.IsInputKeyDown"));
	//	struct keystruct
	//	{
	//		struct FKey Key;
	//		bool ReturnValue;
	//	};
	//	keystruct params;
	//	params.Key = Key;
	//	UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);
	//	return params.ReturnValue;
	//}

};

class UGameViewportClient {

public:
};

class ULocalPlayer {
public:

	APlayerController* PlayerController()
	{
		if (!this) return 0;
		return (APlayerController*)(*(uintptr_t*)(this + 0x30));
	}

	UGameViewportClient* ViewPortClient()
	{
		if (!this) return 0;
		return (UGameViewportClient*)(*(uintptr_t*)(this + 0x78));
	}

};

class ULocalPlayers {
public:

	ULocalPlayer* LocalPlayer()
	{
		if (!this) return 0;
		return (ULocalPlayer*)(*(uintptr_t*)(this));
	}

};

class UGameInstance {
public:

	ULocalPlayers* LocalPlayers()
	{
		if (!this) return 0;
		return (ULocalPlayers*)(*(uintptr_t*)(this + 0x38));
	}

};

struct UWorld {
public:


	UGameInstance* GameInstance()
	{
		return (UGameInstance*)*(uintptr_t*)(this + 0x1B8);
	}

};


class player_structure {
public:


	struct local_player_data {
		ULocalPlayer* player = nullptr;
		APlayerController* controller = nullptr;
		bool ensure();
		bool update();
	} lp;

	struct world_structure {
		UWorld* gworld = nullptr;
		bool invalid_check = false;
		bool world();
	} _world;



public:
	player_structure() = default;

	player_structure(const player_structure& other) {

	}

	player_structure(player_structure&& other) noexcept {

	}

	player_structure& operator=(const player_structure& other) {
		if (this == &other)
			return *this;
		return *this;
	}

	player_structure& operator=(player_structure&& other) noexcept {
		if (this == &other)
			return *this;
		return *this;
	}
};