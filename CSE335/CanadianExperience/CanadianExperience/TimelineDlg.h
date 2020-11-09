#include "Timeline.h"
#pragma once


/// CTimelineDlg dialog class
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:

	///constructor
	///\param pParent
	CTimelineDlg(CWnd* pParent = nullptr);   // standard constructor

	///destructor 
	virtual ~CTimelineDlg();

	/**
 * Pass a timeline object to this dialog box class.
 * \param timeline The timeline object.
 */
	void SetTimeline(CTimeline* timeline);

	/** Transfer dialog values to the Timeline object
*/
	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

protected:

	///does data exchange
	///\param pDX
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	///member variable for frames
	int mNumFrames;
	/// The timeline we are editing
	CTimeline* mTimeline = nullptr;

	///member variable for the framerate
	int mFrameRate;
};
