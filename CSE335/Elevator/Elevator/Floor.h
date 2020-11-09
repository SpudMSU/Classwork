#pragma once
class CController;

///class to handle floors
class CFloor
{
public:
	///getter for up
	///\return up member variable
	bool IsUp() { return mUp; }

	///setter for up
	///\param s is val to set mUp too
	void SetUp(bool s);

	///getter for mDown
	///\return mDown
	bool IsDown() { return mDown; }

	///setter for down
	///\param d is val to set mDown too
	void SetDown(bool d);

	///getter for mPanel
	///\return mPanel
	bool IsPanel() { return mPanel; }

	///setter for Panel
	///\param p is val to set mPanel too
	void SetPanel(bool p);

	///getter for mFloor
	///\return mFloor
	int GetFloor() { return mFloor; }

	///setter for Floor
	///\param floor is val to set mFloor too
	void SetFloor(int floor) { mFloor = floor; }

	///getter for mController
	///\return mController
	CController *GetController() { return mController; }

	///setter for Controller
	///\param controller is val to set mController too
	void SetController(CController *controller) { mController = controller; }

private:
	///member variable to tell if up
	bool mUp = false;

	///member variable to tell if down
	bool mDown = false;

	///member variable for panel
	bool mPanel = false;

	///member variable for floor
	int mFloor = 0;

	CController* mController = nullptr;   ///< Controller for this object
};

