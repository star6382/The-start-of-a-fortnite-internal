#include "unreal_structs.hpp"

// engine library

class ugameplaystatistics : uobject {
public:

	tarray<uobject*> get_all_actors_of_class(uobject* world_context_object, uobject* actor_class) {
		static uobject* function;
		if (!function) function = find_object(L"GameplayStatics.GetAllActorsOfClass");

		struct {
			uobject* world_context_object;
			uobject* actor_class;
			tarray<uobject*> out_actors;
		}

		params = { world_context_object, actor_class };

		process_event(function, &params);
		return params.out_actors;
	}
};



class engine_structure : uobject {
public:

	struct engine_objects {
		static ugameplaystatistics* gameplaystatistics;

		void init(uobject* engine);
	} engine_defines;


public:
	engine_structure() = default;

	engine_structure(const engine_structure& other) {

	}

	engine_structure(engine_structure&& other) noexcept {

	}

	engine_structure& operator=(const engine_structure& other) {
		if (this == &other)
			return *this;
		return *this;
	}

	engine_structure& operator=(engine_structure&& other) noexcept {
		if (this == &other)
			return *this;
		return *this;
	}
};