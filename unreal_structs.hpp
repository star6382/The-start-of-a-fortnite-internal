#include "win_api.hpp"

uint64_t game_address;
uintptr_t staticfindobject_address = 0x14557B0;
//uintptr_t processevent_address = 0x1B8492C;
uintptr_t vft_processevent_address = 0x4D;


template <class type>
struct tarray {
public:
	tarray() { this->data = nullptr; this->count = this->max = 0; };

	type* data;
	int32_t count, max;

	type& operator[](int i) {
		return this->data[i];
	};

	int size() {
		return this->count;
	}

	bool valid(int i) {
		return bool(i < this->count);
	}
};

struct fstring : private tarray<wchar_t> {
	fstring() { };
	fstring(const wchar_t* other) {
		this->max = this->count = *other ? static_cast<int>(windows.wcslen(other)) + 1 : 0;

		if (this->count)
			this->data = const_cast<wchar_t*>(other);
	};

	wchar_t* c_str() const {
		return this->data;
	}

	bool valid() const {
		return this->data != nullptr;
	}
};


struct fvector {
	fvector() : x(), y(), z() { }
	fvector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }

	double x, y, z;

	__forceinline bool null_check() const {
		return (!x && !y && !z);
	}

	operator bool() { return bool(this->x && this->y && this->z); }
	bool operator==(fvector in) { return bool(this->x == in.x && this->y == in.y && this->z == in.z); }
	fvector operator+(fvector in) { return fvector(this->x + in.x, this->y + in.y, this->z + in.z); }
	fvector operator-(fvector in) { return fvector(this->x - in.x, this->y - in.y, this->z - in.z); }
};

struct fvector2d {
	fvector2d() : x(), y() { }
	fvector2d(double _x, double _y) : x(_x), y(_y) { }

	double x, y;

	operator bool() { return bool(this->x && this->y); }
	bool operator==(fvector2d in) { return bool(this->x == in.x && this->y == in.y); }
	fvector2d operator+(fvector2d in) { return fvector2d(this->x + in.x, this->y + in.y); }
	fvector2d operator-(fvector2d in) { return fvector2d(this->x - in.x, this->y - in.y); }
};

struct frotator {
	frotator() : pitch(), yaw(), roll() { }
	frotator(double _pitch, double _yaw, double _roll) : pitch(_pitch), yaw(_yaw), roll(_roll) { }

	double pitch, yaw, roll;

	operator bool() { return bool(this->pitch && this->yaw); }
	bool operator==(frotator in) { return bool(this->pitch == in.pitch && this->yaw == in.yaw && this->roll == in.roll); }
	frotator operator+(frotator in) { return frotator(this->pitch + in.pitch, this->yaw + in.yaw, this->roll + in.roll); }
	frotator operator-(frotator in) { return frotator(this->pitch - in.pitch, this->yaw - in.yaw, this->roll - in.roll); }
};

struct flinearcolor {
	flinearcolor() : r(), g(), b(), a() { }
	flinearcolor(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) { }

	float r, g, b, a;

	operator bool() { return bool(this->r || this->g || this->b || this->a); }
	bool operator==(flinearcolor in) { return bool(this->r == in.r && this->g == in.g && this->b == in.b && this->a == in.a); }
};


//flinearcolor rgb_to_flinear(const int r, const int g, const int b) {
//	return { static_cast<float>(r) / 255.0f,static_cast<float>(g) / 255.0f,static_cast<float>(b) / 255.0f ,1.0f };
//}

//flinearcolor hex_to_flinear(const std::string& hex) {
//	if (hex.size() != 7 || hex[0] != '#') {
//		return { 0,0,0,1 };
//	}
//
//	int r, g, b;
//	std::sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
//	return { static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f, 1.0f };
//}


struct fminimalviewinfo {
	fvector location;
	frotator rotation;
	float fov;
};

struct fname {
	fname() : index() { }
	fname(uint32_t _index) : index(_index) { }

	uint32_t index;
};

struct fkey {
	fname name;
	std::uint8_t details[20];
};

class uobject {
public:

	static uobject* find_object(const wchar_t* name, uobject* outer = nullptr) {
		return reinterpret_cast<uobject*>(uobject::static_find_object(nullptr, outer, name));
	}

	static uobject* static_find_object(uobject* klass, uobject* outer, const wchar_t* name) {
		return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*)>(game_address + staticfindobject_address)(klass, outer, name);
	}

	//static uobject* static_find_object(uobject* klass, uobject* outer, const wchar_t* name, bool exact) {
	//	return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*, bool)>(game_address + staticfindobject_address)(klass, outer, name, exact);
	//}

	void process_event(uobject* function, void* args) {
		auto vtable = *reinterpret_cast<void***>(this);
		reinterpret_cast<void(*)(void*, void*, void*)>(vtable[vft_processevent_address])(this, function, args);
	}

};