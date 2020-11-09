
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Aquarium.h"

// CChildView window
/**
 * \file ChildView.h
 *
 * \author Spencer D Cassetta
 *
 * Class that implements the child window our program draws in.
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

 // CChildView
 /**
  * The child window our program draws in.
  */
class CChildView : public CWnd
{
// Construction
public:
	///constructor
	CChildView();
	/// True until the first time we draw
	
// Attributes
public:

// Operations
public:
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	//destructor
	virtual ~CChildView();
	

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	/// An object that describes our aquarium
	CAquarium  mAquarium;
	/// Initial fish X location
	const int InitialX = 200;

	///bool for if this was first draw
	bool mFirstDraw = true; 
	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates


	/// Initial fish Y location
	const int InitialY = 200;
	/// Any item we are currently dragging
	std::shared_ptr<CItem> mGrabbedItem;
public:

	///GUI functions

	///Add Beta Fish Menu Option
	afx_msg void OnAddfishBetafish();

	///when the mouse moves
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	///when you push mouse button down
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	///when you release mouse item
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	///Erases background
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	///Add angel fish menu option
	afx_msg void OnAddfishAngelfish();

	///Add bubble fish menu option
	afx_msg void OnAddfishBubblefish();

	///Add stinky fish menu option
	afx_msg void OnAddfishStinky();

	///add a castle menu option
	afx_msg void OnAddCastle();

	///menu option for saving
	afx_msg void OnFileSaveAs();

	///menu function for loading
	afx_msg void OnFileOpen();

	///timer for fish speed
	///\param nIDEvent id for the event
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

