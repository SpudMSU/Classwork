/**
 * \file ViewTimeline.h
 *
 * \author 
 *
 * View window for the animation timeline
 */
#include "PictureObserver.h"
#pragma once
class CMainFrame;


/** View window for the animation timeline */
class CViewTimeline : public CScrollView, public CPictureObserver
{
	DECLARE_DYNCREATE(CViewTimeline)

public:
    static const int Height = 90;      ///< Height to make this window

	///override for update observer
	virtual void UpdateObserver() override;
	 /**
	 * Set the mainFrame pointer
	 * \param mainFrame Pointer to the CMainFrame window
	 */
	void SetMainFrame(CMainFrame* mainFrame) { mMainFrame = mainFrame; }

protected:
	///protected constructor
	CViewTimeline();           // protected constructor used by dynamic creation

	///virtual destructor
	virtual ~CViewTimeline();



protected:

	///OnDraw
	///\param pDC
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view

	///oninitialupdate
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

public:
	///erase background
	///\param pDC
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	///edits the key frame
    afx_msg void OnEditSetkeyframe();

	///deletes the key frame
    afx_msg void OnEditDeletekeyframe();

private:
	/// The main frame window that uses this view
	CMainFrame* mMainFrame = nullptr;

	/// Bitmap image for the pointer
	std::unique_ptr<Gdiplus::Bitmap> mPointer;

	/// Flag to indicate we are moving the pointer
	bool mMovingPointer = false;

public:

	///mouse click
	///\param nFlags
	///\param point
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	///mouse click
	///\param nFlags
	///\param point
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	///mouse click
	///\param nFlags
	///\param point
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


