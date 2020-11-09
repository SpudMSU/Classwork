/**
 * \file ViewEdit.h
 *
 * \author 
 *
 * View class the provides a window for editing our pixture
 */
#include "PictureObserver.h"
#include "Drawable.h"
#include "Actor.h"
#include <memory>
#pragma once

class CMainFrame;

/** View class the provides a window for editing our pixture */
class CViewEdit : public CScrollView, public CPictureObserver
{
	DECLARE_DYNCREATE(CViewEdit)

public:
	CViewEdit();           // protected constructor used by dynamic creation
	virtual ~CViewEdit();
	virtual void UpdateObserver() override;


	/**
	 * Set the mainFrame pointer
	 * \param mainFrame Pointer to the CMainFrame window
	 */
	void SetMainFrame(CMainFrame* mainFrame) { mMainFrame = mainFrame; }

	/**Sets the actor
	*\param actor is the actor to set it to*/
	void SetActor(std::shared_ptr<CActor> actor) { mActor = actor; }

	/**Sets the drawable
	*\param drawable to set*/
	void SetDrawable(std::shared_ptr<CDrawable> drawable) { mDrawable = drawable; }

	/**Getter for the actor
	*\return the actor*/
	std::shared_ptr<CActor> GetActor() { return mActor; }

	/**Getter for the drawable
	*\return the drawable*/
	std::shared_ptr<CDrawable> GetDrawable() { return mDrawable; }

protected:
	///OnDraw
	///\param pDC
	virtual void OnDraw(CDC* pDC);// overridden to draw this view

	///OnInitialUpdate
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

public:

	///erases background
	///\param pDC
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	///when click
	///\param nFlags
	///\param point
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	///when mouse moves
	///\param nFlags
	///\param point
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private: 

	///member variable for the mainframe
	CMainFrame* mMainFrame = nullptr;

	///member variable for the actor
	std::shared_ptr<CActor> mActor = nullptr;

	///member variable for the drawable
	std::shared_ptr<CDrawable> mDrawable = nullptr;

	/// The last mouse position
	Gdiplus::Point mLastMouse = Gdiplus::Point(0, 0);
};


