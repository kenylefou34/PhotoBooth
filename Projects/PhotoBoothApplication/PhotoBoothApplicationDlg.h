
// PhotoBoothApplicationDlg.h : fichier d'en-tête
//

#pragma once


// boîte de dialogue CPhotoBoothApplicationDlg
class CPhotoBoothApplicationDlg : public CDHtmlDialog
{
// Construction
public:
	CPhotoBoothApplicationDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOBOOTHAPPLICATION_DIALOG, IDH = IDR_HTML_PHOTOBOOTHAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
