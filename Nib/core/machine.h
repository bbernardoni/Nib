#pragma once

#include <functional>

class Machine {
public:
	Machine(void* object): obj(object) {
		enterFunc = nullptr;
		updateFunc = nullptr;
		exitFunc = nullptr;
	}
	virtual ~Machine(){}

	template <class T>
	void setState(void (T::*newState)()){
		if(newState == nullptr) return;
		if(exitFunc) exitFunc();
		enterFunc = nullptr;
		updateFunc = std::bind(newState, static_cast<T*>(obj));
		exitFunc = nullptr;
	}

	template <class T>
	void setState(void (T::*newState)(), void (T::*enterState)(), void (T::*exitState)()){
		if(newState == nullptr) return;
		if(exitFunc) exitFunc();
		enterFunc = std::bind(enterState, static_cast<T*>(obj));
		updateFunc = std::bind(newState, static_cast<T*>(obj));
		exitFunc = std::bind(exitState, static_cast<T*>(obj));
		if(enterFunc) enterFunc();
	}

	void updateState(){ if(updateFunc) updateFunc(); }

protected:
	void* obj;
	std::function<void()> enterFunc;
	std::function<void()> updateFunc;
	std::function<void()> exitFunc;
};
