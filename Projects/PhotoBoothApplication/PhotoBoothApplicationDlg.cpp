
// PhotoBoothApplicationDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PhotoBoothApplication.h"
#include "PhotoBoothApplicationDlg.h"
#include "afxdialogex.h"
#include "tuner.h"
#include "msvidctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// https://msdn.microsoft.com/en-us/library/windows/desktop/dd695339(v=vs.85).aspx

// boîte de dialogue CPhotoBoothApplicationDlg

BEGIN_DHTML_EVENT_MAP(CPhotoBoothApplicationDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CPhotoBoothApplicationDlg::CPhotoBoothApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_PHOTOBOOTHAPPLICATION_DIALOG, IDR_HTML_PHOTOBOOTHAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhotoBoothApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSVIDCTL1, m_CVideoControl);
}

BEGIN_MESSAGE_MAP(CPhotoBoothApplicationDlg, CDHtmlDialog)
END_MESSAGE_MAP()


// gestionnaires de messages pour CPhotoBoothApplicationDlg

BOOL CPhotoBoothApplicationDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	CWnd * cwndOwner = nullptr;
	CRect rcOwner;
	// Get the owner window and dialog box rectangles. 

	if ((cwndOwner = GetParent()) == nullptr)
	{
		cwndOwner = GetDesktopWindow();
	}

	if (cwndOwner == nullptr)
	{
		AfxMessageBox("Impossible d'ouvrir la fenêtre principale", MB_ICONERROR);
		return FALSE;
	}

	cwndOwner->GetWindowRect(&rcOwner);

	/*CRect rcDesktop;
	rcDesktop.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
	rcDesktop.right = rcDesktop.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
	rcDesktop.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
	rcDesktop.bottom = rcDesktop.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);*/
	MoveWindow(rcOwner, FALSE);

	// Video control
	/*CFileException Exception;
	CFile File;
	File.Open("D:\\DIVERS\\Legend - 2015.mkv", CFile::modeRead | CFile::typeBinary, &Exception);

	TCHAR strErrMessage[255];
	Exception.GetErrorMessage(strErrMessage, 255);
	MessageBox(strErrMessage, "Open file");

	BOOL bCreateVC = m_VideoControl.Create(
		"VideoContrl", WS_MAXIMIZE, rcOwner, this,
		666, &File, FALSE, NULL);
	m_VideoControl.ShowWindow(SW_SHOW);
*/
	
	IMSVidVideoRenderer * pRenderer = (IMSVidVideoRenderer*)m_CVideoControl.get_VideoRendererActive();
	SourceSizeList stabSourceSizeList[15];
	pRenderer->get_SourceSize(stabSourceSizeList);

	HRESULT hr;
	CComPtr<ITuningSpaceContainer> pTuningSpaceContainer;
	hr = CoCreateInstance(CLSID_SystemTuningSpaces,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ITuningSpaceContainer,
		reinterpret_cast<void**> (&pTuningSpaceContainer));
	if (FAILED(hr))
	{
		AfxMessageBox("Failed to create system tuning spaces object");
		return false;
	}
	long count = 0;
	hr = pTuningSpaceContainer->get_Count(&count);
	if (FAILED(hr))
	{
		AfxMessageBox("Failed to get count");
		return false;
	}

	IMSVidInputDevices * inputDevice = (IMSVidInputDevices*)m_CVideoControl.get_InputActive();
	if (inputDevice != nullptr)
	{
		// We have an active input.
		CComPtr<IMSVidTuner> myTuner;
		inputDevice->QueryInterface(__uuidof(IMSVidTuner), reinterpret_cast<void**>(&myTuner));

		if (FAILED(hr))
		{
			AfxMessageBox("Failed to QI for tuner");
			return FALSE;
		}

		// Assume pATSCTR is an IATSCTuneRequest interface pointer.
		//myTuner->put_Tune(pATSCTR);
	}

	DeleteObject(rcOwner);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CPhotoBoothApplicationDlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // contexte de périphérique pour la peinture

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// Centrer l'icône dans le rectangle client
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// Dessiner l'icône
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	{
		CDHtmlDialog::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CPhotoBoothApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CPhotoBoothApplicationDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CPhotoBoothApplicationDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
