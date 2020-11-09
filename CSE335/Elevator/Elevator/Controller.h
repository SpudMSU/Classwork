#pragma once
#include "ElevatorController.h"
#include "Floor.h"

///class for the elevator controller
class CController : public CElevatorController
{
public:

	///constructor
	CController();

	/// The state machine states
	enum States { Idle, DoorOpening, DoorOpen, DoorClosing, Moving, Stop };

	///service function
	virtual void Service() override;

	///initialize function
	virtual void Initialize() override {}

	///open door event
	virtual void OnOpenPressed() override;

	///close door event
	virtual void OnClosePressed() override;

	///panel event
	///\param floor
	virtual void OnPanelFloorPressed(int floor) override;

	///call up event
	///\param floor
	virtual void OnCallUpPressed(int floor) override;

	///call down event
	///\param floor
	virtual void OnCallDownPressed(int floor) override;

private:
	int mFloor = 1; ///< The current floor

	double mStateTime = 0;  ///< The time in a current state

	States mState = Idle;   ///< The current state

	///member variable for going up
	bool mGoingUp = true;

	/// An object for each floor
	CFloor mFloors[NumFloors];

	/** Set a state
	 * \param state The new state to set*/
	void SetState(States state);

	///determines where to go to next
	///\return floor to go to
	int WhatFloorToGoTo();

	///determine floor above
	///\return floor above
	int WhatFloorUp();

	///determine floor down
	///\return floor down
	int WhatFloorDown();
};

