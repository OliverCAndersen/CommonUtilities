#include "InputManager.h"
#include <windows.h>

namespace CommonUtilities
{
	InputManager::InputManager()
	{

	}
	InputManager::~InputManager()
	{
	}

	void InputManager::Update()
	{
		myPreviousState = myCurrentState;
		UpdateCursorPosition();
	}

	void InputManager::UpdateCursorPosition()
	{
		myCursorPositionOnScreenLastUpdate = myCursorPositionOnScreen;
		POINT winCursorPosition;
		GetCursorPos(&winCursorPosition);
		myCursorPositionOnScreen.Set(static_cast<float>(winCursorPosition.x), static_cast<float>(winCursorPosition.y));
	}
	void InputManager::SetCursorPositionOnScreen(int aX, int aY)
	{
		SetCursorPos(aX, aY);
	}

	Vector2f InputManager::GetCursorPositionOnScreen() const
	{
		return myCursorPositionOnScreen;
	}
	Vector2f InputManager::GetCursorPositionOnScreenLastUpdate() const
	{
		return myCursorPositionOnScreenLastUpdate;
	}

	short InputManager::GetWheelDeltaSinceLastFrame() const
	{
		return myWheelDeltaSinceLastFrame;
	}

	bool InputManager::IsMouseButtonClicked(MouseButton aButtonToCompareWith) const
	{
		if (myPreviousState.myVirtualKeys[static_cast<int>(aButtonToCompareWith)] == false && myCurrentState.myVirtualKeys[static_cast<int>(aButtonToCompareWith)] == true)
		{
			return true;
		}
		return false;
	}
	bool InputManager::IsMouseButtonDown(MouseButton aButtonToCompareWith) const
	{
		if (myCurrentState.myVirtualKeys[static_cast<int>(aButtonToCompareWith)] == true)
		{
			return true;
		}
		return false;
	}
	bool InputManager::IsMouseButtonReleased(MouseButton aButtonToCompareWith) const
	{
		if (myPreviousState.myVirtualKeys[static_cast<int>(aButtonToCompareWith)] == true && myCurrentState.myVirtualKeys[static_cast<int>(aButtonToCompareWith)] == false)
		{
			return true;
		}
		return false;
	}

	void InputManager::HandleInput(unsigned int message, unsigned int aVirtualKeyIndex)
	{
		switch (message)
		{
			case WM_KEYDOWN:
				myCurrentState.myVirtualKeys[aVirtualKeyIndex] = true;
				break;
			case WM_KEYUP:
				myCurrentState.myVirtualKeys[aVirtualKeyIndex] = false;
				break;
			case WM_LBUTTONDOWN:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Left)] = true;
				break;
			case WM_LBUTTONUP:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Left)] = false;
				break;
			case WM_RBUTTONDOWN:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Right)] = true;
				break;
			case WM_RBUTTONUP:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Right)] = false;
				break;
			case WM_MBUTTONDOWN:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Middle)] = true;
				break;
			case WM_MBUTTONUP:
				myCurrentState.myVirtualKeys[static_cast<int>(MouseButton::Middle)] = false;
				break;
			case WM_MOUSEWHEEL:
				myWheelDeltaSinceLastFrame = GET_WHEEL_DELTA_WPARAM(aVirtualKeyIndex) / WHEEL_DELTA;
				break;
			default:
				break;
		}
	}

	bool InputManager::IsKeyPressed(KeyCode aKeyToCompareWith) const
	{
		if (myPreviousState.myVirtualKeys[static_cast<int>(aKeyToCompareWith)] == false && myCurrentState.myVirtualKeys[static_cast<int>(aKeyToCompareWith)] == true)
		{
			return true;
		}
		return false;
	}
	bool InputManager::IsKeyDown(KeyCode aKeyToCompareWith) const
	{
		if (myCurrentState.myVirtualKeys[static_cast<int>(aKeyToCompareWith)] == true)
		{
			return true;
		}
		return false;
	}
	bool InputManager::IsKeyReleased(KeyCode aKeyToCompareWith) const
	{
		if (myPreviousState.myVirtualKeys[static_cast<int>(aKeyToCompareWith)] == true && myCurrentState.myVirtualKeys[static_cast<int>(aKeyToCompareWith)] == false)
		{
			return true;
		}
		return false;
	}
}